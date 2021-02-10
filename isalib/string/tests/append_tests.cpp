#include <catch2/catch.hpp>
#include <cstring>
#include <string>
#include "test_utils.h"

#include "../string.h"

// Unit tests for isa::string::append functions
// C++11
// Assuming that all construtor tests are passed (constructor_tests.cpp)

#define tag "[append][function]"

const static size_t short_max = 15;

const isa::string short_src("short str <= 15");
const isa::string long_src("i am long string with length more than 15 chars");

const std::string short_std("short str <= 15");
const std::string long_std("i am long string with length more than 15 chars");



TEST_CASE("append method", tag "[string]")
{
	const char* old_content = "isa::string s(old_content);";
	isa::string s(old_content);
	size_t old_cap = s.capacity();
	size_t old_size = strlen(old_content);
	
	s.append(short_src);
	
	char exp[old_size + short_src.size() + 1];
	strcpy(exp, old_content);
	strcat(exp, short_src.c_str());
	CHECK_MY_STRING(s, old_size + short_src.size(), old_cap * 2, exp);
}
