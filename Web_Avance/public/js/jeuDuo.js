class Player
{
  constructor(name, color, icon)
  {
    this.name = name;
    this.color = color;
    this.icon = icon;
    this.robot = null;

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

    this.instructionArray = [];
    this.indiceInstruction = 0;

    this.imgRobot = new Image();
    this.imgWheel = new Image();
    this.imgRobot.src = "../images/robot-corps-"+ this.color +".png";
    this.imgWheel.src = "../images/robot-chenilles.png";
  }

  update(robot, flagArray)
  {
    this.instructionArray = getInstructionArray(this.color);

    if(this.instructionArray.length == 5 && robot.instructionArray.length == 5 && this.canMove() && robot.canMove())
    {
      flashyText("The robots are doing their maneuvers");
      if (this.indiceInstruction == 5)
      {
        this.indiceInstruction = 0;
        eraseInstruction(this.color);
      }
      else
      {
        this.executeInstruction(this.instructionArray[this.indiceInstruction], robot, flagArray);
        this.indiceInstruction++;
      }
    }
    else if(this.instructionArray.length != 5 || robot.instructionArray.length != 5){
      flashyText("May the players choose their instructions");
    }


    //change orientation
    if (this.destinationOrientation != this.orientation)
    {
      if(this.destinationOrientation >= 180 && this.orientation == 0) this.orientation = 360;
      this.orientation += (this.orientation - this.destinationOrientation <= 90 && this.orientation - this.destinationOrientation > 0) ? -1 : 1;
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
    var coef = 1;
    if(window.innerWidth > 1400)
      coef = 1080/1400;
    else
      coef = 1080/window.innerWidth;

    var carree = 75 / coef;
    var decalage1 = 10 / coef;
    var decalage2 = 20 / coef;
    var taille1 = 55 / coef;
    var taille2 = 35 / coef;

    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.save();
    ctx.translate((this.positionX * carree + decalage1 + taille1/2), (this.positionY * carree + decalage2 + taille2/2));
    ctx.rotate(Math.PI / 180 * this.orientation);
    ctx.translate(-(this.positionX * carree + decalage2 + taille2/2), -(this.positionY * carree + decalage1 + taille1/2));
    ctx.drawImage(this.imgWheel, this.positionX * carree + decalage2, this.positionY * carree + decalage1, taille2, taille1);
    ctx.drawImage(this.imgRobot, this.positionX * carree + decalage1, this.positionY * carree + decalage2, taille1, taille2);
    ctx.restore();
  }

  executeInstruction(instruction, robot, flagArray)
  {
    if(robot.instructionArray[robot.indiceInstruction] != "annuler")
      switch(instruction)
      {
        case "nord":
        {
          this.destinationOrientation = 270;
          this.destinationPositionY-= (this.destinationPositionY == 0 || (this.destinationPositionY-1 == (Math.round(robot.positionY * 100) / 100) && this.destinationPositionX == (Math.round(robot.positionX * 100) / 100))) ? 0 : 1;
          break;
        }
        case "sud":
        {
          this.destinationOrientation = 90;
          this.destinationPositionY+= (this.destinationPositionY == 8 || (this.destinationPositionY+1 == (Math.round(robot.positionY * 100) / 100) && this.destinationPositionX == (Math.round(robot.positionX * 100) / 100))) ? 0 : 1;
          break;
        }
        case "est":
        {
          this.destinationOrientation = 0;
          this.destinationPositionX+= (this.destinationPositionX == 8 || (this.destinationPositionX+1 == (Math.round(robot.positionX * 100) / 100) && this.destinationPositionY == (Math.round(robot.positionY * 100) / 100))) ? 0 : 1;
          break;
        }
        case "ouest":
        {
          this.destinationOrientation = 180;
          this.destinationPositionX-= (this.destinationPositionX == 0 || (this.destinationPositionX-1 == (Math.round(robot.positionX * 100) / 100) && this.destinationPositionY == (Math.round(robot.positionY * 100) / 100))) ? 0 : 1;
          break;
        }
        case "prendre":
        {
          for (var i = 0; i < flagArray.length; ++i)
            if(this.flag == null && (Math.round(flagArray[i].positionX * 100) / 100) == (Math.round(this.positionX * 100) / 100) && (Math.round(flagArray[i].positionY * 100) / 100) == (Math.round(this.positionY * 100) / 100) && flagArray[i].color == this.color)
              this.flag = flagArray[i];
          break;
        }
        case "deposer":
        {
          var canDrop = 0;
          for (var i = 0; i < flagArray.length; ++i)
          {
            if(this.flag != null && (Math.round(flagArray[i].positionX * 100) / 100) == (Math.round(this.flag.positionX * 100) / 100) && (Math.round(flagArray[i].positionY * 100) / 100) == (Math.round(this.flag.positionY * 100) / 100))
              canDrop += 1;
          }

          if(canDrop == 1)
            this.flag = null;
          break;
        }
        case "repousser":
        {
          if (robot.color == "rouge")
            robot.destinationPositionX-= (robot.destinationPositionX == 0 || (robot.destinationPositionX-1 == (Math.round(this.positionX * 100) / 100)  && robot.destinationPositionY == (Math.round(this.positionY * 100) / 100))) ? 0 : 1;
          else if (robot.color == "bleu")
            robot.destinationPositionX+= (robot.destinationPositionX == 8 || (robot.destinationPositionX+1 == (Math.round(this.positionX * 100) / 100)  && robot.destinationPositionY == (Math.round(this.positionY * 100) / 100))) ? 0 : 1;
          break;
        }
        case "pause":
        {
          break;
        }
        case "x2":
        {
          this.executeInstruction(this.instructionArray[this.indiceInstruction -1], robot, flagArray);
          break;
        }
        case "ouest_x2":
        {
          this.destinationOrientation = 180;
          this.destinationPositionX-= (this.destinationPositionX == 0 || (this.destinationPositionX-1 == (Math.round(robot.positionX * 100) / 100) && this.destinationPositionY == (Math.round(robot.positionY * 100) / 100))) ? 0 : 1;
          this.destinationPositionX-= (this.destinationPositionX == 0 || (this.destinationPositionX-1 == (Math.round(robot.positionX * 100) / 100) && this.destinationPositionY == (Math.round(robot.positionY * 100) / 100))) ? 0 : 1;
          break;
        }
        case "est_x2":
        {
          this.destinationOrientation = 0;
          this.destinationPositionX+= (this.destinationPositionX == 8 || (this.destinationPositionX+1 == (Math.round(robot.positionX * 100) / 100) && this.destinationPositionY == (Math.round(robot.positionY * 100) / 100))) ? 0 : 1;
          this.destinationPositionX+= (this.destinationPositionX == 8 || (this.destinationPositionX+1 == (Math.round(robot.positionX * 100) / 100) && this.destinationPositionY == (Math.round(robot.positionY * 100) / 100))) ? 0 : 1;
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
    var coef = 1;
    if(window.innerWidth > 1400)
      coef = 1080/1400;
    else
      coef = 1080/window.innerWidth;

    var carree = 75 / coef;
    var decalage = 10 / coef;
    var taille = 55 / coef;

    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.drawImage(this.img, this.positionX * carree + decalage, this.positionY * carree + decalage, taille, taille);
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

    this.player1 = new Player("Player1", "rouge", '');
    this.player2 = new Player("Player2", "bleu", '');
  }

  update()
  {
    this.player1.getRobot().update(this.player2.getRobot(), this.flagArray);
    this.player2.getRobot().update(this.player1.getRobot(), this.flagArray);

    var flagRed = 0;
    var flagBlue = 0;
    for (var i = 0; i < this.flagArray.length; ++i)
      if(this.flagArray[i].color == "rouge" && (
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 0 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 3)||
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 0 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 4)||
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 0 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 5)||
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 1 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 4)
        ))
        flagRed++;
      else if(this.flagArray[i].color == "bleu" && (
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 8 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 3)||
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 8 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 4)||
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 8 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 5)||
        ((Math.round(this.flagArray[i].positionX * 100) / 100) == 7 && (Math.round(this.flagArray[i].positionY * 100) / 100) == 4)
        ))
        flagBlue++;

    if(flagRed >= 2)
    {
      alert(this.player1.name + " wins! Congratulation!");
      document.location.href="..";
    }
    else if(flagBlue >= 2)
    {
      alert(this.player2.name + " wins! Congratulation!");
      document.location.href="..";
    }
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
