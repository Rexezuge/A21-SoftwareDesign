var express = require('express');
var app = express();
var http = require('http').Server(app);
const path = require('path');
var axios = require('axios');
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
app.post('/addContact/:account_name/:contact_phone/:contact_email/:contact_group', function(req, res) {
    var account_name = req.params.account_name;
    var contact_phone = req.params.contact_phone;
    var contact_email = req.params.contact_email;
    var contact_group = req.params.contact_group;
    var meta_info = {"phone": Number(parseInt(contact_phone)), "email": contact_email}
    console.log("Add contact:")
    var url = 'http://localhost:3001/contacts/' + contact_group + '/' + account_name
    axios.post(url, meta_info,{
                headers:{
                'Content-Type':'application/json'
                }
    })
    .then(function (response) {
        console.log(response);
        res.json(response);
    })
    .catch(function (error) {
        console.log(error);
        res.json(error);
    });
})


//Add group to the database
app.post('/addGroup/:groupName', function(req, res) {
    var groupName = req.params.groupName;
    axios.post('http://localhost:3001/groups/' + groupName)
        .then(function (response) {
            console.log(response);
            res.json(response);
        })
        .catch(function (error) {
            console.log(error);
            res.json(error);
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
            //console.log(response.data);
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
            //console.log(response.data);
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
        //console.log(color);
        res.json(color);
    })
})

//Top contact in the group
app.post('/setTop/:group/:contact',function(req, res){
    var groupName = req.params.group;
    var contactName = req.params.contact;
    axios.delete("http://localhost:3001/tops/" + groupName)
        .then(function (response) {
            console.log("DELETE TOP CONTACT STATUS:")
            console.log(response);
            res.json(response);
        })
        .catch(function (error) {
            console.log(error);
            res.json(error);
        });
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

//Top a group
app.post('/setTopGroup/:group',function(req, res){
    var groupName = req.params.group;
    console.log("TOP "+groupName);
    axios.delete("http://localhost:3001/tops/")
        .then(function (response) {
            console.log("DELETE TOP GROUP STATUS:")
            console.log(response.response);
            res.json(response.response);
        })
        .catch(function (error) {
            console.log(error.response);
            res.json(error);
    });
    axios.post('http://localhost:3001/tops/' + groupName)
        .then(function (response) {
            console.log(response.response);
            res.json(response.response);
        })
        .catch(function (error) {
            console.log(error.response);
            res.json(error);
        });
})

//Add contact to the database
app.delete('/DeleteContact/:account_name/', function(req, res) {
    var account_name = req.params.account_name;
    var msg = "TRY DELETE "+ account_name; 
    console.log(msg);
    axios.delete('http://localhost:3001/contacts/NULL/' + account_name)
    .then(function (response) {
        console.log("DELETE");
        console.log(response.response);
        res.json(response.response);
    })
    .catch(function (error) {
        console.log("ERROR");
        console.log(error.response);
        res.json(error);
    });
})
