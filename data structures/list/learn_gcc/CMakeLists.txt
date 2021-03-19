# builds on clang and gcc. msvc is not tested

cmake_minimum_required(VERSION 3.16)
project(gcc_list)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wno-gnu -O0 -g)

include_directories(include)

set(TEST_SRC_CATCH
        tests/tests_driver.cpp

        tests/ctor.cpp
        tests/operator=.cpp
        tests/front_and_back.cpp
        tests/assign.cpp
        tests/emplace.cpp
        tests/push_pop.cpp
        tests/erase.cpp
        tests/swap_resize.cpp
        tests/insert.cpp
    )

#find_package(Catch2 #[[REQUIRED]])

add_executable(test_with_catch ${TEST_SRC_CATCH})
#target_link_libraries(tests PUBLIC Catch2::Catch2)
