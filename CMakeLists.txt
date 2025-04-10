cmake_minimum_required(VERSION 3.28)
project(Voxel_Engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(includes/SDL EXCLUDE_FROM_ALL)

#install(TARGETS SDL3 DESTINATION lib)

add_executable(Voxel_Editor src/editor.cxx)

target_link_libraries(Voxel_Editor PRIVATE SDL3::SDL3)

