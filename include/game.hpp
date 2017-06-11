#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include "object.hpp"
#include "snake.hpp"
#include "ball.hpp"

#include <vector>

class cGame 
{
private:
  cWindow gameWindow{ 800U, 800U, gameObjects };
  cBall ball{ 0, 5, 1, 1 };
  cSnake snake{ 0, 0, 1, 1 };
  std::vector<cObject *> gameObjects{ &ball, &snake };

  void initObjects( void );
  void updateObjects( void );
  void checkCollisions( void );
  void resetObjects( void );
  void update( void );
  void render( void );

public:
  static constexpr int MIN_X = -10;
  static constexpr int MIN_Y = -10;
  static constexpr int MAX_X =  10;
  static constexpr int MAX_Y =  10;
  static constexpr int SCALE =  10;

  cGame( void );
  void run( void );
};

#endif