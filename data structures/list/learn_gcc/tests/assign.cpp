//
// Created by Isa on 3/18/21.
//

#include "test_utils.h"
#define tag "[assign]"


TEST_CASE("range assing", tag)
{
	CREATE_LISTS_OF_INT(inp);

	gcc_list<int> act = rand_ints;
	std_list<int> exp = rand_ints;

	CHECK_LISTS_NEQ(act, exp);

	act.assign(gcc_inp.begin(), gcc_inp.end());
	exp.assign(std_inp.begin(), std_inp.end());

	LISTS_REQUIRE_EQUAL(act, exp);
}

TEST_CASE("fill assign", tag)
{
	SECTION("short << long")
	{
		gcc_list<int> act = rand_ints;
		std_list<int> exp = rand_ints;

		CHECK_LISTS_NEQ(act, exp);

		size_t n = rand() % (100 - act.size() + 1) + act.size();
		int val = rand() + 1;

		act.assign(n, val);
		exp.assign(n, val);

		LISTS_REQUIRE_EQUAL(act, exp);
	}
	SECTION("long << short")
	{
		gcc_list<int> act = rand_ints_L;
		std_list<int> exp = rand_ints_L;

		CHECK_LISTS_NEQ(act, exp);

		size_t n = rand() % (act.size()) + 1;
		int val = rand() + 1;

		act.assign(n, val);
		exp.assign(n, val);

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}

TEST_CASE("initializer_list assign", tag)
{
	gcc_list<int> act = rand_ints;
	std_list<int> exp = rand_ints;

	CHECK_LISTS_NEQ(act, exp);

	act.assign(init_list_1);
	exp.assign(init_list_1);

	LISTS_REQUIRE_EQUAL(act, exp);

	act.assign(init_list_2);
	exp.assign(init_list_2);
	LISTS_REQUIRE_EQUAL(act, exp);

}