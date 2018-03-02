var c = null;
var ctx = null;

var left_canvas = null;
var left_context = null;

var right_canvas = null;
var right_context = null;

var score_canvas = null;
var score_context = null;

var popOpen = false;
var popUpWindow = null;

var displayIndex;
var x2alreadyDrwn = false;

var sizeBoard = 675;
var rectWidth = 150;
var rectHeight = 675;
var scoreWidth = 675;
var scoreHeight = 50;
var scoreSizeFont = 20;
var sizeImg = 80;
var ecartImg = 32;
var sizeFont = 60;
var baseImgX = 35;
var baseImgY = 16;
var baseTextX = 75;
var baseTextY = 76;

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
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.fillRect(sizeBoard/9 * positionX, sizeBoard/9 * positionY, sizeBoard/9, sizeBoard/9);
  }

  function createLine(color, width, positionX1, positionY1, positionX2, positionY2)
  {
    ctx.strokeStyle = color;
    ctx.beginPath();
    ctx.lineWidth = width;
    ctx.moveTo(positionX1 * sizeBoard/9, positionY1 * sizeBoard/9);
    ctx.lineTo(positionX2 * sizeBoard/9, positionY2 * sizeBoard/9);
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
  left_context.fillStyle="#F1885C";
  left_context.fillRect(0, 0, rectWidth, rectHeight);
  left_context.fillStyle="white";
  left_context.textAlign="center";
  left_context.font = sizeFont+"px Courier New";

  //imgs
  for (var i = 0; i < 6; i++) {
    drawLeftInstruction(i);
  }

}

function drawLeftInstruction(index){
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
      left_context.drawImage(icon, baseImgX, baseImgY + index*(ecartImg+sizeImg), sizeImg, sizeImg);
      left_context.fillText(index,baseTextX, baseTextY + index*(ecartImg+sizeImg));
    }
    icon.src = "../images/block-vide-rouge.png";
  }
}

function drawRightCanvas(){
  //Background
  right_context.fillStyle="#B3D6E4";
  right_context.fillRect(0, 0, rectWidth, rectHeight);
  right_context.fillStyle="white";
  right_context.textAlign="center";
  right_context.font = sizeFont+"px Courier New";

  //imgs
  for (var i = 0; i < 6; i++) {
    drawRightInstruction(i);
  }

}

function drawRightInstruction(index){
  if(index == 0){
    var icon = new Image();
    icon.onload = function() {
      right_context.drawImage(icon, baseImgX, baseImgY, sizeImg, sizeImg);
      right_context.fillText("LD",baseTextX,baseTextY);
    }
    icon.src = "../images/block-vide-bleu.png";
  }else{
    var icon = new Image();
    icon.onload = function() {
      right_context.drawImage(icon, baseImgX, baseImgY + index*(ecartImg+sizeImg), sizeImg, sizeImg);
      right_context.fillText(index,baseTextX, baseTextY + index*(ecartImg+sizeImg));
    }
    icon.src = "../images/block-vide-bleu.png";
  }
}

function drawScoreCanvas(){
  //Background
  score_context.fillStyle="#efbbff";
  score_context.fillRect(0, 0, scoreWidth, scoreHeight);
}


function drawSelectedInstruction(colour, index, instructionName, newWindow) {
  var icon = new Image();

  if (colour == "bleu")
    icon.onload = function() {
      right_context.drawImage(icon, baseImgX, baseImgY + (displayIndex-1)*(ecartImg+sizeImg), sizeImg, sizeImg);
    }
  else if (colour == "rouge")
    icon.onload = function() {
      left_context.drawImage(icon, baseImgX, baseImgY + (displayIndex-1)*(ecartImg+sizeImg), sizeImg, sizeImg);
    }


  icon.src = "../images/" + instructionName + "-" + colour + ".png";
  newWindow.document.title = "Choose next instruction : ";
  addInstructionToArray(colour, instructionName);
  newWindow.document.getElementById(instructionName).style.filter = "grayscale(100%)";
  newWindow.document.getElementById(instructionName).setAttribute('onclick', 'return false;');
  newWindow.document.getElementById(instructionName).onclick = function() {return false;};

  if(displayIndex  >= 1 && x2alreadyDrwn == false){
    x2x2alreadyDrwn = true;
    var x2 = newWindow.document.createElement("img");
    x2.setAttribute("id", "x2");
    x2.setAttribute("src", "http://localhost/Web_Avance/public/images/x2-"+colour+".png");
    x2.setAttribute("height", "70");
    x2.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(x2);
    x2.setAttribute('onclick', 'drawSelectedInstruction(colour, index+1, "x2", newWindow); displayIndex ++;');
    x2.onclick = function() {drawSelectedInstruction(colour, index+1, "x2", newWindow); displayIndex ++;};
  }

  if(displayIndex + 1 == 6){
    newWindow.close();
    popOpen = false;
    popUpWindow = null;
  }

}

function addInstructionToArray(colour, instructionName)
{close
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

function eraseInstruction(colour)
{
  if (colour == "bleu")
  {
    instructionArrayBlue=[];
    drawRightCanvas();
  }
  else if (colour == "rouge")
  {
    instructionArrayRed=[];
    drawLeftCanvas();
  }
}

function PopupCenter(w, h, colour) {

  if(popOpen){
    if (window.focus)
    {
      popUpWindow.focus();
    }
  }


  var validated = 0;

  displayIndex = 1;

  if(colour == "rouge"){
    displayIndex = instructionArrayRed.length + 1;
  }else if(colour == "bleu"){
    displayIndex = instructionArrayBlue.length + 1;
  }
  if(displayIndex == 6){
    displayIndex = 1;
  }

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
  newWindow.document.title = "Choose next instruction :";

  if(!popOpen)
  {

    var annuler = newWindow.document.createElement("img");
    annuler.setAttribute("id", "annuler");
    annuler.setAttribute("src", "http://localhost/Web_Avance/public/images/annuler-"+colour+".png");
    annuler.setAttribute("height", "70");
    annuler.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(annuler);
    annuler.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "annuler", newWindow); displayIndex ++;');
    annuler.onclick = function() {drawSelectedInstruction(colour, index, "annuler", newWindow);displayIndex ++;};

    var deposer = newWindow.document.createElement("img");
    deposer.setAttribute("id", "deposer");
    deposer.setAttribute("src", "http://localhost/Web_Avance/public/images/deposer-"+colour+".png");
    deposer.setAttribute("height", "70");
    deposer.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(deposer);
    deposer.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "deposer", newWindow); displayIndex ++;');
    deposer.onclick = function() {drawSelectedInstruction(colour, index, "deposer", newWindow);displayIndex ++;};

    var est = newWindow.document.createElement("img");
    est.setAttribute("id", "est");
    est.setAttribute("src", "http://localhost/Web_Avance/public/images/est-"+colour+".png");
    est.setAttribute("height", "70");
    est.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(est);
    est.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "est", newWindow); displayIndex ++;');
    est.onclick = function() {drawSelectedInstruction(colour, index, "est", newWindow);displayIndex ++;};

    var nord = newWindow.document.createElement("img");
    nord.setAttribute("id", "nord");
    nord.setAttribute("src", "http://localhost/Web_Avance/public/images/nord-"+colour+".png");
    nord.setAttribute("height", "70");
    nord.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(nord);
    nord.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "nord", newWindow); displayIndex ++;');
    nord.onclick = function() {drawSelectedInstruction(colour, index, "nord", newWindow);displayIndex ++;};

    var ouest = newWindow.document.createElement("img");
    ouest.setAttribute("id", "ouest");
    ouest.setAttribute("src", "http://localhost/Web_Avance/public/images/ouest-"+colour+".png");
    ouest.setAttribute("height", "70");
    ouest.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(ouest);
    ouest.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "ouest", newWindow); displayIndex ++;');
    ouest.onclick = function() {drawSelectedInstruction(colour, index, "ouest", newWindow);displayIndex ++;};

    var pause = newWindow.document.createElement("img");
    pause.setAttribute("id", "pause");
    pause.setAttribute("src", "http://localhost/Web_Avance/public/images/pause-"+colour+".png");
    pause.setAttribute("height", "70");
    pause.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(pause);
    pause.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "pause", newWindow); displayIndex ++;');
    pause.onclick = function() {drawSelectedInstruction(colour, index, "pause", newWindow);displayIndex ++;};


    var prendre = newWindow.document.createElement("img");
    prendre.setAttribute("id", "prendre");
    prendre.setAttribute("src", "http://localhost/Web_Avance/public/images/prendre-"+colour+".png");
    prendre.setAttribute("height", "70");
    prendre.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(prendre);
    prendre.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "prendre", newWindow); displayIndex ++;');
    prendre.onclick = function() {drawSelectedInstruction(colour, index, "prendre", newWindow);displayIndex ++;};

    var repousser = newWindow.document.createElement("img");
    repousser.setAttribute("id", "repousser");
    repousser.setAttribute("src", "http://localhost/Web_Avance/public/images/repousser-"+colour+".png");
    repousser.setAttribute("height", "70");
    repousser.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(repousser);
    repousser.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "repousser", newWindow); displayIndex ++;');
    repousser.onclick = function() {drawSelectedInstruction(colour, index, "repousser", newWindow);displayIndex ++;};

    var sud = newWindow.document.createElement("img");
    sud.setAttribute("id", "sud");
    sud.setAttribute("src", "http://localhost/Web_Avance/public/images/sud-"+colour+".png");
    sud.setAttribute("height", "70");
    sud.setAttribute("width", "70");
    newWindow.document.getElementsByTagName("body")[0].appendChild(sud);
    sud.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "sud", newWindow); displayIndex ++;');
    sud.onclick = function() {drawSelectedInstruction(colour, index, "sud", newWindow);displayIndex ++;}


    if(colour == "rouge")
    {
      var est_x2 = newWindow.document.createElement("img");
      est_x2.setAttribute("id", "est_x2");
      est_x2.setAttribute("src", "http://localhost/Web_Avance/public/images/est_x2-"+colour+".png");
      est_x2.setAttribute("height", "70");
      est_x2.setAttribute("width", "70");
      newWindow.document.getElementsByTagName("body")[0].appendChild(est_x2);
      est_x2.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "est_x2", newWindow); displayIndex ++;');
      est_x2.onclick = function() {drawSelectedInstruction(colour, index, "est_x2", newWindow);displayIndex ++;};
    }else if(colour == "bleu")
    {
      var ouest_x2 = newWindow.document.createElement("img");
      ouest_x2.setAttribute("id", "ouest_x2");
      ouest_x2.setAttribute("src", "http://localhost/Web_Avance/public/images/ouest_x2-"+colour+".png");
      ouest_x2.setAttribute("height", "70");
      ouest_x2.setAttribute("width", "70");
      newWindow.document.getElementsByTagName("body")[0].appendChild(ouest_x2);
      ouest_x2.setAttribute('onclick', 'drawSelectedInstruction(colour, index, "ouest_x2", newWindow); displayIndex ++;');
      ouest_x2.onclick = function() {drawSelectedInstruction(colour, index, "ouest_x2", newWindow);displayIndex ++;};
    }
  }

  popOpen = true;
  popUpWindow = newWindow;

  newWindow.onbeforeunload = function(){
   popOpen = false;
   popUpWindow = null;
 }

}


function flashyText(text) {

  drawScoreCanvas();

  score_context.font = scoreSizeFont+"px Courier New";
  score_context.fillStyle = "#660066";
  score_context.textAlign = "center";
  score_context.fillText(text, score_canvas.width/2, score_canvas.height/2+5);
}

function resize()
{
    var coef = 1;
    if(window.innerWidth > 1400)
      coef = 1080/1400;
    else
      coef = 1080/window.innerWidth;

    sizeBoard = 675/coef;
    rectWidth = 150/coef;
    rectHeight = 675/coef;
    scoreWidth = 675/coef;
    scoreHeight = 50/coef;
    scoreSizeFont = 20/coef;
    sizeImg = 80/coef;
    ecartImg = 32/coef;
    sizeFont = 60/coef;
    baseImgX = 35/coef;
    baseImgY = 16/coef;
    baseTextX = 75/coef;
    baseTextY = 76/coef;

    c.width = sizeBoard;
    c.height = sizeBoard;
    left_canvas.width = rectWidth;
    left_canvas.height = rectHeight;
    right_canvas.width = rectWidth;
    right_canvas.height = rectHeight;
    score_canvas.width = scoreWidth;
    score_canvas.height = scoreHeight;
    drawLeftCanvas();
    drawRightCanvas();
    drawScoreCanvas();

    var game = document.getElementById("game");
    var title = document.getElementById("title");
    game.setAttribute("style", "margin: 0 auto; width: "+(c.width+left_canvas.width+right_canvas.width+10+12)+"px;");
    title.setAttribute("style", "margin: 0 auto; width: "+(score_canvas.width+4)+"px;");
}

function init()
{
  c = document.getElementById("board");
  ctx = c.getContext("2d");

  left_canvas = document.getElementById('left_canvas');
  left_context = left_canvas.getContext('2d');

  right_canvas = document.getElementById('right_canvas');
  right_context = right_canvas.getContext('2d');

  score_canvas = document.getElementById('score_canvas');
  score_context = score_canvas.getContext('2d');

  drawLeftCanvas();
  drawRightCanvas();
  drawScoreCanvas();
  resize();

  left_canvas.addEventListener("click", function(){ PopupCenter(800, 200, "rouge"); }, false);
  right_canvas.addEventListener("click", function(){ PopupCenter(800, 200, "bleu"); }, false);
  window.addEventListener("resize", resize);
}
