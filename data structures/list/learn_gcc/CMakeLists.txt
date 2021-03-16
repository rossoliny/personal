cmake_minimum_required(VERSION 3.16)
project(gcc_list)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wno-gnu)

include_directories(include)

set(TEST_SRC
        tests/tests_driver.cpp

        tests/ctor.cpp
    )


#find_package(Catch2 #[[REQUIRED]])


add_executable(tests ${TEST_SRC})
#target_link_libraries(tests PUBLIC Catch2::Catch2)
