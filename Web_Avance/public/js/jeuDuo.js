function startGame()
{
  var divInstructionBlue = document.getElementById("instructionBlue");
  var divInstructionRed = document.getElementById("instructionRed");
  for(var i = 0; i < 5; ++i)
  {
    var divBlue = document.createElement("div");
    divBlue.setAttribute('id', "divInstructionBlue"+i);
    var imgBlue = document.createElement("img");
    imgBlue.src = "../images/block-vide-bleu.png"
    imgBlue.setAttribute('style', "width:100%;");
    divBlue.appendChild(imgBlue);

    var divRed = document.createElement("div");
    divRed.setAttribute('id', "divInstructionRed"+i);
    var imgRed = document.createElement("img");
    imgRed.src = "../images/block-vide-rouge.png"
    imgRed.setAttribute('style', "width:100%;");
    divRed.appendChild(imgRed);

    var divNumber = document.createElement("div");
    divNumber.innerHTML = ""+i;
    divNumber.setAttribute('id', "centered");

    divBlue.appendChild(divNumber);
    divRed.appendChild(divNumber);

    divInstructionBlue.appendChild(divBlue);
    divInstructionRed.appendChild(divRed);
  }
}

function board()
{
  var divBoard = document.getElementById("board");
  for(var i = 0; i < 9; ++i)
  {
    for(var j = 0; j < 9; ++j)
    {
      var tile = document.createElement("div");
      tile.setAttribute('id', "tile"+i+j);
      tile.setAttribute('style', "width:70px; height:70px; display: inline-block; background-color:lightgrey; border: 1px solid gray; margin-bottom: -5px;");
      divBoard.appendChild(tile);
    }
  }
}
