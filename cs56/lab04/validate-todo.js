function validate()

{

    if(document.getElementById('email').value.length==0){

            alert("Email can't be blank");
        }
    // STEP 4 TODO: We want to create a validation checking
    if(document.getElementById('password').value.length<4){

            alert("Password is at least 4 digits");
        }

    else 

        {

        window.open("welcome-todo.html");

        }

}

function ajax(){
    // STEP 5 TODO: Replace this with JQUERY
    var xmlhttp = new XMLHttpRequest();
    var url = "http://localhost:8000/server.json";

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            var user = JSON.parse(xmlhttp.responseText);
            printEmail(user);
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.send();

    function printEmail(user) {
        console.log(user)
        document.getElementById("username").innerHTML = user.email;
    }
  }
