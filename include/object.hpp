#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <inttypes.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class cObject
{
protected:
  int x, y;
  int width, height;
  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint shaderProgram;

  cObject( int arg_x, int arg_y, int arg_width, int arg_height )
  : x( arg_x )
  , y( arg_y )
  , width( arg_width )
  , height( arg_height )
  {

  }

public:
  virtual ~cObject()
  {

  }

  virtual void init( void ) = 0;
  virtual void update( void ) = 0;
  virtual void draw( void ) = 0;
  virtual void collision( void ) = 0;
  virtual void reset( void ) = 0;

  inline virtual void setX( int arg_x )
  {
    this->x = arg_x;
  }

  inline virtual void setY( int arg_y )
  {
    this->y = arg_y;
  }

  inline virtual int getX( void ) const
  {
    return x;
  }

  inline virtual int getY( void ) const
  {
    return y;
  }

  inline virtual int getWidth( void ) const
  {
    return width;
  }

  inline virtual int getHeight( void ) const
  {
    return height;
  }
  
  virtual void keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode )
  {

  }

};



#endif
