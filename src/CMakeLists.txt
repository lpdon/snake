#SRC

include_directories ( 
  ${PROJECT_SOURCE_DIR}/include/
  ${PROJECT_SOURCE_DIR}/lib/glfw/include
)

file (
  GLOB_RECURSE
  snake_headers
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

file (
  GLOB_RECURSE
  snake_src
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable ( 
  snake
  ${snake_headers}
  ${snake_src}
) 

target_compile_features( 
  snake PRIVATE 
  cxx_auto_type 
  cxx_nullptr 
  cxx_lambdas 
)

if(WIN32)
include_directories (
  ${PROJECT_SOURCE_DIR}/lib/glew-2.0.0/include
)

set (
  glew_lib
  ${PROJECT_SOURCE_DIR}/lib/glew-2.0.0/lib/Release/Win32/glew32s.lib
)
else()
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})
set (
  glew_lib
  ${GLEW_LIBRARIES}
)
endif()

find_package(OpenGL REQUIRED)

target_compile_definitions(snake PRIVATE GLEW_STATIC)

target_link_libraries ( 
  snake
  ${CMAKE_THREAD_LIBS_INIT}
  glfw 
  ${GLFW_LIBRARIES}
  ${glew_lib}
  ${OPENGL_gl_LIBRARY}
 )
