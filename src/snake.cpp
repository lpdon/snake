#include "snake.hpp"
#include "game.hpp"

void cBodyPart::init( void )
{
  // https://open.gl/drawing

  // Shader sources
  const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    out vec3 Color;
    void main()
    {
        Color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

  const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
        //outColor = vec4(Color, 1.0);
        outColor = vec4(0.5, 0.0, 0.5, 1.0);
    }
)glsl";

  // Create Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  vertexArray = vao;

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);
  vertexBuffer = vbo;

  const GLfloat loc_x = static_cast<GLfloat>( x )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_y = static_cast<GLfloat>( y )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_width = static_cast<GLfloat>( width )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_height = static_cast<GLfloat>( height )/static_cast<GLfloat>( cGame::SCALE );

  const GLfloat vertices[] =
  {
    loc_x,             loc_y,               0.0f, 0.0f, 0.0f, // Top-left
    loc_x,             loc_y + loc_height,  0.0f, 1.0f, 0.0f, // Top-right
    loc_x + loc_width, loc_y + loc_height,  0.0f, 0.0f, 1.0f, // Bottom-right
    loc_x + loc_width, loc_y,               0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create an element array
  GLuint ebo;
  glGenBuffers(1, &ebo);

  const GLuint elements[] = 
  {
    0, 1, 2,
    2, 3, 0
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  // Create and compile the vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  // Create and compile the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Link the vertex and fragment shader into a shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

  //GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  //glEnableVertexAttribArray(colAttrib);
  //glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void cBodyPart::draw( void )
{
  glUseProgram( shaderProgram );
  glBindVertexArray( vertexArray );

  const GLfloat loc_x = static_cast<GLfloat>( x )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_y = static_cast<GLfloat>( y )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_width = static_cast<GLfloat>( width )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_height = static_cast<GLfloat>( height )/static_cast<GLfloat>( cGame::SCALE );

  const GLfloat vertices[] =
  {
    loc_x,             loc_y,               0.0f, 0.0f, 0.0f, // Top-left
    loc_x,             loc_y + loc_height,  0.0f, 1.0f, 0.0f, // Top-right
    loc_x + loc_width, loc_y + loc_height,  0.0f, 0.0f, 1.0f, // Bottom-right
    loc_x + loc_width, loc_y,               0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  // draw points 0-3 from the currently bound VAO with current in-use shader
  //glDrawArrays( GL_TRIANGLES, 0, 6 );
  glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

void cSnake::init( void )
{
  cBodyPart::init();

  for ( auto& loc_part : body ) 
  {
    loc_part.init();
  }
}

void cSnake::update( void )
{
  updateBody();

  switch( state )
  {
    case E_STATE_UP:
    {
      moveUp();
      break;
    }
    case E_STATE_DOWN:
    {
      moveDown();
      break;
    }
    case E_STATE_LEFT:
    {
      moveLeft();
      break;
    }
    case E_STATE_RIGHT:
    {
      moveRight();
      break;
    }
    default:
    {
    }
  }

  if ( x > cGame::MAX_X )
  {
    x = cGame::MIN_X;
  }
  else if ( x < cGame::MIN_X )
  {
    x = cGame::MAX_X;
  }

  if ( y > cGame::MAX_Y )
  {
    y = cGame::MIN_Y;
  }
  else if ( y < cGame::MIN_Y )
  {
    y = cGame::MAX_Y;
  }
}

void cSnake::draw( void )
{
  cBodyPart::draw();

  for ( auto& loc_part : body ) 
  {
    loc_part.draw();
  }
}

void cSnake::collision( void )
{
  auto& loc_lastPart = body.back();
  body.push_back( cBodyPart{ loc_lastPart.getX(), loc_lastPart.getY() } );
}

void cSnake::keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode )
{
  switch( arg_key )
  {
    case GLFW_KEY_UP:
    {
      //if ( arg_action == GLFW_PRESS )
      {        
        state = E_STATE_UP;
      }
      break;
    }
    case GLFW_KEY_DOWN:
    {
      //if ( arg_action == GLFW_PRESS )
      {
        state = E_STATE_DOWN;
      }      
      break;
    }
    case GLFW_KEY_LEFT:
    {
      //if ( arg_action == GLFW_PRESS )
      {
        state = E_STATE_LEFT;
      }      
      break;
    }
    case GLFW_KEY_RIGHT:
    {
      //if ( arg_action == GLFW_PRESS )
      {
        state = E_STATE_RIGHT;
      }      
      break;
    }
    default:
    {

    }
  } 
}

void cSnake::updateBody( void )
{
  auto& loc_bodyStart = body.front();

  loc_bodyStart.setX( x );
  loc_bodyStart.setY( y );

  // Shift body positions
  for( uint32_t i = body.size() - 1U; i >= 1U; --i )
  {
    auto& loc_previousPart = body[ i - 1U ];
    auto& loc_part = body[ i ];

    loc_part.setX( loc_previousPart.getX() );
    loc_part.setY( loc_previousPart.getY() );
  }
}