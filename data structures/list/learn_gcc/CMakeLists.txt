cmake_minimum_required(VERSION 3.16)
project(list)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_compile_options(-Wno-gnu)

add_executable(tests tests/main.cpp src/list.cpp)
