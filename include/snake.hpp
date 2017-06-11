#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "object.hpp"
#include <vector>

class cBodyPart : public cObject 
{
private:

public:
  explicit cBodyPart( int arg_x, int arg_y )
    : cObject( arg_x, arg_y, 1, 1 )
  {

  }

  virtual void init( void );
  virtual void draw( void );

  virtual void update( void )
  {
  
  }

  virtual void collision( void ) 
  {
  
  }

  virtual void reset( void )
  {
  
  }
};

class cSnake : public cBodyPart
{
private:
  enum 
  {
    E_STATE_UP,
    E_STATE_DOWN,
    E_STATE_LEFT,
    E_STATE_RIGHT
  } state = { E_STATE_RIGHT };
  
  int speedX{ 1 };
  int speedY{ 1 };

  std::vector<cBodyPart> body{ cBodyPart{ x, y }, cBodyPart{ x, y } };

public:
  explicit cSnake( int arg_x, int arg_y, int arg_width, int arg_height )
    : cBodyPart( arg_x, arg_y )
  {

  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void );  

  virtual void collision( void );

  virtual void reset( void )
  {

  }

  virtual void keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode );
  
  inline void moveUp( void )
  {
    y += speedY;
  }

  inline void moveDown( void )
  {
    y -= speedY;
  }

  inline void moveLeft( void )  
  {
    x -= speedX;
  }

  inline void moveRight( void )
  {
    x += speedX;
  }

  void updateBody( void );
};


#endif
