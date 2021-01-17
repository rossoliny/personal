#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// Unit tests for isa::string constructors
// std=c++11
#include "../string.h"

#define tag "[constructors]"

void CHECK_MY_STRING(const isa::string& actual, const std::string& expected)
{
	REQUIRE(strcmp(actual.c_str() , expected.c_str()) == 0);
	REQUIRE(actual.size() == expected.size());
	REQUIRE(actual.capacity() == expected.capacity()); // short string
}

TEST_CASE("default constructor must create short string", tag "[default]")
{
	isa::string actual;
	std::string expected;
	
	CHECK_MY_STRING(actual, expected);
}

TEST_CASE("fill constructor must create short string", tag "[fill]")
{
	isa::string actual(10, 'i');
	std::string expected(10, 'i');

	CHECK_MY_STRING(actual, expected);
}

TEST_CASE("fill constructor must create long string", tag "[fill]")
{
	isa::string actual(16, 'i');
	std::string expected(16, 'i');
	
	CHECK_MY_STRING(actual, expected);
}

TEST_CASE("from c-string constructor must create short string", tag "[c-string]")
{
	char c_str[] = "0123456789";
	isa::string actual(c_str);
	std::string expected(c_str);

	CHECK_MY_STRING(actual, expected);
}

TEST_CASE("from c-string constructor must create long string", tag "[c-string]")
{
	char c_str[] = "012345678910121315"; // 17
	isa::string actual(c_str);
	std::string expected(c_str);
	
	CHECK_MY_STRING(actual, expected);
}

TEST_CASE("from buffer constructor must create short string", tag "[c-string]")
{
	char buff[16]; 
	memset(buff, 0, sizeof(buff));
	
	isa::string actual(buff, sizeof(buff));
	std::string expected(buff, sizeof(buff));

	CHECK_MY_STRING(actual, expected);
}


