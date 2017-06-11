#include "window.hpp"
#include <iostream>

bool cWindow::init( void )
{
  glfwInit();
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

  glfwWindow = glfwCreateWindow( static_cast<int>( width ), static_cast<int>( height ), "Pong", nullptr, nullptr );
  if ( glfwWindow == nullptr )
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent( glfwWindow );

  glewExperimental = GL_TRUE;
  if ( glewInit() != GLEW_OK )
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return false;
  }

  const GLubyte* renderer = glGetString( GL_RENDERER ); // get renderer string
  const GLubyte* version = glGetString( GL_VERSION ); // version as a string
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  int loc_width, loc_height;
  glfwGetFramebufferSize( glfwWindow, &loc_width, &loc_height );

  glViewport( 0, 0, loc_width, loc_height );

  glEnable( GL_DEPTH_TEST ); // enable depth-testing
  glDepthFunc( GL_LESS ); // depth-testing interprets a smaller value as "closer"

  glfwSetWindowUserPointer( glfwWindow, this );

  auto loc_glfwKeyCallback = []( GLFWwindow * arg_window, int arg_key, int arg_scancode, int arg_action, int arg_mode )
  {
    static_cast<cWindow*>( glfwGetWindowUserPointer( arg_window ) )->keyInputCallback( arg_key, arg_scancode, arg_action, arg_mode );
  };
  glfwSetKeyCallback( glfwWindow, loc_glfwKeyCallback );

  status = true;
  return true;
}

void cWindow::update( void )
{
  if ( status )
  {
    glfwPollEvents();

    // rendeeer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    drawObjects();

    glfwSwapBuffers( glfwWindow );
    status = !glfwWindowShouldClose( glfwWindow );
  }
  else
  {
    glfwTerminate();
  }
}

void cWindow::keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode )
{
  // When a user presses the escape key, we set the WindowShouldClose property to true, 
  // closing the application

  switch( arg_key )
  {
    case GLFW_KEY_ESCAPE: 
    {
      if ( arg_action == GLFW_PRESS )
      {
        glfwSetWindowShouldClose( glfwWindow, GL_TRUE );
      }
      break;
    }
    default:
    {

    }
  } 

  objectsInputKeyCallback( arg_key, arg_scancode, arg_action, arg_mode );
}

void cWindow::drawObjects( void )
{
  for ( auto& loc_pObj : gameObjects )
  {
    loc_pObj->draw();
  }
}

void cWindow::objectsInputKeyCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode )
{
  for ( auto& loc_pObj : gameObjects )
  {
    loc_pObj->keyInputCallback( arg_key, arg_scancode, arg_action, arg_mode );
  }
}