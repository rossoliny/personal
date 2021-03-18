//
// Created by Isa on 3/16/21.
//
#include "test_utils.h"

#include <string>
#include <vector>
#include <memory>


#define tag "[constructors] [constructor] [ctor]"

using namespace std;

TEST_CASE("default ctor", tag)
{
	gcc::list<std::string> actual;
	std::list<std::string> expected;

	gcc_list<string>::iterator act = actual.begin();
	std_list<string>::iterator exp = expected.begin();

	string act_str(*act);
	string exp_str(*exp);

	REQUIRE(act_str == exp_str);

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
		int n = 2000;
		gcc_list<string> actual(n, "isa");
		std_list<string> expected(n, "isa");

		LISTS_REQUIRE_EQUAL(actual, expected);
	}

}

TEST_CASE("range ctor", tag)
{

	gcc_list<string> act(input_string.begin(), input_string.end());
	std_list<string> exp(input_string.begin(), input_string.end());

	LISTS_REQUIRE_EQUAL(act, exp);
}


TEST_CASE("copy ctor", tag)
{
	SECTION("with default allocator")
	{
		gcc_list<string> act_inp(input_string.begin(), input_string.end());
		std_list<string> exp_inp(input_string.begin(), input_string.end());

		gcc_list<string> act(act_inp);
		std_list<string> exp(exp_inp);

		LISTS_REQUIRE_EQUAL(act, exp);
	}
	SECTION("with given allocator")
	{
		gcc_list<string> act_inp(input_string.begin(), input_string.end());
		std_list<string> exp_inp(input_string.begin(), input_string.end());

		std::allocator<void> alloc;
		gcc_list<string> act(act_inp, alloc);
		std_list<string> exp(exp_inp, alloc);

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}

TEST_CASE("move ctor", tag)
{
	SECTION("with default allocator argument")
	{

		gcc_list<string> act_inp(input_string.begin(), input_string.end());
		std_list<string> exp_inp(input_string.begin(), input_string.end());

		gcc_list<string> act(std::move(act_inp));
		std_list<string> exp(std::move(exp_inp));

		LISTS_REQUIRE_EQUAL(act, exp);
	}
	SECTION("with given allocator argument")
	{
		vector<string> inp = {"asdf", "fdsf", "fdefg", "fdj", "fjhrii", "fda", "fhiuro", "fruibvn", "fkjoruvn", "fjhiur"};

		gcc_list<string> act_inp(inp.begin(), inp.end());
		std_list<string> exp_inp(inp.begin(), inp.end());

		std::allocator<void> alloc;
		gcc_list<string> act(std::move(act_inp), alloc);
		std_list<string> exp(std::move(exp_inp), alloc);

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}

TEST_CASE("initializer_list ctor", tag)
{
	initializer_list<string> initialize_list = {"list", "unit", "test", "learn", "gcc std::list"};
	gcc::list<std::string> actual = initialize_list;
	std::list<std::string> expected = initialize_list;

	LISTS_REQUIRE_EQUAL(actual, expected);
}