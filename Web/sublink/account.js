// save the selected color value to the db
function changeColor() {
    var selected_value = $("#change_theme_color :selected").val();
    console.log(selected_value)
    url = "http://localhost:3000/postColor/" + "0000" + '/' + selected_value;
    $.post(url, function(data) {
        alert(data.msg);
    });
    location.reload();
}

// check the color selection and set the color
function checkAndChangeColor() {
  url = "http://localhost:3000/getColor/0000"
  $.get(url, function(data){
    var current_selected_color = data.color
    console.log(current_selected_color);
    if (current_selected_color == "2021") {
      document.querySelector(".account").style.backgroundColor = '#F5DF4D';
      document.querySelector(".change_theme_color_btn").style.backgroundColor = '#F5DF4D';
      document.querySelector(".change_account_name_btn").style.backgroundColor = '#F5DF4D';
    } else if (current_selected_color == "2020") {
      document.querySelector(".account").style.backgroundColor = '#34558b';
      document.querySelector(".change_theme_color_btn").style.backgroundColor = '#34558b';
      document.querySelector(".change_account_name_btn").style.backgroundColor = '#34558b';
    } else if (current_selected_color == "2019") {
      document.querySelector(".account").style.backgroundColor = '#ff6f61';
      document.querySelector(".change_theme_color_btn").style.backgroundColor = '#ff6f61';
      document.querySelector(".change_account_name_btn").style.backgroundColor = '#ff6f61';
    } else if (current_selected_color == "2018") {
      document.querySelector(".account").style.backgroundColor = '#604c8d';
      document.querySelector(".change_theme_color_btn").style.backgroundColor = '#604c8d';
      document.querySelector(".change_account_name_btn").style.backgroundColor = '#604c8d';
    } 
  });
}

function changeName() {
  var selected_value = document.querySelector(".change_account_name_input").value;
    console.log(selected_value)
  document.cookie = "localName="+selected_value;
  updateName();
}

function updateName() {
  const localName = document.cookie
  .split('; ')
  .find(row => row.startsWith('localName='))
  .split('=')[1];
  console.log(localName);
  document.querySelector(".current_account_name").innerHTML = "User Name: " + localName;
}

window.onload = function () { 
  checkAndChangeColor();
  updateName();
}