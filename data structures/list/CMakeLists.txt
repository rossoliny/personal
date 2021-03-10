cmake_minimum_required(VERSION 3.16)
project(list)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tests tests/main.cpp)
