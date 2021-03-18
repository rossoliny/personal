//
// Created by Isa on 3/16/21.
//

#ifndef _TEST_UTILS_H
#define _TEST_UTILS_H
#include <ctime>
#include <cstdlib>
static int seed_rand()
{
	srand(time(0));
	return 1;
}

static int dummy = seed_rand();

//#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/catch.hpp"
#include <string>

#include <list>
#include "gcc_list"


// INPUTS
#define rand_ints {rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand()}
#define rand_ints_L {rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), \
					 rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand()}

const static std::initializer_list<int> init_list_1 = rand_ints;
const static std::initializer_list<int> init_list_2 = rand_ints;
const static std::initializer_list<int> init_list_L = rand_ints;

const static std::vector<std::string> vec_str_1 = {"list", "unit", "test", "learn", "gcc std::list", "ab", "cd", "ef", "gh", "ij", "kl", "mnop", "qrstuv", "wxy", "z"};
const static std::vector<std::string> vec_str_2 = {"list2", "unit2", "test2", "learn2", "gcc std::list2", "ab2", "cd2", "ef2", "gh2", "ij2", "kl2", "mnop2", "qrstuv2", "wxy2", "z2"};

// UTILS
#define LISTS_REQUIRE_EQUAL(gcc_list, std_list) (verify((gcc_list), (std_list)))

template<typename Tp, typename Alloc>
void verify(gcc::list<Tp, Alloc>& gcc_list, std::list<Tp, Alloc>& std_list)
{
	REQUIRE(gcc_list.size() == std_list.size());
	REQUIRE(gcc_list.get_allocator() == std_list.get_allocator());
	REQUIRE(gcc_list.max_size() == std_list.max_size());

	REQUIRE(*gcc_list.begin() == *std_list.begin());

	REQUIRE(*--gcc_list.end() == *--std_list.end());

	REQUIRE(*gcc_list.cbegin() == *std_list.cbegin());
	REQUIRE(*--gcc_list.cend() == *--std_list.cend());

	REQUIRE(*gcc_list.rbegin() == *std_list.rbegin());
	REQUIRE(*++gcc_list.rend() == *++std_list.rend());

	REQUIRE(*gcc_list.crbegin() == *std_list.crbegin());
	REQUIRE(*++gcc_list.crend() == *++std_list.crend());

	auto act = gcc_list.begin();
	auto exp = std_list.begin();

	while(act != gcc_list.end())
	{

		REQUIRE(*act == *exp);

		++act;
		++exp;
	}
}

#define CHECK_LISTS_NEQ(gcc_list, std_list) (check_neq((gcc_list), (std_list)))
template<typename Tp, typename Alloc>
bool check_neq(gcc::list<Tp, Alloc>& gcc_list, std::list<Tp, Alloc>& std_list)
{
	if(gcc_list.size() != std_list.size())
		return true;

	auto act = gcc_list.begin();
	auto exp = std_list.begin();

	bool full_match = true;
	while(act != gcc_list.end())
	{
		if(*act != *exp)
		{
			full_match = false;
			break;
		}

		++act;
		++exp;
	}

	CHECK(not full_match);
	return not full_match;
}


#define CREATE_INPUT_LISTS_OF_INT(name) \
	std::initializer_list<int> ___init_list_input___ = rand_ints; \
	gcc_list<int> gcc_##name = ___init_list_input___; \
	std_list<int> std_##name = ___init_list_input___

#define gcc_list gcc::list
#define std_list std::list

using namespace std;

#endif //_TEST_UTILS_H
