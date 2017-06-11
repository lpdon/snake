#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <inttypes.h>
#include <vector>
#include <memory>

#include "object.hpp"

class cWindow
{
private:
  uint16_t width;
  uint16_t height; 
  GLFWwindow * glfwWindow;
  const std::vector<cObject *>& gameObjects;
  bool status;

  void keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode );
  
  void drawObjects( void );
  void objectsInputKeyCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode );

public:
  cWindow( uint16_t arg_width, uint16_t arg_height, const std::vector<cObject *>& arg_objects )
  : width( arg_width )
  , height( arg_height )
  , glfwWindow( nullptr )
  , gameObjects( arg_objects )
  , status( false )
  {

  }

  bool init( void );
  void update( void );

  inline bool getStatus( void )
  {
    return status;
  }
};

#endif