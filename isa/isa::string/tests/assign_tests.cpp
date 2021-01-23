#include <catch2/catch.hpp>
#include "test_utils.h"

#include "../string.h"

// Unit tests for isa::string::assign functions
// C++11
// Assuming that all construtor tests passed

#define tag "[assign][function]"

const static size_t short_max = 15;

const isa::string short_src("short str <= 15");
const isa::string long_src("i am long string with length more than 15 chars");

const std::string short_std("short str <= 15");
const std::string long_std("i am long string with length more than 15 chars");

TEST_CASE("copy assignment", tag "[copy]")
{

	SECTION("must result in short string")
	{
		isa::string res("short string");
		res.assign(short_src);

		CHECK_MY_STRING(res, short_src.size(), short_src.capacity(), short_src.c_str());

		std::string std_s("short string");
		std_s.assign(short_std);
		CMP_MINE_WITH_STD(res, std_s);
	}
	SECTION("must result in long string")
	{
		isa::string res("short");
		res.assign(long_src);

		CHECK_MY_STRING(res, long_src.size(), long_src.capacity(), long_src.c_str());

		std::string std_s("short");
		std_s.assign(long_std);
		CMP_MINE_WITH_STD(res, std_s);
	}
}

TEST_CASE("substring assignment", tag "[substring]")
{
	isa::string str("I am not really short string");
	std::string std_s("I am not really short string");

	SECTION("whole string")
	{
		str.assign(short_src, 0, short_src.size());
		CHECK_MY_STRING(str, short_src.size(), short_src.capacity(), short_src.c_str());

		std_s.assign(short_std, 0, short_std.size());
		CMP_MINE_WITH_STD(str, std_s);
		
		// long
		str.assign(long_src, 0, long_src.size());
		CHECK_MY_STRING(str, long_src.size(), long_src.capacity(), long_src.c_str());

		std_s.assign(long_std, 0, long_std.size());
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("from 0, but not whole string")
	{
		str.assign(short_src, 0, 5);
		CHECK_MY_STRING(str, 5, short_max, "short");

		std_s.assign(short_std, 0, 5);
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("from some pos(not 0) to end")
	{
		str.assign(short_src, 4, short_src.size() - 4);
		CHECK_MY_STRING(str, short_src.size() - 4, short_max, short_src.c_str() + 4);

		std_s.assign(short_std, 4, short_std.size() - 4);
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("if len bigger than source string than copy until end")
	{
		str.assign(long_src, 10, 123456);
		CHECK_MY_STRING(str, long_src.size() - 10, long_src.capacity() - 10, long_src.c_str() + 10);

		std_s.assign(long_std, 10, 123456);
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("if len is string::npos then copy until end")
	{
		str.assign(long_src, 5, isa::string::npos);
		CHECK_MY_STRING(str, long_src.size() - 5, long_src.capacity() - 5, long_src.c_str() + 5);

		std_s.assign(long_std, 5, std::string::npos);
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("if pos is greater than source length then must throw isa::out_of_range")
	{
		REQUIRE_THROWS_AS(std_s.assign(long_std, long_std.size() + 1, 10), std::out_of_range);
		REQUIRE_THROWS_AS(str.assign(long_src, long_src.size() + 1, 10), isa::out_of_range);
	}
}
