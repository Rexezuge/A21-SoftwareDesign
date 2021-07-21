$(document).ready(function(){
  	$("button.test").click(function(){
  	alert("test");
  	url = '/addMember/NotToday&b';
    $.get(url, function(data){
      alert("back");
    });
  });
});

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
