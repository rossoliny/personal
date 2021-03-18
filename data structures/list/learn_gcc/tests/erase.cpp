//
// Created by Isa on 3/19/21.
//

#include "test_utils.h"

#define tag "[erase]"


TEST_CASE("erase", tag)
{
	SECTION("int")
	{
		CREATE_LISTS_OF_INT(res);

		int n = gcc_res.size() / 2;
		while(n--)
		{
			gcc_res.erase(gcc_res.begin());
			std_res.erase(std_res.begin());
		}

		LISTS_REQUIRE_EQUAL(gcc_res, std_res);
	}
	SECTION("string")
	{
		gcc_list<string> act(vec_str_2.begin(), vec_str_2.end());
		std_list<string> exp(vec_str_2.begin(), vec_str_2.end());

		int n = 10;
		while(n--)
		{
			int adv =  rand() % (act.size() - 1);

			auto it1 = act.begin();
			auto it2 = exp.begin();

			std::advance(it1, adv);
			std::advance(it2, adv);


			act.erase(it1);
			exp.erase(it2);
		}

		LISTS_REQUIRE_EQUAL(act, exp);
	}
}

TEST_CASE("range erase", tag "[range erase]")
{
	CREATE_LISTS_OF_INT(res);

	int adv =  rand() % (gcc_res.size() - 1);

	auto it1 = gcc_res.begin();
	auto it2 = std_res.begin();

	std::advance(it1, adv);
	std::advance(it2, adv);

	gcc_res.erase(gcc_res.begin(), it1);
	std_res.erase(std_res.begin(), it2);

	LISTS_REQUIRE_EQUAL(gcc_res, std_res);
}