var buttonPressed = false;
var positionX = 0;
var positionY = 0;
var size = 5;

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
}

function draw()
{
  if (buttonPressed)
  {
    var c = document.getElementById("canvas2");
    var ctx = c.getContext("2d");
    ctx.fillStyle="white";
    ctx.beginPath();
    ctx.arc(positionX, positionY, size, 0, 2 * Math.PI);
    ctx.fill();
  }
}

function getSizeOfCircle() {
    size = document.getElementById("circleSize").value;
}
