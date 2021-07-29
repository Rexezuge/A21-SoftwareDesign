$(document).ready(function(){
	//When open the web page, the page will automatically show the first group
	shwoAllGroups();
});
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
		url = "http://localhost:3000/addContact/" + contact_name + '/' + contact_email_1 + '/' + contact_email_2 + '/' + contact_group
		console.log("Start to post the info!" + url)
	}
		$.post(url, function(data) {
				alert(data.msg);
				console.log(data.status)
			if (data.status!="Fail")
				window.location.reload();
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
			alert(data.msg);
			console.log(data);
			window.location.reload();
			}
		);
}

function showOneGroupContact(group_name){
	document.getElementById("Contact_group").style.display = "inline";
	document.getElementById("Area_Add_Contact_Group").style.display = "none";
    document.getElementById("Area_Add_Contact").style.display = "none";
	$("#Contacts_Info_List").empty();
	$(".Group_Name").html(group_name);
	$.ajax({
		type:"GET",
		url: "http://localhost:3000/getGroupContacts/"+group_name,
		beforeSend: function(){},
		success:function(data){
			//If there is no data
			if (data.length==0){
				$("#Contacts_Info_List").append("No contacts in this")
			}
			length = data.length;
			for (i=0;i<length;i++){
				var contact_name = data[i].account_name;
				var mail1 = data[i].mail_address_1;
				var mail2 = data[i].mail_address_2;
				var contactHtml = '<li class="Contact">\
					            <p class="Contact_Name">'+contact_name+'</p>\
					            <p class="Address">'+mail1+'</p>\
					            <p class="Address">'+mail2+'</p>\
					         </li>'
				$("#Contacts_Info_List").append(contactHtml);
			}
		}
	})
}

function shwoAllGroups(){
	$.ajax({
		type:"GET",
		url: "http://localhost:3000/getGroups",
		beforeSend: function(){},
		success:function(data){
			console.log(data);
			length = data.length;
			for (i=0;i<length;i++){
				group = data[i].group_name;
				groupHtml = '<a class="Contact_Group" >'+group+' </a><svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-arrow-right" viewBox="1 -3 16 16"><path fill-rule="evenodd" d="M1 8a.5.5 0 0 1 .5-.5h11.793l-3.147-3.146a.5.5 0 0 1 .708-.708l4 4a.5.5 0 0 1 0 .708l-4 4a.5.5 0 0 1-.708-.708L13.293 8.5H1.5A.5.5 0 0 1 1 8z"/> </svg>'
				$("#groups_block").append(groupHtml);
			}
			//Show the first group automatically
			showOneGroupContact($("a.Contact_Group")[0].text)

			$(".Contact_Group").click(function(){
				showOneGroupContact($(this).text());
			});

			$(".New_Contact").click(function(){
				displayAddContact();
			});
			$(".New_Group").click(function(){
				displayAddGroup();
			});
		}
	})
}