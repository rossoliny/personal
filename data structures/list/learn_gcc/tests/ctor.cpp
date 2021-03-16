//
// Created by Isa on 3/16/21.
//

#include "catch2/catch.hpp"

#include "list"
#include <string>

#define tag "[constructors] [constructor]"


TEST_CASE("default ctor", tag)
{
	gcc::list<std::string> l = {"list", "test"};

	REQUIRE(l.size() == 2);
	REQUIRE(*l.begin() == "list");
	REQUIRE(*++l.begin() == "test");

}