#include <catch2/catch.hpp>
#include <string>
#include <cstring>

// Unit tests for isa::string::resize() 
// C++11

#include "../string.h"
#include "test_utils.h"

#define tag "[resize]"
const static isa::string::size_type short_max = 15;

TEST_CASE("resize tests", tag "[fill]")
{
	isa::string short_s("short");
	std::string short_std("short");

	char long_cstr[] = "long long not short string this is long";
	isa::string long_s(long_cstr);
	size_t old_cap = long_s.capacity();
	std::string long_std(long_cstr);

	SECTION("short extend to short")
	{
		short_s.resize(10, 'o');
		
		CHECK_MY_STRING(short_s, 10, short_max, "short" "ooooo");

		short_std.resize(10, 'o');
		CMP_MINE_WITH_STD(short_s, short_std);
	}
	SECTION("short extend to long")
	{
		short_s.resize(20, 'o');
		
		CHECK_MY_STRING(short_s, 20, 30, "short" "ooooo" "ooooo" "ooooo");

		short_std.resize(20, 'o');
		CMP_MINE_WITH_STD(short_s, short_std);
	}
	SECTION("long extend")
	{
		size_t new_sz = long_s.size() + 5;
		long_s.resize(new_sz, 'l');

		long_std.resize(new_sz, 'l');
		CHECK_MY_STRING(long_s, new_sz, old_cap * 2, long_std.data());
		CMP_MINE_WITH_STD(short_s, short_std);
	}
	SECTION("short shrink")
	{
		short_s.resize(1, 'c');

		CHECK_MY_STRING(short_s, 1, short_max, "s");

		short_std.resize(1, 'c');
		CMP_MINE_WITH_STD(short_s, short_std);
	}
	SECTION("long shrink")
	{

	}
	SECTION("illegal size")
	{
		REQUIRE_THROWS_AS(long_s.resize((size_t)-1, 'c'), std::length_error);
	}
}
