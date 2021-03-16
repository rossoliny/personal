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
	SECTION("1")
	{
		int n = 11;
		gcc_list<string> actual(n, "isa");
		std_list<string> expected(n, "isa");

		LISTS_REQUIRE_EQUAL(actual, expected);
	}

}