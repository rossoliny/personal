//
// Created by Isa on 3/19/21.
//

#include "test_utils.h"

TEST_CASE("swap", "[swap]")
{
	CREATE_LISTS_OF_INT(list1);
	CREATE_LISTS_OF_INT(list2);

	gcc_list<int> gcc_list1_cpy = gcc_list1;

	gcc_list1.swap(gcc_list2);
	std_list1.swap(std_list2);

	LISTS_REQUIRE_EQUAL(gcc_list1, std_list1);
	LISTS_REQUIRE_EQUAL(gcc_list2, gcc_list1_cpy);
}

TEST_CASE("std::swap", "[swap]")
{
	CREATE_LISTS_OF_INT(list1);
	CREATE_LISTS_OF_INT(list2);

	gcc_list<int> gcc_list1_cpy = gcc_list1;

	std::swap(gcc_list1, gcc_list2);
	std::swap(std_list1, std_list2);

	LISTS_REQUIRE_EQUAL(gcc_list1, std_list1);
	LISTS_REQUIRE_EQUAL(gcc_list2, gcc_list1_cpy);

}

TEST_CASE("resize default", "[resize]")
{
	CREATE_LISTS_OF_INT(res);

	gcc_list<string> act_S(vec_str_1.begin(), vec_str_1.end());
	std_list<string> exp_S(vec_str_1.begin(), vec_str_1.end());

	SECTION("shrink")
	{
		int n = gcc_res.size() / 2;

		gcc_res.resize(n);
		std_res.resize(n);

		LISTS_REQUIRE_EQUAL(gcc_res, std_res);

		// with string
		act_S.resize(act_S.size() / 2);
		exp_S.resize(exp_S.size() / 2);

		LISTS_REQUIRE_EQUAL(act_S, exp_S);
	}
	SECTION("expand")
	{
		int n = gcc_res.size() * 2;

		gcc_res.resize(n);
		std_res.resize(n);

		LISTS_REQUIRE_EQUAL(gcc_res, std_res);

		// with string
		act_S.resize(act_S.size() * 2);
		exp_S.resize(exp_S.size() * 2);

		LISTS_REQUIRE_EQUAL(act_S, exp_S);
	}
}

TEST_CASE("resize copy", "[resize]")
{
	CREATE_LISTS_OF_INT(res);

	gcc_list<string> act_S(vec_str_1.begin(), vec_str_1.end());
	std_list<string> exp_S(vec_str_1.begin(), vec_str_1.end());

	SECTION("shrink")
	{
		int n = gcc_res.size() / 2;
		int val = rand();

		gcc_res.resize(n, val);
		std_res.resize(n, val);

		LISTS_REQUIRE_EQUAL(gcc_res, std_res);

		// with string
		string val_s = "string";

		act_S.resize(act_S.size() / 2, val_s);
		exp_S.resize(exp_S.size() / 2, val_s);

		LISTS_REQUIRE_EQUAL(act_S, exp_S);
	}
	SECTION("expand")
	{
		int n = gcc_res.size() * 2;

		int val = rand();

		gcc_res.resize(n, val);
		std_res.resize(n, val);

		LISTS_REQUIRE_EQUAL(gcc_res, std_res);

		// with string
		string val_s = "string";

		act_S.resize(act_S.size() / 2, val_s);
		exp_S.resize(exp_S.size() / 2, val_s);

		LISTS_REQUIRE_EQUAL(act_S, exp_S);
	}
}
