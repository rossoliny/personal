#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// TODO: I MUST NOT CHANGE THE STRUCTURE ANYMORE

// Unit tests for isa::string constructors
// C++11

#include "../string.h"
#include "test_utils.h"

#define tag "[constructors] [constructor]"
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
	char buff[17] = "iiiiiiiiii" "iiiiii";

	SECTION("must create short string")
	{
		char buff[4] = "iii";

		isa::string str(3, 'i');
		CHECK_MY_STRING(str, 3, short_max, buff + 13);

		std::string std_str(3, 'i');
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		isa::string str(16, 'i');
		CHECK_MY_STRING(str, 16, 16, buff);

		std::string std_str(16, 'i');
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("when too long must throw std::length_error")
	{
		size_t max_size_t = -1;
		REQUIRE_THROWS_AS(isa::string(max_size_t, 'i'), std::length_error);
	}
}

TEST_CASE("from c-string constructor", tag "[c-string]")
{
	char c_str[] = "0123456789" "123456"; // len 16 sz 17

	SECTION("must create short string")
	{
		c_str[15] = '\0'; // now len is 15

		isa::string str(c_str);
		CHECK_MY_STRING(str, 15, short_max, c_str);

		std::string std_str(c_str);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		isa::string str(c_str);
		CHECK_MY_STRING(str, 16, 16, c_str);

		std::string std_str(c_str);
		CMP_MINE_WITH_STD(str, std_str);
	}
}

TEST_CASE("from buffer constructor", tag "[buffer]")
{
	char buff[16]; 
	memset(buff, 'c', 16);

	SECTION("must create short string")
	{	
		isa::string str(buff, 15);
		CHECK_MY_STRING(str, 15, short_max, buff);

		std::string std_str(buff, 15);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		isa::string str(buff, 16);
		CHECK_MY_STRING(str, 16, 16, buff);

		std::string std_str(buff, 16);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("when too long must throw")
	{
		REQUIRE_THROWS_AS(isa::string(nullptr, std::numeric_limits<size_t>::max()), std::length_error);
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
		CHECK_MY_STRING(str, 15, short_max, short_cstr);

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
	std::string std_src("01234" "56789" "01234" "56789");

	SECTION("must create short string")
	{
		isa::string str(src, 5, 15);

		CHECK_MY_STRING(str, 15, short_max, "56789" "01234" "56789");

		std::string std_str(std_src, 5, 15);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		isa::string str(src, 4, 16);

		CHECK_MY_STRING(str, 16, 16, "4" "56789" "01234" "56789");

		std::string std_str(std_src, 4, 16);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must copy everything until the end")
	{
		isa::string str(src, 1, isa::string::npos);

		CHECK_MY_STRING(str, 19, 19, "1234" "56789" "01234" "56789");

		std::string std_str(std_src, 1, std::string::npos);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("when start > src.size() must throw isa::out_of_range")
	{
		REQUIRE_THROWS_AS(isa::string(src, src.size() + 1, isa::string::npos), isa::out_of_range);
	}
	SECTION("when start < 0 must throw isa::out_of_range")
	{
		REQUIRE_THROWS_AS(isa::string(src, -1, isa::string::npos), isa::out_of_range);
	}
}

TEST_CASE("move constructor", tag "[move]")
{
	isa::string short_str("short string 15");
	isa::string long_str("long string = 16");

	SECTION("must create short string and not steal resources")
	{
		isa::string str( std::move(short_str) );
		
		CHECK_MY_STRING(str, 15, short_max, "short string 15");
		CHECK_MY_STRING(short_str, 15, short_max, "short string 15");

		std::string std_str( std::move(std::string("short string 15")) );	
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string and must steal resources")
	{
		isa::string str( std::move(long_str) );
		
		CHECK_MY_STRING(str, 16, 16, "long string = 16");
		CHECK_MY_STRING(long_str, 0, short_max, "");

		std::string std_str( std::move(std::string("long string = 16")) );	
		CMP_MINE_WITH_STD(str, std_str);
	}
}


TEST_CASE("range constructor", tag "[range]")
{
	char src[33] = "this is some string of length 32";

	SECTION("must create short string")
	{
		isa::string str(src + 17, src + 32);

		CHECK_MY_STRING(str, 15, 15, "ng of length 32");

		std::string std_str(src + 17, src + 32);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		isa::string str(src, src + 32);

		CHECK_MY_STRING(str, 32, 32, src);

		std::string std_str(src, src + 32);
		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("when too long buffer must throw")
	{
		char* begin = (char*) std::numeric_limits<intptr_t>::min();
		char* end = (char*) std::numeric_limits<intptr_t>::max();

		REQUIRE_THROWS_AS(isa::string(begin, end), std::length_error);
	}
}

TEST_CASE("from initializer list constructor", tag "[initializer list]")
{
	SECTION("must create short string")
	{
		isa::string str = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',	\
	   						'1', '2', '3', '4', '5' };

		CHECK_MY_STRING(str, 15, short_max, "01234" "56789" "12345");

		std::string std_str = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',	\
	   						'1', '2', '3', '4', '5' };

		CMP_MINE_WITH_STD(str, std_str);
	}
	SECTION("must create long string")
	{
		isa::string str = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',	 \
	   						'1', '2', '3', '4', '5', '6'};

		CHECK_MY_STRING(str, 16, 16, "01234" "56789" "12345" "6");

		std::string std_str = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',	 \
	   						'1', '2', '3', '4', '5', '6' };

		CMP_MINE_WITH_STD(str, std_str);
	}
}
