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
const ContactSchema = new Schema({
    name: String,
    phoneNumber: Number,
    adress: String
}, {collection: "contacts"})
const Contact = connection.model("Contacts", ContactSchema, "contacts");

app.use(express.static(__dirname));
app.listen(3000, () => {
    console.log(`ContactBook app listening at http://localhost:3000`)
  })


app.get("/addtest/:username", function(req, res){
    console.log(req.params.username)
    var text = req.params.username
    Contact.findOne({name:text}, (err, user)=>{
    	if (err) throw err;
	    if (user == null){
	        var newuser = new Contact({
	            name : String(req.params.username),
    			phoneNumber: Number(5189610742),
    			adress: String("yef3@rpi.edu")
	        })
	        newuser.save((err)=>{
	            if (err) throw err;
	            console.log("User " + req.params.username +" added")
	        })
	    }
	    else{
	        console.log("Finded");
	        res.status(200);
    	}
    })
})