#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// Unit tests for isa::string constructors
// std=c++11
#include "../string.h"

#define tag "[constructors]"

void COMPARE_WITH_STD(const isa::string& actual, const std::string& expected)
{
	TEST_CASE("isa::string must be identical to std::string")
	{
		CHECK(strcmp(actual.c_str() , expected.c_str()) == 0);
		CHECK(actual.size() == expected.size());
		CHECK(actual.capacity() == expected.capacity()); // short string
	}
}

TEST_CASE("default constructor must create short string", tag "[default]")
{
	isa::string actual;
	std::string expected;
	
	COMPARE_WITH_STD(actual, expected);
}

TEST_CASE("fill constructor", tag "[fill]")
{

	SECTION("must create short string")
	{
		isa::string actual(10, 'i');
		std::string expected(10, 'i');

		COMPARE_WITH_STD(actual, expected);
	}
	SECTION("must create long string")
	{
		size_t sz = 16;
		char buff[sz + 1];
		memset(buff, 'i', sizeof(buff));
		buff[sz] = '\0';


		isa::string actual(sz, 'i');
		
		CHECK(actual.size() == sz);
		CHECK(actual.capacity() == sz);
		CHECK(strcmp(actual.c_str(), buff) == 0);

		std::string expected(16, 'i');
		COMPARE_WITH_STD(actual, expected);
	}
}

TEST_CASE("from c-string constructor", tag "[c-string]")
{
	SECTION("must create short string")
	{
		char c_str[] = "0123456789";
		isa::string actual(c_str);
		std::string expected(c_str);

		COMPARE_WITH_STD(actual, expected);
	}
	SECTION("must create long string")
	{
		char c_str[] = "012345678910121315"; // 17
		isa::string actual(c_str);
		std::string expected(c_str);
		
		COMPARE_WITH_STD(actual, expected);
	}
}

TEST_CASE("from buffer constructor", tag "[buffer]")
{
	SECTION("must create short string")
	{
		char buff[10]; 
		memset(buff, 0, sizeof(buff));
		
		isa::string actual(buff, sizeof(buff));
		std::string expected(buff, sizeof(buff));

		COMPARE_WITH_STD(actual, expected);
	}
	SECTION("must create long string")
	{
		char buff[16]; 
		memset(buff, 0, sizeof(buff));
		
		isa::string actual(buff, sizeof(buff));
		std::string expected(buff, sizeof(buff));

		COMPARE_WITH_STD(actual, expected);
	}
}

TEST_CASE("copy constructor", tag "[copy]")
{
	char short_str[] = "short string"; // 15
	char long_str[] = "this is long string 22";
	std::string to_copy_short(short_str);
	std::string to_copy_long(long_str);

	std::string expected_short(to_copy_short);
	std::string expected_long(to_copy_long);

	SECTION("must create short string") 
	{
		isa::string to_copy(short_str);
		isa::string actual(to_copy);
		
		COMPARE_WITH_STD(actual, expected_short);
	}
	SECTION("msut create long string")
	{
		isa::string to_copy(long_str);
		isa::string actual(to_copy);

		COMPARE_WITH_STD(actual, expected_long);
	}
}
