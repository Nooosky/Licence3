class Player
{
  constructor(name, color, icon)
  {
    this.name = name;
    this.color = color;
    this.icon = icon;
    this.score = 0;
    this.robot = null;

    if (color == "bleu")
      if (Math.floor(Math.random() * Math.floor(4)) != 0)
        this.robot = new Robot('rouge', 0, 3 + Math.floor(Math.random() * Math.floor(3)), 0);
      else
        this.robot = new Robot('rouge', 1, 4, 0);
    else if (color == "rouge")
      if (Math.floor(Math.random() * Math.floor(4)) != 0)
        this.robot = new Robot('bleu', 8, 3 + Math.floor(Math.random() * Math.floor(3)), 180);
      else
        this.robot = new Robot('bleu', 7, 4, 180);
  }

  getRobot()
  {
    return this.robot;
  }
}

class Robot
{
  constructor(color, postionX, positionY, orientation)
  {
    this.color = color;
    this.postionX = postionX;
    this.postionY = positionY;
    this.orientation = orientation;
    this.hasLFag = false;

    this.imgRobot = new Image();
    this.imgWheel = new Image();
    this.imgRobot.src = "../images/robot-corps-"+ this.color +".png";
    this.imgWheel.src = "../images/robot-chenilles.png";
  }

  draw()
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.save();
    ctx.translate((this.postionX * 75 + 10 + 55/2), (this.postionY * 75 + 20 + 35/2));
    ctx.rotate(Math.PI / 180 * this.orientation);
    ctx.translate(-(this.postionX * 75 + 20 + 35/2), -(this.postionY * 75 + 10 + 55/2));
    ctx.drawImage(this.imgWheel, this.postionX * 75 + 20, this.postionY * 75 + 10, 35, 55);
    ctx.drawImage(this.imgRobot, this.postionX * 75 + 10, this.postionY * 75 + 20, 55, 35);
    ctx.restore();
  }

  rotation(orientation)
  {

  }

  move()
  {

  }
}

class Flag
{
  constructor(postionX, positionY)
  {
    this.postionX = postionX;
    this.postionY = positionY;

    this.img = new Image();
    this.color = '';
  }

  setPosition(postionX, positionY)
  {
    this.postionX = postionX;
    this.postionY = positionY;
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
    ctx.drawImage(this.img, this.postionX * 75 + 10, this.postionY * 75 + 10, 55, 55);
  }
}

class Instruction
{
  constructor(name, action)
  {
    this.name = name;
    this.action = action;
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


    // rectangle rouge
    for(var i = 3; i < 6; ++i)
      createSquare("#ffaaaa", 0, i)
    createSquare("#ffaaaa", 1, 4)

    // rectangle bleu
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
        { red++; color = 'red'; }
      else
        { blue++; color = 'blue'; }

      this.flagArray[i].setColor(color);

      if (i == this.flagArray.length/2 - 1)
        blue = 0, red = 0;
    }

    this.player1 = new Player("test1", "rouge", '');
    this.player2 = new Player("test2", "bleu", '');
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
      this.display();
  }

  test()
  {
    this.player2.getRobot().rotation(100);
  }
}

/* main */
function main()
{
  var game = new Game();
  game.initGame();
  game.game();
  document.getElementById("board").onclick = function() {game.test()};
}
