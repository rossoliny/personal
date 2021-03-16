//
// Created by Isa on 3/16/21.
//

#include "catch2/catch.hpp"

#include "test_utils.h"
#include <gcc_list>
#include <list>
#include <string>

#define tag "[constructors] [constructor] [ctor]"

using namespace std;

TEST_CASE("default ctor", tag)
{
	gcc::list<std::string> actual = {"list", "test"};
	std::list<std::string> expected = {"list", "test"};

	LISTS_REQUIRE_EQUAL(actual, expected);
}

TEST_CASE("fill ctor", tag)
{
	int n = 100;

	SECTION("default constructed val")
	{
		gcc_list<string> actual(n);
		std_list<string> expected(n);

		LISTS_REQUIRE_EQUAL(actual, expected);
	}
//	SECTION("copy constructed val")
//	{
//		gcc_list<string> act(n);
//		std_list<string> exp(n);
//
//		LISTS_REQUIRE_EQUAL(act, exp);
//	}
}
