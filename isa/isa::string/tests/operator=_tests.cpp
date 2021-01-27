#include <catch2/catch.hpp>
#include <cstring>

#include "test_utils.h"
#include "../string.h"


#define tag "[operators] [operator] [operator=]"

const static size_t short_max = 15;

const isa::string short_src("short str <= 15");
const isa::string long_src("i am long string with length more than 15 chars");

const std::string short_std("short str <= 15");
const std::string long_std("i am long string with length more than 15 chars");

TEST_CASE("single character operator=", tag "[single character] [single char] [single] [char] [character]")
{
	isa::string str1("short str");
	std::string std_s1("short str");
	str1 = 's';
	std_s1 = 's';
	CHECK_MY_STRING(str1, 1, 15, "s");
	CMP_MINE_WITH_STD(str1, std_s1);

	isa::string str2("123456789 123456789 ");
	std::string std_s2("123456789 123456789 ");
	str2 = 'c';
	std_s2 = 'c';
	CHECK_MY_STRING(str2, 1, 20, "c");
	CMP_MINE_WITH_STD(str2, std_s2);
}




TEST_CASE("copy operator=", tag "[copy]")
{
	isa::string str("short string");
	std::string std_s("short string");

	SECTION("must stay short")
	{
		str = short_src;

		CHECK_MY_STRING(str, short_src.size(), short_src.capacity(), short_src.c_str());

		std_s = short_std;
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("must increase capacity")
	{
		str = long_src;

		CHECK_MY_STRING(str, long_src.size(), long_src.capacity(), long_src.c_str());

		std_s = long_std;
		CMP_MINE_WITH_STD(str, std_s);
	}
}




TEST_CASE("move operator=", tag "[move]")
{
	size_t long_len = 25;
	char long_cstr[long_len + 1] = "rvalue with 25 characters";
	isa::string long_tmp(long_cstr);
	std::string long_std_tmp(long_cstr);

	size_t short_len = 15;
	char short_cstr[short_len + 1] = "char rvalue[15]";
	isa::string short_tmp(short_cstr);
	std::string short_std_tmp(short_cstr);


	SECTION("short target")
	{
		isa::string str("short str");
		std::string std_s("short str");

		SECTION("move assign short src")
		{
			str = std::move(short_tmp);
			
			CHECK_MY_STRING(str, short_len, short_max, short_cstr);
			CHECK_MY_STRING(short_tmp, short_len, short_max, short_cstr);

			std_s = std::move(short_std_tmp);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("move assign long src")
		{
			str = std::move(long_tmp);
			
			CHECK_MY_STRING(str, long_len, long_len, long_cstr);
			CHECK_MY_STRING(long_tmp, 0, short_max, "");

			std_s = std::move(long_std_tmp);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("long target")
	{
		isa::string str("long destination string"); // sz = 23
		size_t old_cap = str.capacity();
		std::string std_s("long destination string");

		SECTION("move assign short src")
		{
			str = std::move(short_tmp);
			
			CHECK_MY_STRING(str, short_len, short_max, short_cstr);
			CHECK_MY_STRING(short_tmp, short_len, short_max, short_cstr);

			std_s = std::move(short_std_tmp);
			CHECK_MY_STRING(short_std_tmp, 0, short_max, "");
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("move assign long src")
		{
			str = std::move(long_tmp);
			
			CHECK_MY_STRING(str, long_len, long_len, long_cstr);
			CHECK_MY_STRING(long_tmp, 0, short_max, "");

			std_s = std::move(long_std_tmp);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
}
