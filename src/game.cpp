#include "game.hpp"
#include <iostream>

cGame::cGame( void )
{
  gameWindow.init();
  initObjects();
}

void cGame::initObjects( void )
{
  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->init();
  }
}

void cGame::run( void )
{
  // https://stackoverflow.com/questions/20390028/c-using-glfwgettime-for-a-fixed-time-step
  static double limitFPS = 1.0 / 10;

  double lastTime = glfwGetTime(), timer = lastTime;
  double deltaTime = 0, nowTime = 0;
  int frames = 0 , updates = 0;

  // - While window is alive
  while ( gameWindow.getStatus() )
  {
    // - Measure time
    nowTime = glfwGetTime();
    deltaTime += (nowTime - lastTime) / limitFPS;
    lastTime = nowTime;

    // - Only update at 60 frames / s
    while (deltaTime >= 1.0){
      update();   // - Update function
      updates++;
      deltaTime--;
    }
    // - Render at maximum possible frames
    render(); // - Render function
    frames++;

    // - Reset after one second
    if (glfwGetTime() - timer > 1.0) {
      timer ++;
      std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
      updates = 0, frames = 0;
    }

  }
}

void cGame::updateObjects( void )
{
  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->update();
  }
}

void cGame::checkCollisions( void )
{
  for ( unsigned int i = 0; i < gameObjects.size(); ++i )
  {
    for ( unsigned int j = i + 1; j < gameObjects.size(); ++j )
    {
      auto& loc_pObj1 = gameObjects[ i ];
      auto& loc_pObj2 = gameObjects[ j ];

      const bool loc_xCol = ( loc_pObj1->getX() == loc_pObj2->getX() );
      const bool loc_yCol = ( loc_pObj1->getY() == loc_pObj2->getY() );

      if ( loc_xCol && loc_yCol )
      {
        loc_pObj1->collision();
        loc_pObj2->collision();
      }
    }
  }

  // out of bounds
  for ( auto& loc_pObj : gameObjects ) 
  {
    if ( ( loc_pObj->getX() < MIN_X ) || ( loc_pObj->getX() + loc_pObj->getWidth() > MAX_X ) )
    {
      loc_pObj->reset();
    }
  }
}

void cGame::resetObjects( void )
{
  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->reset();
  }
}

void cGame::update( void )
{
  updateObjects();
  checkCollisions();
}

void cGame::render( void )
{
  gameWindow.update();
}