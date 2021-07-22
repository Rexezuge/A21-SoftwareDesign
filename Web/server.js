var express = require('express');
var app = express();
var http = require('http').Server(app);
const path = require('path');
var axios = require('axios');
const fetch = require('node-fetch');
var mongoose = require('mongoose');
var cors = require('cors');
app.use(cors());

var url = "mongodb+srv://yef3:rpi123456@cluster0.ro74a.mongodb.net/contactbook";

app.use(express.static(__dirname));

mongoose.connect(url, { useUnifiedTopology: true, useNewUrlParser: true });

// connect to the database and inform
var db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', function() {
  console.log("MongoDB database connection established successfully");
});


app.listen(3000, () => {
    console.log(`ContactBook app listening at http://localhost:3000`)
})

// Schemas
const { Schema } = mongoose;
const contactInfo = new Schema ({
    account_name: {type: String},
    mail_address_1: {type: String},
    mail_address_2: {type: String},
    group_in: {type: String}
});
const ContactInfo = mongoose.model('ContactInfo', contactInfo);


//Add contact to the database
app.post('/addContact/:account_name/:mail_address_1/:mail_address_2/:group_in', function(req, res) {
    var account_name = req.params.account_name;
    var mail_address_1 = req.params.mail_address_1;
    var mail_address_2 = req.params.mail_address_2;
    var group_in = req.params.group_in;
    GroupInfo.findOne({group_name: group_in}).exec(function(err,group){
        if (group==null){
            res.json({'msg':'Group '+ group_in + " is not exist\n Please create the group first"});
        }

    })

    // avoid saving repetitive info
    ContactInfo.findOne({account_name: account_name, group_in: group_in}).exec(function(err, contact) {
        if (contact) {
            res.json({'msg': account_name + ' already existed in ' + group_in});
        } else {
            var thisContactInfo = new ContactInfo({
                account_name: account_name,
                mail_address_1: mail_address_1,
                mail_address_2: mail_address_2,
                group_in: group_in
            })
            thisContactInfo.save(function (err) {
                if (err) res.json(err);
                else {
                    text = account_name + " added to Group: " + group_in;
                    console.log(text);
                    res.json({'msg': text});
                }
            })
        }
    });
})

//Schema
const groupInfo = new Schema ({
    group_name: {type: String},
    note: {type: String},
});
const GroupInfo = mongoose.model('GroupInfo', groupInfo);

//Add group to the database
app.post('/addGroup/:group_name/:note', function(req, res) {
    var group_name = req.params.group_name;
    var note = req.params.note;

    // avoid saving repetitive info
    GroupInfo.findOne({group_name: group_name, note: note}).exec(function(err, group) {
        if (group) {
            res.json({'msg': 'Already existed'});
        } else {
            var thisGroupInfo = new GroupInfo({
                group_name: group_name,
                note: note
            })
            thisGroupInfo.save(function (err) {
                if (err) res.json(err);
                else res.json({'msg': group_name + " is added!"})
            })
        }
    });
})


//Get all groups in the database
app.get('/getGroups', function(req, res){
    GroupInfo.find((err, groups)=>{
        console.log(groups);
        res.json(groups);
    })
})

//Get contacts in specific Group
app.get('/getGroupContacts/:group_name', function(req, res){
    var group_name = req.params.group_name;
    ContactInfo.find({group_in: group_name},(err, contacts)=>{
        console.log(contacts);
        res.json(contacts);
    })
})

