//
// Created by Isa on 3/18/21.
//

#include "test_utils.h"
#define tag "[emplace]"


TEST_CASE("emplace", tag)
{
	gcc_list<string> act(vec_str_1.begin(), vec_str_1.end());
	std_list<string> exp(vec_str_1.begin(), vec_str_1.end());

	act.emplace(act.begin());
	exp.emplace(exp.begin());

	act.emplace(act.begin(), "emplace test");
	exp.emplace(exp.begin(), "emplace test");

	act.emplace(act.begin(), 100, 'S');
	exp.emplace(exp.begin(), 100, 'S');

	string const s = "QWERTYUIOP[]";
	act.emplace(act.begin(), s.begin(), s.end());
	exp.emplace(exp.begin(), s.begin(), s.end());

	LISTS_REQUIRE_EQUAL(act, exp);
}

TEST_CASE("emplace back", tag "[back]" )
{
	gcc_list< std::pair<int,char> > act;
	std_list< std::pair<int,char> > exp;

	act.emplace_back(10, 'a');
	act.emplace_back(20, 'b');
	act.emplace_back(30, 'c');

	exp.emplace_back(10, 'a');
	exp.emplace_back(20, 'b');
	exp.emplace_back(30, 'c');

	LISTS_REQUIRE_EQUAL(act, exp);
}

TEST_CASE("emplace front", tag "[front]")
{
	gcc_list< std::pair<int,char> > act;
	std_list< std::pair<int,char> > exp;

	act.emplace_front(10, 'a');
	act.emplace_front(20, 'b');
	act.emplace_front(30, 'c');

	exp.emplace_front(10, 'a');
	exp.emplace_front(20, 'b');
	exp.emplace_front(30, 'c');

	LISTS_REQUIRE_EQUAL(act, exp);
}