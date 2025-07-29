cmake_minimum_required(VERSION 3.28)
project(Voxel_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/generate_files")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/binary_folder")
