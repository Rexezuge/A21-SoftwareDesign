// $(document).ready(function(){
//   	$("button.test").click(function(){
//   	alert("test");
//   	url = '/addMember/NotToday&b';
//     $.get(url, function(data){
//       alert("back");
//     });
//   });
// });
// const axios = require('axios').default;
function displayAddContact() {
	document.getElementById("Contact_group").style.display = "none";
	document.getElementById("Area_Add_Contact_Group").style.display = "none";
    document.getElementById("Area_Add_Contact").style.display = "inline";
}

function displayAddGroup() {
	document.getElementById("Contact_group").style.display = "none";
	document.getElementById("Area_Add_Contact_Group").style.display = "inline";
    document.getElementById("Area_Add_Contact").style.display = "none";
}

function FakedisplayAddContact() {
	document.getElementById("Area_Add_Contact_Group").style.display = "none";
    document.getElementById("Area_Add_Contact").style.display = "none";
    document.getElementById("Contact_group").style.display = "";
}


function goToAccountPage(){
	window.location.href='sublink/account.html';
}

function addContact() {
	var contact_name = document.querySelector('#add_contact_name').value;
	var contact_email_1 = document.querySelector('#add_contact_email_1').value;
	var contact_email_2 = document.querySelector('#add_contact_email_2').value;
	var contact_group = document.querySelector('#add_contact_group').value;
	if (contact_name == "" || contact_email_1 == "" || contact_group == "") {
		alert("Info Missed!")
	} else {
		if (contact_email_2 == "") {
			contact_email_2 = "none"
		}
		console.log("Start to post the info!")
		url = "http://localhost:3000/addContact/" + contact_name + '/' + contact_email_1 + '/' + contact_email_2 + '/' + contact_group
	}
		$.post(url, function(data) {
				console.log(data);
			}
		);
}

function addGroup() {
	var new_group = document.querySelector('#add_new_group').value;
	var define_new_group = document.querySelector('#define_new_group').value;
	if (new_group == "" || define_new_group == "") {
		alert("Info Missed!")
	} else {
		console.log("Start to post the info!")
		url = "http://localhost:3000/addGroup/" + new_group + '/' + define_new_group
	}
		$.post(url, function(data) {
				console.log(data);
			}
		);
}