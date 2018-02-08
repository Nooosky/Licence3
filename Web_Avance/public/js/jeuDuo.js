class Player
{
  //variable
  var m_name;
  var m_color;
  var m_icon;
  var m_score;

  //methode
  constructor(name, color, icon)
  {
    m_name = name;
    m_color = color;
    m_icon = icon;
    m_score = 0;
  }
}

class Robot
{
  //variable
  var m_color;
  var m_postionX;
  var m_postionY;
  var m_hasLFag;

  //methode
  constructor(color, postionX, positionY)
  {
    m_color = color;
    m_postionX = postionX;
    m_postionY = positionY;
  }
}

class Flag
{
  //variable
  var m_color;
  var m_postionX;
  var m_postionY;

  //methode
  constructor(color, postionX, positionY)
  {
    m_color = color;
    m_postionX = postionX;
    m_postionY = positionY;
  }
}

class Instruction
{
  //variable
  var m_name;
  var m_action;

  //methode
  constructor()
  {
  }
}

class Game
{
  //variable
  var m_time;

  //methode
  constructor()
  {
    m_time = 0;
  }
}

/* main */
