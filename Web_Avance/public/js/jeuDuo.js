class Player
{
  constructor(name, color, icon)
  {
    this.name = name;
    this.color = color;
    this.icon = icon;
    this.robot = null;

    this.instructionArray = [];
    this.popUpIsOpen = false;

    if (this.color == "rouge")
      if (Math.floor(Math.random() * Math.floor(4)) != 0)
        this.robot = new Robot(this.color, 0, 3 + Math.floor(Math.random() * Math.floor(3)), 0);
      else
        this.robot = new Robot(this.color, 1, 4, 0);
    else if (this.color == "bleu")
      if (Math.floor(Math.random() * Math.floor(4)) != 0)
        this.robot = new Robot(this.color, 8, 3 + Math.floor(Math.random() * Math.floor(3)), 180);
      else
        this.robot = new Robot(this.color, 7, 4, 180);
  }

  getRobot()
  {
    return this.robot;
  }
}

class Robot
{
  constructor(color, positionX, positionY, orientation)
  {
    this.color = color;
    this.positionX = positionX;
    this.positionY = positionY;
    this.orientation = orientation;

    this.destinationPositionX = this.positionX;
    this.destinationPositionY = this.positionY;
    this.destinationOrientation = this.orientation;

    this.flag = null;

    this.imgRobot = new Image();
    this.imgWheel = new Image();
    this.imgRobot.src = "../images/robot-corps-"+ this.color +".png";
    this.imgWheel.src = "../images/robot-chenilles.png";
  }

  update()
  {
    //change orientation
    if (this.destinationOrientation != this.orientation)
    {
      this.orientation += this.destinationOrientation - this.orientation > 0 ? 1 : -1;

      if (this.destinationOrientation == this.orientation && this.orientation == 360)
      {
          this.orientation = 0;
          this.destinationOrientation = 0;
      }
    }

    //change position
    if (this.destinationOrientation == this.orientation)
    {
      if(this.destinationPositionX > this.positionX)
        this.positionX+= 1 * 0.02;
      if(this.destinationPositionX < this.positionX)
        this.positionX-= 1 * 0.02;
      if(this.destinationPositionY > this.positionY)
        this.positionY+= 1 * 0.02;
      if(this.destinationPositionY < this.positionY)
        this.positionY-= 1 * 0.02;

      // change position of flag if the robot carry a flag
      if(this.flag != null)
        this.flag.setPosition(this.positionX, this.positionY);
    }
  }

  draw()
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.save();
    ctx.translate((this.positionX * 75 + 10 + 55/2), (this.positionY * 75 + 20 + 35/2));
    ctx.rotate(Math.PI / 180 * this.orientation);
    ctx.translate(-(this.positionX * 75 + 20 + 35/2), -(this.positionY * 75 + 10 + 55/2));
    ctx.drawImage(this.imgWheel, this.positionX * 75 + 20, this.positionY * 75 + 10, 35, 55);
    ctx.drawImage(this.imgRobot, this.positionX * 75 + 10, this.positionY * 75 + 20, 55, 35);
    ctx.restore();
  }

  executeInstruction(instruction, robot, flagArray)
  {
    switch(instruction)
    {
      case "nord":
      {
        this.destinationOrientation = 270;
        this.destinationPositionY-= (this.destinationPositionY > 0  && this.destinationPositionY-1 != robot.positionY) ? 1 : 0;
        break;
      }
      case "sud":
      {
        this.destinationOrientation = 90;
        this.destinationPositionY+= (this.destinationPositionY < 8  && this.destinationPositionY+1 != robot.positionY) ? 1 : 0;
        break;
      }
      case "est":
      {
        this.destinationOrientation = 180;
        this.destinationPositionX-= (this.destinationPositionX > 0  && this.destinationPositionX-1 != robot.positionX) ? 1 : 0;
        break;
      }
      case "ouest":
      {
        this.destinationOrientation = this.orientation > 180 ? 360: 0;
        this.destinationPositionX+= (this.destinationPositionX < 8 && this.destinationPositionX+1 != robot.positionX) ? 1 : 0;
        break;
      }
      case "prendre":
      {
        for (var i = 0; i < flagArray.length; ++i)
          if(this.flag == null && flagArray[i].positionX == positionX && flagArray[i].positionY == positionY && flagArray[i].color == color)
            this.flag = flagArray[i];
        break;
      }
      case "deposer":
      {
        var canDrop = true;
        for (var i = 0; i < flagArray.length; ++i)
          if(this.flag != null && flagArray[i].positionX == this.flag.positionX && flagArray[i].positionY == this.flag.positionY)
            canDrop = false;

        if(canDrop)
          this.flag = null;
        break;
      }
      case "repousser":
      {
        if (this.color == "red")
          this.destinationPositionX-= (this.destinationPositionX > 0  && this.destinationPositionX-1 != robot.positionX) ? 1 : 0;
        else if (this.color == "blue")
          this.destinationPositionX+= (this.destinationPositionX < 8 && this.destinationPositionX+1 != robot.positionX) ? 1 : 0;
        break;
      }
      case "annuler":
      {
        break;
      }
      case "pause":
      {
        break;
      }
      default:
        break;
    }
  }
}

class Flag
{
  constructor(positionX, positionY)
  {
    this.positionX = positionX;
    this.positionY = positionY;

    this.img = new Image();
    this.color = '';
  }

  setPosition(positionX, positionY)
  {
    this.positionX = positionX;
    this.positionY = positionY;
  }

  setColor(color)
  {
    this.color = color;
    this.img.src = "../images/flag-" + this.color + ".png";
  }

  draw()
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.drawImage(this.img, this.positionX * 75 + 10, this.positionY * 75 + 10, 55, 55);
  }
}

class Instruction
{
  constructor(name)
  {
    this.name = name;
  }
}

class Game
{
  constructor()
  {
    this.time = 0;
    this.flagArray = [];
    this.player1 = null;
    this.player2 = null;
  }

  clear()
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.clearRect(0, 0, c.width, c.height);
  }

  drawBoard()
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

  initGame()
  {
    // flaf
    for (var i = 3; i < 6; ++i)
      this.flagArray.push(new Flag(i, 0));
    this.flagArray.push(new Flag(4, 1));

    for (var i = 3; i < 6; ++i)
      this.flagArray.push(new Flag(i, 8));
    this.flagArray.push(new Flag(4, 7));

    var blue = 0, red = 0;
    var color = ''
    for (var i = 0; i < this.flagArray.length; ++i)
    {
      var rand = Math.floor(Math.random() * Math.floor(2));

      if ( rand == 0 && red != 2 || blue == 2)
        { red++; color = 'rouge'; }
      else
        { blue++; color = 'bleu'; }

      this.flagArray[i].setColor(color);

      if (i == this.flagArray.length/2 - 1)
        blue = 0, red = 0;
    }

    this.player1 = new Player("test1", "rouge", '');
    this.player2 = new Player("test2", "bleu", '');
  }

  update()
  {
    this.player1.getRobot().update();
    this.player2.getRobot().update();
  }

  display()
  {
    this.clear();

    this.drawBoard();

    this.player1.getRobot().draw();
    this.player2.getRobot().draw();

    for (var i = 0; i < this.flagArray.length; ++i)
      this.flagArray[i].draw();
  }

  game()
  {
      if(this.player1.instructionArray.length == 0 && this.player1.popUpIsOpen == false && this.player2.popUpIsOpen != true)
      {
        this.player1.popUpIsOpen = true;
        PopupCenter(800, 200, this.player1.color);
      }

      if(this.player2.instructionArray.length == 0 && this.player2.popUpIsOpen == false && this.player1.popUpIsOpen != true)
      {
        this.player2.popUpIsOpen = true;
        PopupCenter(800, 200, this.player2.color);
      }

      this.update();
      this.display();
  }

  test()
  {
    this.player1.getRobot().executeInstruction("repousser", this.player2.getRobot(), this.flagArray);
  }
}

/* main */
function main()
{
  var game = new Game();
  game.initGame();
  var id = setInterval(frame, 1000/60);
  function frame()
  {
   if (false)
     clearInterval(id);
   else
   {
     game.game();
   }
  }
}
