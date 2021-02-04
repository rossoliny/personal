#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// Unit tests for isa::string::resize() 
// C++11

#include "../string.h"
#include "test_utils.h"

#define tag "[reserve]"
const static isa::string::size_type short_max = 15;


TEST_CASE("reserve tests", tag)
{

	SECTION("short target")
	{
		isa::string short_s("short");
		std::string short_std("short");

		SECTION("reserve more than already has, but <= short_max")
		{
			short_s.reserve(short_max);
			
			CHECK_MY_STRING(short_s, 5, short_max, "short");

			short_std.reserve(short_max);
			CMP_MINE_WITH_STD(short_s, short_std);
		}
		SECTION("reserve less than already has")
		{
			short_s.reserve(0);
			
			CHECK_MY_STRING(short_s, 5, short_max, "short");

			short_std.reserve(0);
			CMP_MINE_WITH_STD(short_s, short_std);
		}
		SECTION("reserve 1.5 times more than short_max")
		{
			short_s.reserve(short_max * 1.5);
			
			CHECK_MY_STRING(short_s, 5, short_max * 2, "short");

			short_std.reserve(short_max * 1.5);
			CMP_MINE_WITH_STD(short_s, short_std);
		}
		SECTION("reserve more than 2 * short_max")
		{
			short_s.reserve(short_max * 2 + 1);
			
			CHECK_MY_STRING(short_s, 5, short_max * 2 + 1, "short");

			short_std.reserve(short_max * 2 + 1);
			CMP_MINE_WITH_STD(short_s, short_std);
		}
	}
	SECTION("long string target")
	{
		char orig_str[] = "not short string with heap allocated memory";

		isa::string long_str(orig_str);
		size_t old_sz = long_str.size();
		size_t old_cap = long_str.capacity();
		std::string long_std(orig_str);

		SECTION("reserve more, must double")
		{
			long_str.reserve(old_cap + 1);

			CHECK_MY_STRING(long_str, old_sz, old_cap*2, orig_str);

			long_std.reserve(long_std.capacity() + 1);
			CMP_MINE_WITH_STD(long_str, long_std);
		}
		SECTION("reserve more that 2 * capacity, must become n")
		{
			long_str.reserve(old_cap * 2 + 2);

			CHECK_MY_STRING(long_str, old_sz, old_cap * 2 + 2, orig_str);

			long_std.reserve(long_std.capacity() * 2 + 2);
			CMP_MINE_WITH_STD(long_str, long_std);
		}
		SECTION("reserve less than its capacity")
		{
			long_str.reserve(old_cap / 2);

			CHECK_MY_STRING(long_str, old_sz, old_cap, orig_str);

			long_std.reserve(long_std.capacity() / 2);
			CMP_MINE_WITH_STD(long_str, long_std);
		}
		SECTION("reserve 0")
		{
			long_str.reserve(0);

			CHECK_MY_STRING(long_str, old_sz, old_cap, orig_str);

			long_std.reserve(0);
			CMP_MINE_WITH_STD(long_str, long_std);
		}
	}
	SECTION("reserve too much")
	{
		isa::string s("temp");

		REQUIRE_THROWS_AS(s.reserve(s.max_size() + 1), std::length_error);
	}
}
