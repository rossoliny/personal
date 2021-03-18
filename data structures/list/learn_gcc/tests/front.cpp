//
// Created by Isa on 3/17/21.
//

#include "test_utils.h"

#define tag "[front]"


TEST_CASE("front", tag)
{
	gcc_list<string> act(input_string.begin(), input_string.end());
	gcc_list<string> exp(input_string.begin(), input_string.end());

	REQUIRE(act.front() == exp.front());

	initializer_list<int> rand_int_inp = rand_ints;
	gcc_list<int> act2 = rand_int_inp;
	std_list<int> exp2 = rand_int_inp;

	REQUIRE(act2.front() == exp2.front());
}

TEST_CASE("const front", tag)
{
	gcc_list<string>const act(input_string.begin(), input_string.end());
	gcc_list<string>const exp(input_string.begin(), input_string.end());

	REQUIRE(act.front() == exp.front());

	initializer_list<int> rand_int_inp = rand_ints;
	const gcc_list<int> act2 = rand_int_inp;
	const std_list<int> exp2 = rand_int_inp;

	REQUIRE(act2.front() == exp2.front());
}