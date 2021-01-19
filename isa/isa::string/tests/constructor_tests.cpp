#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// Unit tests for isa::string constructors
// std=c++11
#include "../string.h"
#include "test_utils.h"

#define tag "[constructors]"
const static isa::string::size_type short_max = 15;

TEST_CASE("default constructor must create short string", tag "[default]")
{
	isa::string str;
	std::string std_str;
	
	CHECK_MY_STRING(str, 0, short_max, "");

	CMP_MINE_WITH_STD(str, std_str);
}

TEST_CASE("fill constructor", tag "[fill]")
{

	SECTION("must create short string")
	{
		size_t sz = 10;
		char buff[sz + 1];
		memset(buff, 'i', sizeof(buff));
		buff[sz] = '\0';

		isa::string str(sz, 'i');

		CHECK_MY_STRING(str, sz, short_max, buff);

		std::string std_str(sz, 'i');
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		size_t sz = 16;
		char buff[sz + 1];
		memset(buff, 'i', sizeof(buff));
		buff[sz] = '\0';

		isa::string str(sz, 'i');
		
		CHECK_MY_STRING(str, sz, sz, buff);

		std::string std_str(16, 'i');
		CMP_MINE_WITH_STD(str, std_str);
	}
}

TEST_CASE("from c-string constructor", tag "[c-string]")
{
	SECTION("must create short string")
	{
		char c_str[] = "0123456789";
		isa::string actual(c_str);
		std::string expected(c_str);

		CMP_MINE_WITH_STD(actual, expected);
	}
	SECTION("must create long string")
	{
		char c_str[] = "012345678910121315"; // 17
		isa::string actual(c_str);
		std::string expected(c_str);
		
		CMP_MINE_WITH_STD(actual, expected);
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

		CMP_MINE_WITH_STD(actual, expected);
	}
	SECTION("must create long string")
	{
		char buff[16]; 
		memset(buff, 0, sizeof(buff));
		
		isa::string actual(buff, sizeof(buff));
		std::string expected(buff, sizeof(buff));

		CMP_MINE_WITH_STD(actual, expected);
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
		
		CMP_MINE_WITH_STD(actual, expected_short);
	}
	SECTION("msut create long string")
	{
		isa::string to_copy(long_str);
		isa::string actual(to_copy);

		CMP_MINE_WITH_STD(actual, expected_long);
	}
}
