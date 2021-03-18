//
// Created by Isa on 3/18/21.
//
#include "test_utils.h"


TEST_CASE("push back", "[push_back]")
{
	gcc_list<int> act = init_list_1;
	std_list<int> exp = init_list_1;

	int N = rand() % 100 + 1;

	while(N--)
	{
		int n = rand();
		exp.push_back(n);
		act.push_back(n);
	}

	LISTS_REQUIRE_EQUAL(act, exp);
}

TEST_CASE("push front", "[push_front]")
{
	SECTION("int")
	{
		gcc_list<int> act = init_list_2;
		std_list<int> exp = init_list_2;

		int N = rand() % 100 + 1;

		while(N--)
		{
			int n = rand();
			exp.push_front(n);
			act.push_front(n);
		}

		LISTS_REQUIRE_EQUAL(act, exp);
	}
	SECTION("string")
	{
		gcc_list<string> act;
		std_list<string> exp;

		int N = rand() % 100 + 1;

		while(N--)
		{
			int n = rand() % 100 + 1;
			char c = (n % (255 - 32 + 1) + 32);
			string s(n, c);

			exp.push_front(s);
			act.push_front(s);
		}

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}

TEST_CASE("pop back", "[pop_back]")
{
	gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
	std_list<string> exp(vec_str_1.begin(), vec_str_1.end());

	int n = rand() % vec_str_1.size()  + 1;
	while (n--)
	{
		act.pop_back();
		exp.pop_back();
	}

	LISTS_REQUIRE_EQUAL(act, exp);
}

TEST_CASE("pop front", "[pop_front]")
{
	gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
	std_list<string> exp(vec_str_1.begin(), vec_str_1.end());

	int n = rand() % vec_str_1.size()  + 1;
	while (n--)
	{
		act.pop_front();
		exp.pop_front();
	}

	LISTS_REQUIRE_EQUAL(act, exp);
}

