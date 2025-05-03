cmake_minimum_required(VERSION 3.31)
project(cherry_v)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add include path
include_directories(include test data)

# collect all source files
file(GLOB SRC_FILES src/*.cpp)

# define exec
add_executable(cherry_v main.cpp ${SRC_FILES})
