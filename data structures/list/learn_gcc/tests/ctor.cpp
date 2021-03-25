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
	std::allocator<std::string> alloc;
	gcc::list<std::string> m(alloc);

	gcc::list<std::string> actual;
	std::list<std::string> expected;


	// dereference iterator of empty list is UB
	string act_str(*actual.begin());
	string exp_str(*expected.begin());

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

	gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
	std_list<string> exp(vec_str_1.begin(), vec_str_1.end());

	LISTS_REQUIRE_EQUAL(act, exp);
}


TEST_CASE("copy ctor", tag)
{
	SECTION("with default allocator")
	{
		gcc_list<string> act_inp(vec_str_1.begin(), vec_str_1.end());
		std_list<string> exp_inp(vec_str_1.begin(), vec_str_1.end());

		gcc_list<string> act(act_inp);
		std_list<string> exp(exp_inp);

		LISTS_REQUIRE_EQUAL(act, exp);
	}
	SECTION("with given allocator")
	{
		gcc_list<string> act_inp(vec_str_1.begin(), vec_str_1.end());
		std_list<string> exp_inp(vec_str_1.begin(), vec_str_1.end());

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

		gcc_list<string> act_inp(vec_str_1.begin(), vec_str_1.end());
		std_list<string> exp_inp(vec_str_1.begin(), vec_str_1.end());

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
	gcc_list<std::string> actual = initialize_list;
	std_list<std::string> expected = initialize_list;

	LISTS_REQUIRE_EQUAL(actual, expected);
}

TEST_CASE("clear", "[clear]")
{
	SECTION("int")
	{
		CREATE_LISTS_OF_INT(res);

		gcc_res.clear();
		std_res.clear();

		LISTS_REQUIRE_EQUAL(gcc_res, std_res);
	}
	SECTION("string")
	{
		gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
		std_list<string> exp(vec_str_1.begin(), vec_str_1.end());

		act.clear();
		exp.clear();

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}