cmake_minimum_required(VERSION 3.28)
project(Voxel_Engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(includes/SDL EXCLUDE_FROM_ALL)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR})

set(GLAD_SOURCES 
  lib/glad/src/glad.c) 

set(GLAD_INCLUDES 
  includes/Third-Party
  )

include_directories(${GLAD_INCLUDES})

#include_directories( ${OPENGL_INCLUDE_DIRS})

#add_include_directories(includes)

#install(TARGETS SDL3 DESTINATION lib)

add_executable(Voxel_Editor src/editor.cxx ${GLAD_SOURCES})

#target_link_libraries(Voxel_Editor ${OPENGL_gl_LIBRARY})

target_link_libraries(Voxel_Editor PRIVATE SDL3::SDL3 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

