var buttonPressed = false;
var positionX = 0;
var positionY = 0;
var size = 5;
var tool = "null";
var fixed = false;
var positionFixeX = 0;
var positionFixeY = 0;
var sizeX = 0;
var sizeY = 0;


function buttonDown()
{
  buttonPressed = true;
}

function buttonRelease()
{
  buttonPressed = false;
}

function mouseMove(e)
{
  var rect = e.target.getBoundingClientRect();
  positionX = e.clientX - rect.left;
  positionY = e.clientY - rect.top;

  draw();
}

function mouseOut()
{
  buttonPressed = false;

  var c2 = document.getElementById("canvas2");
  var ctx2 = c2.getContext("2d");
  ctx2.clearRect(0, 0, c2.width, c2.height);
}

function draw()
{
  switch (tool)
  {
    case "pinceau":
    {
      var c2 = document.getElementById("canvas2");
      var ctx2 = c2.getContext("2d");
      ctx2.clearRect(0, 0, c2.width, c2.height);
      ctx2.fillStyle="white";
      ctx2.beginPath();
      ctx2.arc(positionX, positionY, size, 0, 2 * Math.PI);
      ctx2.fill();

      if (buttonPressed)
      {
        var c1 = document.getElementById("canvas1");
        var ctx1 = c1.getContext("2d");
        ctx1.fillStyle="white";
        ctx1.beginPath();
        ctx1.arc(positionX, positionY, size, 0, 2 * Math.PI);
        ctx1.fill();
      }

      break;
    }
    case "gomme":
    {
      var c2 = document.getElementById("canvas2");
      var ctx2 = c2.getContext("2d");
      ctx2.clearRect(0, 0, c2.width, c2.height);
      ctx2.strokeStyle = 'black';
      ctx2.beginPath();
      ctx2.strokeRect(positionX, positionY, size*2, size*2);

      if (buttonPressed)
      {
        var c1 = document.getElementById("canvas1");
        var ctx1 = c1.getContext("2d");
        ctx1.beginPath();
        ctx1.clearRect(positionX, positionY, size*2, size*2);
      }

      break;
    }
    case "trait":
    {
      var c2 = document.getElementById("canvas2");
      var ctx2 = c2.getContext("2d");
      ctx2.clearRect(0, 0, c2.width, c2.height);
      ctx2.lineWidth = 1;
      ctx2.fillStyle="white";
      ctx2.beginPath();
      ctx2.arc(positionX, positionY, size, 0, 2 * Math.PI);
      ctx2.fill();

      if (buttonPressed)
      {
        if(!fixed)
        {
          positionFixeX = positionX;
          positionFixeY = positionY;
          fixed = true;
        }

        c2 = document.getElementById("canvas2");
        ctx2 = c2.getContext("2d");
        ctx2.strokeStyle = 'white';
        ctx2.beginPath();
        ctx2.lineWidth = size;
        ctx2.moveTo(positionFixeX, positionFixeY);
        ctx2.lineTo(positionX, positionY);
        ctx2.stroke();
      }

      if (!buttonPressed && fixed)
      {
        var c1 = document.getElementById("canvas1");
        var ctx1 = c1.getContext("2d");
        ctx1.strokeStyle = 'white';
        ctx1.beginPath();
        ctx1.lineWidth = size;
        ctx1.moveTo(positionFixeX, positionFixeY);
        ctx1.lineTo(positionX, positionY);
        ctx1.stroke();
        fixed = false;
      }

      break;
    }
    case "rectangle":
    {
      var c2 = document.getElementById("canvas2");
      var ctx2 = c2.getContext("2d");
      ctx2.clearRect(0, 0, c2.width, c2.height);
      ctx2.fillStyle="white";
      ctx2.beginPath();
      ctx2.fillRect(positionX, positionY, size*2, size*2);

      if (buttonPressed)
      {
        if(!fixed)
        {
          positionFixeX = positionX;
          positionFixeY = positionY;
          fixed = true;
        }

        c2 = document.getElementById("canvas2");
        ctx2 = c2.getContext("2d");
        ctx2.fillStyle="white";
        ctx2.beginPath();
        sizeX = positionX - positionFixeX;
        sizeY = positionY - positionFixeY;
        ctx2.fillRect(positionFixeX, positionFixeY, sizeX, sizeY);
      }

      if (!buttonPressed && fixed)
      {
        var c1 = document.getElementById("canvas1");
        var ctx1 = c1.getContext("2d");
        ctx1.fillStyle="white";
        ctx1.beginPath();
        ctx1.fillRect(positionFixeX, positionFixeY, sizeX, sizeY);
        fixed = false;
      }

      break;
    }
    default:
      break;
  }
}

function getPinceau()
{
  removeShadow();
  document.getElementById("pinceau").style.cssText = "box-shadow: 1px 1px 12px blue;";
  tool = "pinceau";
}

function getGomme()
{
  removeShadow();
  document.getElementById("gomme").style.cssText = "box-shadow: 1px 1px 12px blue;";
  tool = "gomme";
}

function getTrait()
{
  removeShadow();
  document.getElementById("trait").style.cssText = "box-shadow: 1px 1px 12px blue;";
  tool = "trait";
}

function getRectangle()
{
  removeShadow();
  document.getElementById("rectangle").style.cssText = "box-shadow: 1px 1px 12px blue;";
  tool = "rectangle";
}

function getSize()
{
  size = document.getElementById("size").value;
}

function getNouveau()
{
  var c1 = document.getElementById("canvas1");
  var ctx1 = c1.getContext("2d");
  ctx1.clearRect(0, 0, c1.width, c1.height);
}

function getOuvrir()
{
  var myNode = document.getElementById("images");
  while (myNode.firstChild) {myNode.removeChild(myNode.firstChild);}

  var divImage = document.getElementById("images");
  for(var i = 0; i < localStorage.length; ++i)
  {
    var div = document.createElement("div");
    var p = document.createElement("p");
    p.innerHTML = localStorage.key(i);
    p.setAttribute('style', "display:inline-block;");
    var img = document.createElement("img");
    img.src = localStorage.getItem(localStorage.key(i));
    img.setAttribute('onclick', "chargerImage('"+ localStorage.getItem(localStorage.key(i))+"')");
    img.setAttribute('style', "border: 1px solid black; display:inline-block;");
    var icon = document.createElement("img");
    icon.setAttribute('src', '../images/icone-supprimer.png');
    icon.setAttribute('onclick', "removeImageSaved('"+localStorage.key(i)+"',this)");
    icon.setAttribute('style', "display:inline-block; width:25px; height:25px;");
    div.appendChild(p);
    div.appendChild(img);
    div.appendChild(icon);
    divImage.appendChild(div);
  }

  document.getElementById('selectionnerImage').setAttribute("style", "display:block");
}

function getEnregistrer()
{
  var dataURL = document.getElementById("canvas1").toDataURL();
  var name = prompt("Please enter a name");
  if (name != null)
  {
    localStorage.setItem(name, dataURL);
  }
}

function removeShadow()
{
    document.getElementById("pinceau").style.cssText = "box-shadow: 0px 0px 0px black;";
    document.getElementById("gomme").style.cssText = "box-shadow: 0px 0px 0px black;";
    document.getElementById("trait").style.cssText = "box-shadow: 0px 0px 0px black;";
    document.getElementById("rectangle").style.cssText = "box-shadow: 0px 0px 0px black;";
}

function removeImageSaved(key, node)
{
  localStorage.removeItem(key);
  node.parentNode.remove();
}

function getOuvrirClose()
{
  document.getElementById('selectionnerImage').setAttribute("style", "display:none");
}

function chargerImage(dataURL)
{
  getNouveau();

  var c1 = document.getElementById("canvas1");
  var ctx1 = c1.getContext("2d");
  var imageObj = new Image();
  imageObj.onload = function() {
    ctx1.drawImage(this, 0, 0);
  };

  imageObj.src = dataURL;

  document.getElementById('selectionnerImage').setAttribute("style", "display:none");
}
