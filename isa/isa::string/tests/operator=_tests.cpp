#include <catch2/catch.hpp>
#include <cstring>

#include "test_utils.h"
#include "../string.h"


#define tag "[operators] [operator] [operator=]"

TEST_CASE("test", tag)
{
	isa::string str("123456789 123456789 ");

	str = 'c';

	CHECK_MY_STRING(str, 1, 20, "c");
}
