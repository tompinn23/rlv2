cmake_minimum_required(VERSION 3.8)

project(rl VERSION 1.0.0)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set(CMAKE_C_STANDARD 11)

add_subdirectory(Dependencies)
add_subdirectory(Source)