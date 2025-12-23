cmake_minimum_required(VERSION 3.28)
project(Voxel_Engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(includes/SDL EXCLUDE_FROM_ALL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(GLAD_SOURCES 
  lib/glad/src/glad.c) 

set(GLAD_INCLUDES 
  includes/Third-Party)
set(STB_INCLUDES 
  includes/Third-Party/stb)

include_directories(Voxel_Editor PRIVATE ${GLAD_INCLUDES} ${OPENGL_INCLUDE_DIRS})
#include_directories( ${OPENGL_INCLUDE_DIRS})

#add_include_directories(includes)

#install(TARGETS SDL3 DESTINATION lib)

add_executable(Voxel_Editor src/editor.cxx src/renderer/shaders.cxx ${GLAD_SOURCES})

#target_link_libraries(Voxel_Editor ${OPENGL_gl_LIBRARY})

target_link_libraries(Voxel_Editor PRIVATE SDL3::SDL3 glm::glm ${OPENGL_LIBRARIES} ${GLM_LIBRARIES})

set(RESOURCE_DEST "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")

add_custom_command(TARGET Voxel_Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RESOURCE_DEST}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "${RESOURCE_DEST}"
    COMMENT "Copying resources to ${RESOURCE_DEST}"
)
