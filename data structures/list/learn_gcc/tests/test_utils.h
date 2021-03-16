//
// Created by Isa on 3/16/21.
//

#ifndef _TEST_UTILS_H
#define _TEST_UTILS_H
#include "catch2/catch.hpp"
#include <list>
#include "gcc_list"


#define LISTS_REQUIRE_EQUAL(gcc_list, std_list) (verify((gcc_list), (std_list)))

template<typename Tp, typename Alloc>
void verify(gcc::list<Tp, Alloc>& gcc_list, std::list<Tp, Alloc>& std_list)
{
	REQUIRE(gcc_list.size() == std_list.size());
	REQUIRE(gcc_list.get_allocator() == std_list.get_allocator());
	REQUIRE(gcc_list.max_size() == std_list.max_size());

	REQUIRE(*gcc_list.begin() == *std_list.begin());

	auto v1 = gcc_list.end();
	auto v2 = std_list.end();

	auto v1d = *v1;
	auto v2d = *v2;

	REQUIRE(v1d == v2d);

	REQUIRE(*gcc_list.cbegin() == *std_list.cbegin());
	REQUIRE(*gcc_list.cend() == *std_list.cend());

	REQUIRE(*gcc_list.rbegin() == *std_list.rbegin());
	REQUIRE(*gcc_list.rend() == *std_list.rend());

	REQUIRE(*gcc_list.crbegin() == *std_list.crbegin());
	REQUIRE(*gcc_list.crend() == *std_list.crend());

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

#endif //_TEST_UTILS_H
