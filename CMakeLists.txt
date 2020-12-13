cmake_minimum_required(VERSION 3.15)
project(sudoku)

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Werror -g --std=c++17")

# output binary files to bin directory
set(CMAKE_BINARY_DIR "../bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(sudoku
    ../src/main.cc
    ../src/sudoku/core/grid.cc
    ../src/util/kb_io.cc
    ../src/util/user_input.cc)

# need this to find header files
target_include_directories(sudoku PRIVATE include)
