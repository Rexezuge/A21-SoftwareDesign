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
//Load the html and css
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
        //Group is not exist, addContact fail
        if (group==null){
            res.json({'msg':'Group '+ group_in + " is not exist\nPlease create the group first",
                      'status':'Fail'});
        }
        else{
            ContactInfo.findOne({account_name: account_name, group_in: group_in}).exec(function(err, contact) {
            //Contact already exist, fail to add contact
            if (contact) {
                res.json({'msg': account_name + ' already existed in ' + group_in,
                          'status':'Fail'});
            } else {
                //Save new contact into database
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
        }

    })

    // avoid saving repetitive info

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
    GroupInfo.findOne({group_name: group_name}).exec(function(err, group) {
        //Group already exist. Fail to add the group
        if (group) {
            res.json({'msg': 'Already existed',
                    'status':'Fail'});
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
app.get('/groups', function(req, res){
    var groupName = req.params.groupName;
    var contactName = req.params.contactName;
    console.log("______________________________________________________")
    axios.get('http://localhost:3001/groups')
        .then(function (response) {
            console.log("—————————————Success———————————————")
            console.log(response.data);
            res.send(response.data);
        })
        .catch(function (error) {
            console.log(error);
            res.json(error);
        });
})

//Get contacts in specific Group
app.get('/contacts/:groupName', function(req, res){
    var groupName = req.params.groupName;
    //var contactName = req.params.contactName;
    console.log("GET CONTACTS-START")
    axios.get('http://localhost:3001/contacts/' + groupName)
        .then(function (response) {
            console.log("GET CONTACTS: ")
            console.log(response.data);
            res.json(response.data);
        })
        .catch(function (error) {
            console.log(error);
            res.json(error);
        });
})


const colorInfo = new Schema ({
    user_ID: {type: String},
    color: {type: String},
});
const ColorInfo = mongoose.model('ColorInfo', colorInfo);

app.post('/postColor/:user_ID/:color', function(req, res) {
    var user_ID = req.params.user_ID;
    var color = req.params.color;
    
    ColorInfo.findOne({user_ID: user_ID}).exec(function(err, thiscolor) {
        if (thiscolor) {
            console.log("Find one")
            // ColorInfo.deleteOne({user_ID: user_ID})
            ColorInfo.findOneAndDelete({user_ID: user_ID}).exec(function(err, thiscolor_2) {
                if (err) console.log(err);
                else console.log({'msg': 'Deleted'})
            });

            var thisColorInfo = new ColorInfo({
                user_ID: user_ID,
                color: color
            })
            thisColorInfo.save(function (err) {
                if (err) res.json(err);
                else {
                    res.json({'msg': "Saved!"})
                    console.log("Saved!")
                }
            })
        } else {
            var thisColorInfo = new ColorInfo({
                user_ID: user_ID,
                color: color
            })
            thisColorInfo.save(function (err) {
                if (err) res.json(err);
                else {
                    res.json({'msg': "Saved!"})
                    console.log("Saved!")
                }
            })
        }
    });
})

app.get('/getColor/:user_ID', function(req, res){
    var user_ID = req.params.user_ID;
    ColorInfo.findOne({user_ID: user_ID},(err, color)=>{
        console.log(color);
        res.json(color);
    })
})

app.post('setTop/:group/:contact',function(req, res){
    var groupName = req.params.group;
    var contactName = req.params.contact;
    axios.post('http://localhost:3001/tops/' + groupName + '/' + contactName)
        .then(function (response) {
            console.log(response);
            res.json(response);
        })
        .catch(function (error) {
            console.log(error);
            res.json(error);
        });
})

app.post('/setTopGroup/:group',function(req, res){
    var groupName = req.params.group;
    console.log("TOP "+groupName);
    axios.post('http://localhost:3001/tops/' + groupName)
        .then(function (response) {
            console.log(response);
            res.json(response);
        })
        .catch(function (error) {
            console.log(error);
            res.json(error);
        });
})
