var express = require('express');
var app = express();
var http = require('http').Server(app);
const path = require('path');
var axios = require('axios');
const fetch = require('node-fetch');
var mongoose = require('mongoose');
var url = "mongodb+srv://yef3:rpi123456@cluster0.ro74a.mongodb.net/contactbook";

//Connect to mongodb
const connection = mongoose.createConnection(url,{ useUnifiedTopology: true, useNewUrlParser: true});

var db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', function() {
  console.log("MongoDB database connection established successfully");
});

//Schemas
const {Schema} = mongoose;
const GroupSchema = new Schema({
    groupName: String,
    members: [
        {contactName: String,
        phoneNumber: Number,
        adress: String}
    ]
}, {collection: "groups"})
const Group= connection.model("groups", GroupSchema, "groups");

app.use(express.static(__dirname));
app.listen(3000, () => {
    console.log(`ContactBook app listening at http://localhost:3000`)
  })


app.get("/addGroup/:groupname", function(req, res){
    console.log(req.params.groupname)
    var text = req.params.groupname
    Group.findOne({groupName:text}, (err, user)=>{
    	if (err) throw err;
	    if (user == null){
	        var newuser = new Group({
                groupName: String(text),
	            members: []
	        })
	        newuser.save((err)=>{
	            if (err) throw err;
	            console.log("Group " + req.params.username +" added")
	        })
	    }
	    else{
	        console.log("Already have " + text + " group");
	        res.status(200);
    	}
    })
})

app.get("/addMember/:username&:groupname", function(req, res){
    console.log(req.params.username)
    var text = req.params.username
    var group = req.params.groupname
    Group.findOne({groupName:group}, (err, user)=>{
        if (err) throw err;
        if (user != null){
            var newuser = {
                members:{
                contactName : String(text),
                phoneNumber: Number(524252340742),
                adress: String("noooooo")
                }
            }
            Group.updateOne({groupName:group},{'$push': newuser} ).then(result => {
  }).catch(err => console.error(`Failed to update the item: ${err}`))

        }
    })
})
