cmake_minimum_required(VERSION 3.23.0-rc2)

project(csvreader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("Building in debug mode\n")
	add_compile_definitions(CSVREADER_DEBUG)
else()
	
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

set(SOURCES
	main.cpp
	csv_calculator.cpp
)

set(TESTS_SOURCES
	tests.cpp
	csv_calculator.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(test_${PROJECT_NAME} ${TESTS_SOURCES})