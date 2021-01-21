#include <catch2/catch.hpp>
#include "test_utils.h"

#include "../string.h"

// Unit tests for isa::string::assign functions
// C++11
// Assuming that all construtor tests passed

#define tag "[assign][function]"


const isa::string short_src("short str <= 15");
const isa::string long_src("i am long string with length more than 15 chars");

const std::string std_short("short str <= 15");
const std::string std_long("i am long string with length more than 15 chars");

TEST_CASE("copy assignment", tag "[copy]")
{

	SECTION("must result in short string")
	{
		isa::string res("short string");
		res.assign(short_src);

		CHECK_MY_STRING(res, short_src.size(), short_src.capacity(), short_src.c_str());

		std::string std_s("short string");
		std_s.assign(std_short);
		CMP_MINE_WITH_STD(res, std_s);
	}
	SECTION("must result in long string")
	{
		isa::string res("short");
		res.assign(long_src);

		CHECK_MY_STRING(res, long_src.size(), long_src.capacity(), long_src.c_str());

		std::string std_s("short");
		std_s.assign(std_long);
		CMP_MINE_WITH_STD(res, std_s);
	}
}
