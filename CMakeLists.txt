cmake_minimum_required(VERSION 3.28)
project(Voxel_Engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(includes/SDL EXCLUDE_FROM_ALL)

add_subdirectory(includes/Third-Party/glew/build/cmake)

find_package(OpenGL REQUIRED)

#include_directories( ${OPENGL_INCLUDE_DIRS})

#add_include_directories(includes)

#install(TARGETS SDL3 DESTINATION lib)

add_executable(Voxel_Editor src/editor.cxx)

target_include_directories(Voxel_Editor PRIVATE includes/Third-Party/glew/auto/src)

#target_link_libraries(Voxel_Editor ${OPENGL_gl_LIBRARY})

if(WIN32)
  target_compile_definition(Voxel_Editor PRIVATE GLEW)
endif()

target_link_libraries(Voxel_Editor PRIVATE SDL3::SDL3 libglew_shared)

