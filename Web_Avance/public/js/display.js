var left_canvas = null;
var left_context = null;

var right_canvas = null;
var right_context = null;

var rectX = 0;
var rectY = 0;
var rectWidth = 140;
var rectHeight = 675;
var cornerRadius = 8;

var instructionArrayBlue = [];
var instructionArrayRed = [];

function clear()
{
  var c = document.getElementById("board");
  var ctx = c.getContext("2d");
  ctx.clearRect(0, 0, c.width, c.height);
}

function drawBoard()
{
  function createSquare(color, positionX, positionY)
  {
      var c = document.getElementById("board");
      var ctx = c.getContext("2d");
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.fillRect(75 * positionX, 75 * positionY, 75, 75);
  }

  function createLine(color, width, positionX1, positionY1, positionX2, positionY2)
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.strokeStyle = color;
    ctx.beginPath();
    ctx.lineWidth = width;
    ctx.moveTo(positionX1 * 75, positionY1 * 75);
    ctx.lineTo(positionX2 * 75, positionY2 * 75);
    ctx.stroke();
  }


  // rectangle red
  for(var i = 3; i < 6; ++i)
    createSquare("#ffaaaa", 0, i)
  createSquare("#ffaaaa", 1, 4)

  // rectangle blue
  for(var i = 3; i < 6; ++i)
    createSquare("#aaaaff", 8, i)
  createSquare("#aaaaff", 7, 4)

  // rectangle vert haut
  for(var i = 3; i < 6; ++i)
    createSquare("#aaffaa", i, 0)
  createSquare("#aaffaa", 4, 1)

  // rectangle vert bas
  for(var i = 3; i < 6; ++i)
    createSquare("#aaffaa", i, 8)
  createSquare("#aaffaa", 4, 7)

  // quadrillage
  for(var i = 1; i < 9; ++i)
  {
    createLine("gray", 2, 0, i, 9, i);
    createLine("gray", 2, i, 0, i, 9);
  }
}

function drawLeftCanvas(){
  //Background
  left_context.lineJoin = "round";
  left_context.strokeStyle = "#0000000";
  left_context.fillStyle="#F1885C";
  left_context.lineWidth = cornerRadius;
  left_context.strokeRect(rectX+(cornerRadius/2), rectY+(cornerRadius/2), rectWidth-cornerRadius, rectHeight-cornerRadius);
  left_context.fillRect(rectX+(cornerRadius/2), rectY+(cornerRadius/2), rectWidth-cornerRadius, rectHeight-cornerRadius);
  left_context.fillStyle="white";
  left_context.textAlign="center";
  left_context.font = "60px Courier New";

  //imgs
  for (var i = 0; i < 6; i++) {
    drawLeftInstruction(i);
  }

}

function drawLeftInstruction(index){
  var sizeImg = 80;
  var baseImgX = 30;
  var baseImgY = 16;
  var baseTextX = 70;
  var baseTextY = 76;

  if(index == 0){
    var icon = new Image();
    icon.onload = function() {
      left_context.drawImage(icon, baseImgX, baseImgY, sizeImg, sizeImg);
      left_context.fillText("RD",baseTextX,baseTextY);
    }
    icon.src = "../images/block-vide-rouge.png";
  }else{
    var icon = new Image();
    icon.onload = function() {
      left_context.drawImage(icon, baseImgX, baseImgY + index*(32+sizeImg), sizeImg, sizeImg);
      left_context.fillText(index,baseTextX, baseTextY + index*(32+sizeImg));
    }
    icon.src = "../images/block-vide-rouge.png";
  }
}

function drawRightCanvas(){
  //Background
  right_context.lineJoin = "round";
  right_context.strokeStyle = "#0000000";
  right_context.fillStyle="#B3D6E4";
  right_context.lineWidth = cornerRadius;
  right_context.strokeRect(rectX+(cornerRadius/2), rectY+(cornerRadius/2), rectWidth-cornerRadius, rectHeight-cornerRadius);
  right_context.fillRect(rectX+(cornerRadius/2), rectY+(cornerRadius/2), rectWidth-cornerRadius, rectHeight-cornerRadius);
  right_context.fillStyle="white";
  right_context.textAlign="center";
  right_context.font = "60px Courier New";

  //imgs
  for (var i = 0; i < 6; i++) {
    drawRightInstruction(i);
  }

}

function drawRightInstruction(index){
  var sizeImg = 80;
  var baseImgX = 30;
  var baseImgY = 16;
  var baseTextX = 70;
  var baseTextY = 76;

  if(index == 0){
    var icon = new Image();
    icon.onload = function() {
      right_context.drawImage(icon, baseImgX, baseImgY, sizeImg, sizeImg);
      right_context.fillText("RD",baseTextX,baseTextY);
    }
    icon.src = "../images/block-vide-bleu.png";
  }else{
    var icon = new Image();
    icon.onload = function() {
      right_context.drawImage(icon, baseImgX, baseImgY + index*(32+sizeImg), sizeImg, sizeImg);
      right_context.fillText(index,baseTextX, baseTextY + index*(32+sizeImg));
    }
    icon.src = "../images/block-vide-bleu.png";
  }
}


function drawSelectedInstruction(colour, index, instructionName, newWindow) {
  var sizeImg = 80;
  var baseImgX = 30;
  var baseImgY = 16;
  var baseTextX = 70;
  var baseTextY = 76;
  var icon = new Image();
  if (colour == "bleu")
    icon.onload = function() {
      right_context.drawImage(icon, baseImgX, baseImgY + index*(32+sizeImg), sizeImg, sizeImg);
    }
  else if (colour == "rouge")
    icon.onload = function() {
      left_context.drawImage(icon, baseImgX, baseImgY + index*(32+sizeImg), sizeImg, sizeImg);
    }


  icon.src = "../images/" + instructionName + "-" + colour + ".png";
  newWindow.document.title = "Choose instruction " + (index+1);
  addInstructionToArray(colour, instructionName);
  newWindow.document.getElementById(instructionName).style.filter = "grayscale(100%)";
  newWindow.document.getElementById(instructionName).setAttribute('onclick', 'return false;');
  newWindow.document.getElementById(instructionName).onclick = function() {return false;};

  if(index + 1 == 6){
    newWindow.close();
  }

}

function addInstructionToArray(colour, instructionName)
{
  if (colour == "bleu")
    instructionArrayBlue.push(instructionName);
  else if (colour == "rouge")
    instructionArrayRed.push(instructionName);
}

function getInstructionArray(colour)
{
  if (colour == "bleu")
    return instructionArrayBlue;
  else if (colour == "rouge")
    return instructionArrayRed;
}

function eraseInstruction()
{
  instructionArrayBlue=[];
  instructionArrayRed=[];
}

function PopupCenter(w, h, colour) {
  var validated = 0;
  var index = 1;
    // Fixes dual-screen position                         Most browsers      Firefox
  var dualScreenLeft = window.screenLeft != undefined ? window.screenLeft : screen.left;
  var dualScreenTop = window.screenTop != undefined ? window.screenTop : screen.top;

  var width = window.innerWidth ? window.innerWidth : document.documentElement.clientWidth ? document.documentElement.clientWidth : screen.width;
  var height = window.innerHeight ? window.innerHeight : document.documentElement.clientHeight ? document.documentElement.clientHeight : screen.height;

  var left = ((width / 2) - (w / 2)) + dualScreenLeft;
  var top = ((height / 2) - (h / 2)) + dualScreenTop;
  var newWindow = window.open("", "Test", 'resizable=no, scrollbars=yes, width=' + w + ', height=' + h + ', top=' + top + ', left=' + left, );

  // Puts focus on the newWindow
  if (window.focus)
  {
    newWindow.focus();
  }
  newWindow.document.title = "Choose instruction " + (validated + 1);

  var annuler = newWindow.document.createElement("img");
  annuler.setAttribute("id", "annuler");
  annuler.setAttribute("src", "http://localhost/Web_Avance/public/images/annuler-"+colour+".png");
  annuler.setAttribute("height", "70");
  annuler.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(annuler);
  annuler.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "annuler", newWindow); index ++;');
  annuler.onclick = function() {drawSelectedInstruction(colour, index, "annuler", newWindow);index ++;};

  var deposer = newWindow.document.createElement("img");
  deposer.setAttribute("id", "deposer");
  deposer.setAttribute("src", "http://localhost/Web_Avance/public/images/deposer-"+colour+".png");
  deposer.setAttribute("height", "70");
  deposer.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(deposer);
  deposer.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "deposer", newWindow); index ++;');
  deposer.onclick = function() {drawSelectedInstruction(colour, index, "deposer", newWindow);index ++;};

  var est = newWindow.document.createElement("img");
  est.setAttribute("id", "est");
  est.setAttribute("src", "http://localhost/Web_Avance/public/images/est-"+colour+".png");
  est.setAttribute("height", "70");
  est.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(est);
  est.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "est", newWindow); index ++;');
  est.onclick = function() {drawSelectedInstruction(colour, index, "est", newWindow);index ++;};

  var nord = newWindow.document.createElement("img");
  nord.setAttribute("id", "nord");
  nord.setAttribute("src", "http://localhost/Web_Avance/public/images/nord-"+colour+".png");
  nord.setAttribute("height", "70");
  nord.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(nord);
  nord.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "nord", newWindow); index ++;');
  nord.onclick = function() {drawSelectedInstruction(colour, index, "nord", newWindow);index ++;};

  var ouest = newWindow.document.createElement("img");
  ouest.setAttribute("id", "ouest");
  ouest.setAttribute("src", "http://localhost/Web_Avance/public/images/ouest-"+colour+".png");
  ouest.setAttribute("height", "70");
  ouest.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(ouest);
  ouest.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "ouest", newWindow); index ++;');
  ouest.onclick = function() {drawSelectedInstruction(colour, index, "ouest", newWindow);index ++;};

  var pause = newWindow.document.createElement("img");
  pause.setAttribute("id", "pause");
  pause.setAttribute("src", "http://localhost/Web_Avance/public/images/pause-"+colour+".png");
  pause.setAttribute("height", "70");
  pause.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(pause);
  pause.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "pause", newWindow); index ++;');
  pause.onclick = function() {drawSelectedInstruction(colour, index, "pause", newWindow);index ++;};


  var prendre = newWindow.document.createElement("img");
  prendre.setAttribute("id", "prendre");
  prendre.setAttribute("src", "http://localhost/Web_Avance/public/images/prendre-"+colour+".png");
  prendre.setAttribute("height", "70");
  prendre.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(prendre);
  prendre.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "prendre", newWindow); index ++;');
  prendre.onclick = function() {drawSelectedInstruction(colour, index, "prendre", newWindow);index ++;};

  var repousser = newWindow.document.createElement("img");
  repousser.setAttribute("id", "repousser");
  repousser.setAttribute("src", "http://localhost/Web_Avance/public/images/repousser-"+colour+".png");
  repousser.setAttribute("height", "70");
  repousser.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(repousser);
  repousser.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "repousser", newWindow); index ++;');
  repousser.onclick = function() {drawSelectedInstruction(colour, index, "repousser", newWindow);index ++;};

  var sud = newWindow.document.createElement("img");
  sud.setAttribute("id", "sud");
  sud.setAttribute("src", "http://localhost/Web_Avance/public/images/sud-"+colour+".png");
  sud.setAttribute("height", "70");
  sud.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(sud);
  sud.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "sud", newWindow); index ++;');
  sud.onclick = function() {drawSelectedInstruction(colour, index, "sud", newWindow);index ++;};

  var x2 = newWindow.document.createElement("img");
  x2.setAttribute("id", "x2");
  x2.setAttribute("src", "http://localhost/Web_Avance/public/images/x2-"+colour+".png");
  x2.setAttribute("height", "70");
  x2.setAttribute("width", "70");
  newWindow.document.getElementsByTagName("body")[0].appendChild(x2);
  x2.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "x2", newWindow); index ++;');
  x2.onclick = function() {drawSelectedInstruction(colour, index, "x2", newWindow);index ++;};

}

function init()
{
  left_canvas = document.getElementById('left_canvas');
  left_context = left_canvas.getContext('2d');

  right_canvas = document.getElementById('right_canvas');
  right_context = right_canvas.getContext('2d');

  drawLeftCanvas();
  drawRightCanvas();

  left_canvas.addEventListener("click", function(){ PopupCenter(800, 200, "rouge"); }, false);
  right_canvas.addEventListener("click", function(){ PopupCenter(800, 200, "bleu"); }, false);
}
