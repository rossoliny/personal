#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// TODO: I MUST NOT CHANGE THE STRUCTURE ANYMORE
// TODO: I MUST NOT CHANGE THE STRUCTURE ANYMORE
// TODO: I MUST NOT CHANGE THE STRUCTURE ANYMORE
// TODO: I MUST NOT CHANGE THE STRUCTURE ANYMORE

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
		char buff[4] = "iii";

		isa::string str(3, 'i');
		CHECK_MY_STRING(str, 3, short_max, buff);

		std::string std_str(3, 'i');
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		char buff[17] = "iiiiiiiiii" "iiiiii";

		isa::string str(16, 'i');
		CHECK_MY_STRING(str, 16, 16, buff);

		std::string std_str(16, 'i');
		CMP_MINE_WITH_STD(str, std_str);
	}
}

TEST_CASE("from c-string constructor", tag "[c-string]")
{
	SECTION("must create short string")
	{
		char c_str[] = "0123456789" "12345"; // 15

		isa::string str(c_str);
		CHECK_MY_STRING(str, 15, short_max, c_str);

		std::string std_str(c_str);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		char c_str[] = "0123456789" "123456"; // 16

		isa::string str(c_str);
		CHECK_MY_STRING(str, 16, 16, c_str);

		std::string std_str(c_str);
		CMP_MINE_WITH_STD(str, std_str);
	}
}

TEST_CASE("from buffer constructor", tag "[buffer]")
{
	SECTION("must create short string")
	{
		char buff[15];
		memset(buff, 'c', 15);
		
		isa::string str(buff, 15);
		CHECK_MY_STRING(str, 15, short_max, buff);

		std::string std_str(buff, 15);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		char buff[16]; 
		memset(buff, 'c', 16);

		isa::string str(buff, 16);
		CHECK_MY_STRING(str, 16, 16, buff);

		std::string std_str(buff, 16);
		CMP_MINE_WITH_STD(str, std_str);
	}
}

TEST_CASE("copy constructor", tag "[copy]")
{
	SECTION("must create short string") 
	{
		char short_cstr[] = "short string 15"; // 15
		isa::string to_copy(short_cstr);

		isa::string str(short_cstr);
		CHECK_MY_STRING(str, to_copy.size(), to_copy.capacity(), to_copy.c_str());
		CHECK_MY_STRING(str, 15, 15, short_cstr);

		std::string std_to_copy(short_cstr);
		std::string std_str(std_to_copy);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("msut create long string")
	{
		char long_cstr[] = "i am long string";
		isa::string to_copy(long_cstr);

		isa::string str(long_cstr);
		CHECK_MY_STRING(str, to_copy.size(), to_copy.capacity(), to_copy.c_str());
		CHECK_MY_STRING(str, 16, 16, long_cstr);

		std::string std_to_copy(long_cstr);
		std::string std_str(std_to_copy);
		CMP_MINE_WITH_STD(str, std_str);
	}
}

TEST_CASE("substring constructor", tag "[substring]")
{
	isa::string src("01234" "56789" "01234" "56789");

	SECTION("must create short string")
	{
		isa::string str(src, 5, 15);

		CHECK_MY_STRING(str, 15, short_max, "56789" "01234" "56789");
	}
	SECTION("must create long string")
	{
		
	}

}

