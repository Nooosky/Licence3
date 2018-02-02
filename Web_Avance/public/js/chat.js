var user;
var key;
var general;
var privateMessage;
var users;

var time;
var indiceGeneral = 0;
var indicePrivateMessage = 0;


var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    var data = JSON.parse(this.responseText);

    if (data.user != "" && data.key != null)
    {
      user = data.user;
      key = data.key;
      document.getElementById("titleChat").innerHTML += " - utilisateur : " + user;
      time = new Date().getTime();
    }
    if(typeof data.general != 'undefined' && data.general.length > 0)
      general = data.general;
    if(typeof data.user != 'undefined' && data.user.length > 0 && data.key == null)
      privateMessage = data.user;
    if(typeof data.users != 'undefined' && data.users.length > 0)
      users = data.users;
  }
  else {
    switch (this.status) {
      case 409:
          alert("nom d'utilisateur deja utiliser");
          connection();
        break;
      case 403:
          alert("nom incorrecte");
          connection();
        break;
      default:
        break;
    }
  }
};

function connection()
{
  document.getElementById("input").value = "";
  var person = prompt("Please enter your name:");
  if (person == null)
    document.location.href="../index.html";
  else if (person == "")
      person = "unknown";

  xhttp.open("POST", "/chat/"+person);
  xhttp.send();
}

function deconnection()
{
  xhttp.open("DELETE", "/chat/"+user+"/"+key);
  xhttp.send();
  user = "";
  key = null;
  setTimeout(function(){document.location.href="../index.html";}, 500);
}

function sendMessage()
{
  var message = document.getElementById("input").value;
  document.getElementById("input").value = "";
  if(message.indexOf("/to:") == 0)
  {
    var to =  message.split(" ")[0].split(":")[1];
    xhttp.open("PUT", "/chat/"+user+"/"+key+"/"+to);
    xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhttp.send("message="+message.substring(4 + to.length + 1, message.lenght));
  }
  else
  {
    xhttp.open("PUT", "/chat/"+user+"/"+key);
    xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhttp.send("message="+message);
  }
}

setInterval(
  function receiveMessage()
  {
    if(user != "" && key != null)
    {
      xhttp.open("GET", "/chat/"+user+'/'+key+'/timestamp');
      xhttp.send();
    }

    usersConnected();
    message();
  }
, 500);

function usersConnected()
{
  var element = document.getElementById("pseudo");
  while (element.firstChild) {
    element.removeChild(element.firstChild);
  }

  if (typeof users != 'undefined')
    for(var i= 0; i < users.length; ++i)
    {
      var zonePseudo = document.getElementById("pseudo");
      var user = document.createElement("p");
      user.innerHTML = users[i];
      zonePseudo.appendChild(user);
    }
}

function message()
{
  if (typeof general != 'undefined')
  {
    for(indiceGeneral; indiceGeneral < general.length; ++indiceGeneral)
    {
      if(general[indiceGeneral].when > time)
      {
        var temps=new Date();
        temps.setTime(general[indiceGeneral].when);
        var strTime = temps.getHours() + ":" + temps.getMinutes() + ":" + temps.getSeconds();

        var zoneMessage = document.getElementById("message");
        var message = document.createElement("p");
        if(general[indiceGeneral].from == null)
        {
          message.innerHTML =  strTime + " - (Systeme) : " + general[indiceGeneral].text;
          message.style.color = "red";
        }
        else if(general[indiceGeneral].from == user)
        {
          message.innerHTML =  strTime + " - "  + general[indiceGeneral].from + " : " + general[indiceGeneral].text;
          message.style.color = "green";
        }
        else
        {
          message.innerHTML =  strTime + " - "  + general[indiceGeneral].from + " : " + general[indiceGeneral].text;
        }
        zoneMessage.appendChild(message);
      }
    }
  }

  if (typeof privateMessage != 'undefined')
    for(indicePrivateMessage; indicePrivateMessage < privateMessage.length; ++indicePrivateMessage)
    {
      if(privateMessage[indicePrivateMessage].when > time)
      {
        var temps=new Date();
        temps.setTime(privateMessage[indicePrivateMessage].when);
        var strTime = temps.getHours() + ":" + temps.getMinutes() + ":" + temps.getSeconds();

        var zoneMessage = document.getElementById("message");
        var message = document.createElement("p");
        if(privateMessage[indicePrivateMessage].from == user)
        {
          message.innerHTML =  strTime + " - "  + privateMessage[indicePrivateMessage].from + " : " + privateMessage[indicePrivateMessage].text;
          message.style.color = "green";
        }
        else
        {
          message.innerHTML =  strTime + " - "  + privateMessage[indicePrivateMessage].from + " : " + privateMessage[indicePrivateMessage].text;
        }
        zoneMessage.appendChild(message);
      }
    }
}
