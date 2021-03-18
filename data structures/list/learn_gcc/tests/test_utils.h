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



const static std::vector<std::string> input_string = {"list", "unit", "test", "learn", "gcc std::list", "ab", "cd", "ef", "gh", "ij", "kl", "mnop", "qrstuv", "wxy", "z"};
const static std::vector<std::string> input_string_2 = {"list2", "unit2", "test2", "learn2", "gcc std::list2", "ab2", "cd2", "ef2", "gh2", "ij2", "kl2", "mnop2", "qrstuv2", "wxy2", "z2"};

#define rand_ints {rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand()}
const static std::initializer_list<int> input_int = rand_ints;
const static std::initializer_list<int> intput_int_initializer_list = rand_ints;


#define LISTS_REQUIRE_EQUAL(gcc_list, std_list) (verify((gcc_list), (std_list)))

template<typename Tp, typename Alloc>
void verify(gcc::list<Tp, Alloc>& gcc_list, std::list<Tp, Alloc>& std_list)
{

	REQUIRE(gcc_list.size() == std_list.size());
	REQUIRE(gcc_list.get_allocator() == std_list.get_allocator());
	REQUIRE(gcc_list.max_size() == std_list.max_size());

	auto b1 = gcc_list.begin();
	auto b2 = std_list.begin();
	auto s1 = *b1;
	auto s2 = *b2;

	REQUIRE(s1 == s2);

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

#define gcc_list gcc::list
#define std_list std::list

using namespace std;

#endif //_TEST_UTILS_H
