class Player
{
  constructor(name, color, icon)
  {
    this.name = name;
    this.color = color;
    this.icon = icon;
    this.score = 0;
  }
}

class Robot
{
  constructor(color, postionX, positionY)
  {
    this.color = color;
    this.postionX = postionX;
    this.postionY = positionY;
    this.hasLFag = false;
  }
}

class Flag
{
  constructor(color, postionX, positionY)
  {
    this.color = color;
    this.postionX = postionX;
    this.postionY = positionY;
  }

  setPosition(postionX, positionY)
  {
    this.postionX = postionX;
    this.postionY = positionY;
  }

  setColor(color)
  {
    this.color = color;
  }

  draw()
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    var img = new Image();
    img.src = "../images/flag-" + this.color + ".png";
    ctx.drawImage(img, this.postionX * 75 + 10, this.postionY * 75 + 10, 55, 55);
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
  }

  clear()
  {
    var c = document.getElementById("board");
    var ctx = c.getContext("2d");
    ctx.clearRect(0, 0, c.width, c.height);
  }

  drawBoard()
  {
    var createSquare =
    function(color, positionX, positionY)
    {
        var c = document.getElementById("board");
        var ctx = c.getContext("2d");
        ctx.fillStyle = color;
        ctx.beginPath();
        ctx.fillRect(75 * positionX, 75 * positionY, 75, 75);
    }

    var createLine =
    function(color, width, positionX1, positionY1, positionX2, positionY2)
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
    for (var i = 3; i < 6; ++i)
      this.flagArray.push(new Flag('', i, 0));
    this.flagArray.push(new Flag('', 4, 1));

    for (var i = 3; i < 6; ++i)
      this.flagArray.push(new Flag('', i, 8));
    this.flagArray.push(new Flag('', 4, 7));

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
  }

  display()
  {
    this.clear();

    this.drawBoard();

    for (var i = 0; i < this.flagArray.length; ++i)
      this.flagArray[i].draw();
  }

  game()
  {
      this.display();
  }
}

/* main */
function main()
{
  var game = new Game();
  game.initGame();
  game.game();
}
