//
// Created by Isa on 3/17/21.
//

#include "test_utils.h"

#define tag "[front]"


TEST_CASE("front", tag)
{
	gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
	gcc_list<string> exp(vec_str_1.begin(), vec_str_1.end());

	REQUIRE(act.front() == exp.front());

	initializer_list<int> rand_int_inp = rand_ints;
	gcc_list<int> act2 = rand_int_inp;
	std_list<int> exp2 = rand_int_inp;

	REQUIRE(act2.front() == exp2.front());
}

TEST_CASE("const front", tag)
{
	gcc_list<string>const act(vec_str_1.begin(), vec_str_1.end());
	gcc_list<string>const exp(vec_str_1.begin(), vec_str_1.end());

	REQUIRE(act.front() == exp.front());

	initializer_list<int> rand_int_inp = rand_ints;
	const gcc_list<int> act2 = rand_int_inp;
	const std_list<int> exp2 = rand_int_inp;

	REQUIRE(act2.front() == exp2.front());
}


#undef tag
#define tag "[back]"


TEST_CASE("back", tag)
{
	gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
	gcc_list<string> exp(vec_str_1.begin(), vec_str_1.end());

	REQUIRE(act.back() == exp.back());

	initializer_list<int> rand_int_inp = rand_ints;
	gcc_list<int> act2 = rand_int_inp;
	std_list<int> exp2 = rand_int_inp;

	REQUIRE(act2.back() == exp2.back());
}

TEST_CASE("const back", tag)
{
	gcc_list<string>const act(vec_str_1.begin(), vec_str_1.end());
	gcc_list<string>const exp(vec_str_1.begin(), vec_str_1.end());

	REQUIRE(act.back() == exp.back());

	initializer_list<int> rand_int_inp = rand_ints;
	const gcc_list<int> act2 = rand_int_inp;
	const std_list<int> exp2 = rand_int_inp;

	REQUIRE(act2.back() == exp2.back());
}