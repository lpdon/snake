#ifndef BALL_HPP
#define BALL_HPP

#include "object.hpp"

#include <random>

class cBall : public cObject
{
private:
  bool stateUp, stateRight;
  int speedX, speedY;
  int colDebounce;
  int startX, startY;

  std::random_device rd{};
  std::mt19937 mt{ rd() };

public:
  explicit cBall( int arg_x, int arg_y, int arg_width, int arg_height )
  : cObject( arg_x, arg_y, arg_width, arg_height )
  , stateUp( true ), stateRight( true )
  , speedX( 1 )
  , speedY( 1 )
  , colDebounce( 0 )
  , startX( arg_x ), startY( arg_y )
  {
  
  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void ); 
  virtual void collision( void );
  virtual void reset( void );
};

#endif