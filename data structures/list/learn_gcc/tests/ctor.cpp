//
// Created by Isa on 3/16/21.
//
#include "test_utils.h"

#include <string>

#define tag "[constructors] [constructor] [ctor]"

using namespace std;

TEST_CASE("default ctor", tag)
{
	gcc::list<std::string> actual = {"list", "unit", "test", "learn",  "gcc std::list"};
	std::list<std::string> expected = {"list", "unit", "test", "learn", "gcc std::list"};

	LISTS_REQUIRE_EQUAL(actual, expected);
}

TEST_CASE("fill ctor", tag)
{
	SECTION("default constructed elements")
	{
		int n = 100;
		gcc_list<string> actual(n);
		std_list<string> expected(n);

		LISTS_REQUIRE_EQUAL(actual, expected);
	}
	SECTION("copy constructed elements")
	{
		int n = 20000;
		gcc_list<string> actual(n, "isa");
		std_list<string> expected(n, "isa");

		LISTS_REQUIRE_EQUAL(actual, expected);

		BENCHMARK("gcc::list ctor n = " + to_string(n) ) { return gcc_list<string> (n, "isa"); };
		BENCHMARK("std::list ctor n = " + to_string(n)) { return std_list<string> (n, "isa"); };
	}

}