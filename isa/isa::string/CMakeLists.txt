cmake_minimum_required(VERSION 3.16.3)

# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")

project(string)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

IF(UNIX OR MINGW)
	message("GNU")

	set(MY_FLAGS "-Wall -O0 -g")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_FLAGS}")
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${MY_FLAGS}")
ELSEIF(WIN32)
	message("WIN")
ELSEIF(APPLE)
	message("APPLE")
ENDIF()


set(STRING_SRC
		string.cpp
	)

set(TEST_SRC 
		tests/tests.cpp
		tests/constructor_tests.cpp
		tests/assign_tests.cpp
	)

find_package(Catch2 REQUIRED)
add_executable(tests ${TEST_SRC} ${STRING_SRC})
target_link_libraries(tests PUBLIC Catch2::Catch2)

