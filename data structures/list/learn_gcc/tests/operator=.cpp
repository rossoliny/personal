//
// Created by Isa on 3/17/21.
//

#include "test_utils.h"

#define tag "[operator=] [assign operator] [operator] [operators]"

TEST_CASE("copy assignment operator")
{
	SECTION("shorter = longer")
	{
		initializer_list<int> input = rand_ints_L;
		gcc_list<int> act_inp = input;
		std_list<int> exp_inp = input;

		gcc_list<int> act = rand_ints;
		std_list<int> exp = rand_ints;

		CHECK_LISTS_NEQ(act, exp);

		// shorter = longer
		act = act_inp;
		exp = exp_inp;

		LISTS_REQUIRE_EQUAL(act, exp);
		LISTS_REQUIRE_EQUAL(act_inp, exp_inp);
	}
	SECTION("longer = shorter")
	{
		initializer_list<int> input = rand_ints;
		gcc_list<int> act_inp = input;
		std_list<int> exp_inp = input;

		gcc_list<int> act = rand_ints_L;
		std_list<int> exp = rand_ints_L;

		CHECK_LISTS_NEQ(act, exp);

		act = act_inp;
		exp = exp_inp;

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}


TEST_CASE("move assignment operator")
{
	SECTION("short = long")
	{
		initializer_list<int> input = rand_ints_L;
		gcc_list<int> act_inp = input;
		std_list<int> exp_inp = input;

		gcc_list<int> act = rand_ints;
		std_list<int> exp = rand_ints;

		act = std::move(act_inp);
		exp = std::move(exp_inp);

		LISTS_REQUIRE_EQUAL(act, exp);
		LISTS_REQUIRE_EQUAL(act_inp, exp_inp);
	}
	SECTION("long = short")
	{
		initializer_list<int> input = rand_ints;
		gcc_list<int> act_inp = input;
		std_list<int> exp_inp = input;

		gcc_list<int> act = rand_ints_L;
		std_list<int> exp = rand_ints_L;

		act = std::move(act_inp);
		exp = std::move(exp_inp);

		LISTS_REQUIRE_EQUAL(act, exp);
		LISTS_REQUIRE_EQUAL(act_inp, exp_inp);
	}
}

TEST_CASE("initializer_list assignment operator")
{
	SECTION("short <- long")
	{
		gcc_list<int> act = init_list_1;
		std_list<int> exp = init_list_1;

		act = init_list_L;
		exp = init_list_L;

		LISTS_REQUIRE_EQUAL(act, exp);
	}
	SECTION("long <- short")
	{
		gcc_list<int> act = init_list_L;
		std_list<int> exp = init_list_L;

		act = init_list_1;
		exp = init_list_1;

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}