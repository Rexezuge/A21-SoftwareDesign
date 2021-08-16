$(document).ready(function(){
	//When open the web page, the page will automatically show the first group
	shwoAllGroups();
});

//Display AddContact div and hide other divs
function displayAddContact() {
	document.getElementById("Contact_group").style.display = "none";
	document.getElementById("Area_Add_Contact_Group").style.display = "none";
    document.getElementById("Area_Add_Contact").style.display = "inline";
}
//Display AddGroup div and hide other divs
function displayAddGroup() {
	document.getElementById("Contact_group").style.display = "none";
	document.getElementById("Area_Add_Contact_Group").style.display = "inline";
    document.getElementById("Area_Add_Contact").style.display = "none";
}

//Jump to the AccountPage
function goToAccountPage(){
	window.location.href='sublink/account.html';
}

//Post the input information to the server and save them into the database
function addContact() {
	var contact_name = document.querySelector('#add_contact_name').value;
	var contact_phone = document.querySelector('#add_contact_phone').value;
	var contact_email = document.querySelector('#add_contact_email').value;
	var contact_group = document.querySelector('#add_contact_group').value;
	//Check if every block is entered
	if (contact_name == "" || contact_phone == "" || contact_group == "" || contact_email == "") {
		alert("Info Missed!")
	} else {
		url = "http://localhost:3000/addContact/" + contact_name + '/' + contact_phone + '/' + contact_email + '/' + contact_group
		console.log("Start to post the info!" + url)
	}//Post information to the server
		$.post(url, function(data) {
			//alert(data.msg);
			console.log(data.status)
			// If information saved sucessfully, reload the whole page

			window.location.reload();
			}
		);
}

//Post data from input and save the new group into databse
function addGroup() {
	//Get data
	var new_group = document.querySelector('#add_new_group').value;

	//Ensure there is no empty input
	if (new_group == "") {
		alert("Info Missed!")
	} else {
		console.log("Start to post the info!")
		url = "http://localhost:3000/addGroup/" + new_group;
	}//Post information to the server
		$.post(url, function(data) {
			//alert(data.msg);
			console.log(data);
			// If information saved sucessfully, reload the whole page
			window.location.reload();
			}
		);
}
//Show the contacts information in the group one clicked
function showOneGroupContact(group_name){
	//Hide the form and show the div with id=Contact_group
	group_name = group_name.substring(0, group_name.length-18);
	document.getElementById("Contact_group").style.display = "inline";
	document.getElementById("Area_Add_Contact_Group").style.display = "none";
    document.getElementById("Area_Add_Contact").style.display = "none";
	$("#Contacts_Info_List").empty();
	$(".Group_Name").html(group_name);
	//Connerct to the server to get contacts information
	$.ajax({
		type:"GET",
		url: "http://localhost:3000/contacts/"+group_name,
		beforeSend: function(){},
		success:function(data){
			//If there is no data
			console.log(data);
			if (data==null||data.length==0){
				$("#Contacts_Info_List").append("No contacts in this group")
			}
			else{
				//Output information in the screen
				length = data.length;
				for (i=0;i<length;i++){
					var contact_name = data[i].name;
					var mail1 = data[i].email;
					var phone = data[i].phone;
					var mostRecent = data[i].mostRecent;
					var contactHtml = '<li class="Contact">\
						            <button class="Delete_Contact">Delete</button>\
									<button class="Top_Contact">Top</button>\
									<button class="Display_Recent_Email">Display</button>\
						            <p class="Contact_Name">'+contact_name+'</p>\
						            <p class="Address">'+mail1+'</p>\
						            <p class="Address">'+phone+'</p>\
						            <p class="Recent_Email">Recent Email: '+mostRecent+'</p>\
						         </li>'
					$("#Contacts_Info_List").append(contactHtml);
				}
			}
			$(".Top_Contact").click(function(){
				groups = $("#Contacts_Info_List").contents();
				group = $(this).parent();
				var contact = $(this).next().next().text();
				topContacts(group,contact);
				console.log(group);
					//showTopContact($("a.Contact_Group")[0].text);
			})

			$(".Delete_Contact").click(function(){
				var contact = $(this).next().next().text();
				deleteContact(contact);
				console.log(contact);
				//Contact($("a.Contact_Group")[0].text);
			})

			$(".Display_Recent_Email").click(function(){
				$(this).next().next().next().next().toggle(100);
			})
		}
	})
}

//List all groups in the database
function shwoAllGroups(){
	$.ajax({
		type:"GET",
		url: "http://localhost:3000/groups",
		beforeSend: function(){},
		success:function(data){
			console.log(data);
			length = data.length;
			for (i=0;i<length;i++){
				group = data[i].name;
				groupHtml = '<a class="Contact_Group" >'+group+' <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-arrow-right" viewBox="1 -3 16 16"><path fill-rule="evenodd" d="M1 8a.5.5 0 0 1 .5-.5h11.793l-3.147-3.146a.5.5 0 0 1 .708-.708l4 4a.5.5 0 0 1 0 .708l-4 4a.5.5 0 0 1-.708-.708L13.293 8.5H1.5A.5.5 0 0 1 1 8z"/></svg>\
							<button class="Top_Button">Top</button>\
							</a>';
				$("#groups_block").append(groupHtml);
			}
			//Show the first group automatically
			showOneGroupContact($("a.Contact_Group")[0].text)

			//Allow clicking the groupname to show details
			$(".Contact_Group").click(function(){
				showOneGroupContact($(this).text());
				//Change color after every group move
				checkAndChangeColor();

			});
			checkAndChangeColor();

			$(".Top_Button").click(function(){
				groups = $("#groups_block").contents();
				console.log(this);
				//$(this).addClass("TOP");
				group = $(this).parent();
				group_name = group.text();
				group_name = group_name.substring(0, group_name.length-18);
				topGroup(group_name);
				checkAndChangeColor();
			})

			$(".Top_Contact").click(function(){
				groups = $("#Contacts_Info_List").contents();
				group = $(this).parent();
				topContacts(group);
				console.log(group);
				showTopContact($("a.Contact_Group")[0].text);
			})

			$(".New_Contact").click(function(){
				displayAddContact();
			});
			$(".New_Group").click(function(){
				displayAddGroup();
			});

		}
	})
}

// check the color selection and set the color
function checkAndChangeColor() {
	url = "http://localhost:3000/getColor/0000"
	$.get(url, function(data){
		var current_selected_color = data.color
		console.log(current_selected_color);
		// change the color to the 2021 Pantone year's color
		if (current_selected_color == "2021") {
			document.querySelector(".account").style.backgroundColor = '#F5DF4D';
			document.querySelector(".New_Contact").style.backgroundColor = '#F5DF4D';
			document.querySelector(".New_Group").style.backgroundColor = '#F5DF4D';
			document.querySelector("#add_contact_add_btn").style.backgroundColor = '#F5DF4D';
			document.querySelector("#add_group_add_btn").style.backgroundColor = '#F5DF4D';
			document.querySelector(".decoration").style.backgroundColor = '#F5DF4D';
			$(".Top_Button").css("color",'#F5DF4D');
			$(".Top_Button").css("border",'2px solid #F5DF4D');
			$(".Top_Contact").css("color",'#F5DF4D');
			$(".Top_Contact").css("border",'2px solid #F5DF4D');
			$(".Delete_Contact").css("color",'#F5DF4D');
			$(".Delete_Contact").css("border",'2px solid #F5DF4D');
			$(".TOP").css("background-color", "#F5DF4D");
			$(".TOP").css("color", "white");
			$(".Display_Recent_Email").css("color",'#F5DF4D');
			$(".Display_Recent_Email").css("border",'2px solid #F5DF4D');
		// change the color to the 2020 Pantone year's color
		} else if (current_selected_color == "2020") {
			document.querySelector(".account").style.backgroundColor = '#34558b';
			document.querySelector(".New_Contact").style.backgroundColor = '#34558b';
			document.querySelector(".New_Group").style.backgroundColor = '#34558b';
			document.querySelector("#add_contact_add_btn").style.backgroundColor = '#34558b';
			document.querySelector("#add_group_add_btn").style.backgroundColor = '#34558b';
			document.querySelector(".decoration").style.backgroundColor = '#34558b';
			$(".Top_Button").css("color",'#34558b');
			$(".Top_Button").css("border",'2px solid #34558b');
			$(".Top_Contact").css("color",'#34558b');
			$(".Top_Contact").css("border",'2px solid #34558b');
			$(".Delete_Contact").css("color",'#34558b');
			$(".Delete_Contact").css("border",'2px solid #34558b');
			$(".TOP").css("background-color", "#34558b");
			$(".TOP").css("color", "white");
			$(".Display_Recent_Email").css("color",'#34558b');
			$(".Display_Recent_Email").css("border",'2px solid #34558b');
		// change the color to the 2019 Pantone year's color
		} else if (current_selected_color == "2019") {
			document.querySelector(".account").style.backgroundColor = '#ff6f61';
			document.querySelector(".New_Contact").style.backgroundColor = '#ff6f61';
			document.querySelector(".New_Group").style.backgroundColor = '#ff6f61';
			document.querySelector("#add_contact_add_btn").style.backgroundColor = '#ff6f61';
			document.querySelector("#add_group_add_btn").style.backgroundColor = '#ff6f61';
			document.querySelector(".decoration").style.backgroundColor = '#ff6f61';
			$(".Top_Button").css("color",'#ff6f61');
			$(".Top_Button").css("border",'2px solid #ff6f61');
			$(".Top_Contact").css("color",'#ff6f61');
			$(".Top_Contact").css("border",'2px solid #ff6f61');
			$(".Delete_Contact").css("color",'#ff6f61');
			$(".Delete_Contact").css("border",'2px solid #ff6f61');
			$(".TOP").css("background-color", "#ff6f61");
			$(".TOP").css("color", "white");
			$(".Display_Recent_Email").css("color",'#ff6f61');
			$(".Display_Recent_Email").css("border",'2px solid #ff6f61');
		// change the color to the 2018 Pantone year's color
		} else if (current_selected_color == "2018") {
			document.querySelector(".account").style.backgroundColor = '#604c8d';
			document.querySelector(".New_Contact").style.backgroundColor = '#604c8d';
			document.querySelector(".New_Group").style.backgroundColor = '#604c8d';
			document.querySelector("#add_contact_add_btn").style.backgroundColor = '#604c8d';
			document.querySelector("#add_group_add_btn").style.backgroundColor = '#604c8d';
			document.querySelector(".decoration").style.backgroundColor = '#604c8d';
			$(".Top_Button").css("color",'#604c8d');
			$(".Top_Button").css("border",'2px solid #604c8d');
			$(".Top_Contact").css("color",'#604c8d');
			$(".Top_Contact").css("border",'2px solid #604c8d');
			$(".Delete_Contact").css("color",'#604c8d');
			$(".Delete_Contact").css("border",'2px solid #604c8d');
			$(".TOP").css("background-color", "#604c8d");
			$(".TOP").css("color", "white");
			$(".Display_Recent_Email").css("color",'#604c8d');
			$(".Display_Recent_Email").css("border",'2px solid #604c8d');
		} 
	});
}


function showTopContact(group_name){
	group_name = group_name.substring(0, group_name.length-18);
	//Connerct to the server to get contacts information
	$.ajax({
		type:"GET",
		url: "http://localhost:3000/getTopContact/"+group_name,
		beforeSend: function(){},
		success:function(data){
			//If there is no data
			if (data!=null){
				var contact_name = data.topContact;
				contacts = $("#Contacts_Info_List").contents();
				var top;
				for (i=0;i<contacts.length;i++){
					name = $(contacts[i]).contents().filter(".Contact_Name").text()
					//alert(name);
					if (contact_name == name){
						top = contacts[i];
						console.log(top);
						break;
					}
				}
				$(top).contents().filter("button").filter(':not(.Delete_Contact)').addClass("TOP");
				$(contacts[0]).before(top);
				
				checkAndChangeColor();
			}
		}
	})

}

function topGroup(group_name){
	//alert(group_name);
	$.ajax({
		type:"POST",
		url: "http://localhost:3000/setTopGroup/"+group_name,
		beforeSend: function(){},
		success:function(data){
			window.location.reload();
		}
	})
}

function showTopContact(group_name, contact_name){
	group_name = group_name.substring(0, group_name.length-18);
	//Connerct to the server to get contacts information
	$.ajax({
		type:"POST",
		url: "http://localhost:3000/setTop/"+group_name+"/"+contact_name,
		beforeSend: function(){},
		success:function(data){
			window.location.reload();
		}
	})

}


function deleteContact(contact_name){
	//alert(group_name);
	$.ajax({
		type:"DELETE",
		url: "http://localhost:3000/DeleteContact/"+contact_name,
		beforeSend: function(){},
		success:function(data){
			window.location.reload();
		}
	})
}