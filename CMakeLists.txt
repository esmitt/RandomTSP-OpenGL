cmake_minimum_required(VERSION 3.0)

PROJECT(tspOpenGL)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_executable(tspOpenGL main.cpp)


target_link_libraries(tspOpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )