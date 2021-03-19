//
// Created by Isa on 3/19/21.
//

#include "test_utils.h"

#define tag "[insert]"


TEST_CASE("insert single element", tag)
{
	CREATE_LISTS_OF_INT(l);

	auto pos1 = gcc_l.begin();
	auto pos2 = std_l.begin();
	advance(pos1, rand() % gcc_l.size() + 1);
	advance(pos2, rand() % std_l.size() + 1);

	int val = rand();

	gcc_l.insert(pos1, val);
	std_l.insert(pos2, val);
}

TEST_CASE("fill insert", tag)
{

}

TEST_CASE("range insert", tag)
{

}

TEST_CASE("move insert", tag)
{

}

TEST_CASE("initializer list insert", tag)
{

}