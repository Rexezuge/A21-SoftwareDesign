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

function addContact() {
    alert("Add Success!!! (Fake)")
}

function goToAccountPage(){
	window.location.href='sublink/account.html';
}
