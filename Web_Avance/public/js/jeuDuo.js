class Player
{
  constructor(name, color, icon)
  {
    this.name = name;
    this.color = color;
    this.icon = icon;
    this.robot = null;

    this.instructionArray = [];
    this.indiceInstruction = 0;

    if (this.color == "rouge")
      if (Math.floor(Math.random() * Math.floor(4)) != 0)
        this.robot = new Robot(this.color, 0, 3 + Math.floor(Math.random() * Math.floor(3)), 360);
      else
        this.robot = new Robot(this.color, 1, 4, 360);
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
      this.orientation += 1;

      if (this.orientation > 360) this.orientation -= 360;
    }

    //change position
    if (this.destinationOrientation == this.orientation)
    {
      if(this.destinationPositionX > Math.round(this.positionX * 100) / 100)
        this.positionX+= 0.02;
      else if(this.destinationPositionX < Math.round(this.positionX * 100) / 100)
        this.positionX-= 0.02;
      else if(this.destinationPositionY > Math.round(this.positionY * 100) / 100)
        this.positionY+= 0.02;
      else if(this.destinationPositionY < Math.round(this.positionY * 100) / 100)
        this.positionY-= 0.02;

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
        this.destinationOrientation = 360;
        this.destinationPositionX+= (this.destinationPositionX < 8 && this.destinationPositionX+1 != robot.positionX) ? 1 : 0;
        break;
      }
      case "ouest":
      {
        this.destinationOrientation = 180;
        this.destinationPositionX-= (this.destinationPositionX > 0  && this.destinationPositionX-1 != robot.positionX) ? 1 : 0;
        break;
      }
      case "prendre":
      {
        for (var i = 0; i < flagArray.length; ++i)
          if(this.flag == null && flagArray[i].positionX == (Math.round(this.positionX * 100) / 100) && flagArray[i].positionY == (Math.round(this.positionY * 100) / 100) && flagArray[i].color == this.color)
            this.flag = flagArray[i];
        break;
      }
      case "deposer":
      {
        var canDrop = true;
        for (var i = 0; i < flagArray.length; ++i)
          if(this.flag != null && flagArray[i].positionX == (Math.round(this.flag.positionX * 100) / 100) && flagArray[i].positionY == (Math.round(this.flag.positionY * 100) / 100))
            canDrop = false;

        if(canDrop)
          this.flag = null;
        break;
      }
      case "repousser":
      {
        if (robot.color == "rouge")
          robot.destinationPositionX-= (robot.destinationPositionX > 0 && robot.destinationPositionX-1 != (Math.round(this.positionX * 100) / 100)) ? 1 : 0;
        else if (robot.color == "bleu")
          robot.destinationPositionX+= (robot.destinationPositionX < 8 && robot.destinationPositionX+1 != (Math.round(this.positionX * 100) / 100)) ? 1 : 0;
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

  canMove()
  {
    return this.destinationOrientation == this.orientation &&
      this.destinationPositionX == (Math.round(this.positionX * 100) / 100) &&
      this.destinationPositionY == (Math.round(this.positionY * 100) / 100);
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

class Game
{
  constructor()
  {
    this.time = 0;
    this.flagArray = [];
    this.player1 = null;
    this.player2 = null;
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
    this.player1.instructionArray = getInstructionArray(this.player1.color);
    this.player2.instructionArray = getInstructionArray(this.player2.color);

    if(this.player1.instructionArray.length == 5 && this.player2.instructionArray.length == 5)
    {
      if(this.player1.getRobot().canMove() && this.player2.getRobot().canMove())
      {
        this.player1.getRobot().executeInstruction(this.player1.instructionArray[this.player1.indiceInstruction], this.player2.getRobot(), this.flagArray);
        this.player2.getRobot().executeInstruction(this.player2.instructionArray[this.player2.indiceInstruction], this.player1.getRobot(), this.flagArray);
        this.player1.indiceInstruction++;
        this.player2.indiceInstruction++;

        if (this.player1.indiceInstruction == 5 && this.player2.indiceInstruction == 5)
        {
          this.player1.indiceInstruction=0;
          this.player2.indiceInstruction=0;
          eraseInstruction();
          drawLeftCanvas();
          drawRightCanvas();
        }
      }
    }

    this.player1.getRobot().update();
    this.player2.getRobot().update();
  }

  display()
  {
    clear();

    drawBoard();

    this.player1.getRobot().draw();
    this.player2.getRobot().draw();

    for (var i = 0; i < this.flagArray.length; ++i)
      this.flagArray[i].draw();
  }

  game()
  {
      this.update();
      this.display();
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
