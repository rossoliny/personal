#pragma once
#include <cstring>

#ifndef CMP_MINE_WITH_STD
#define CMP_MINE_WITH_STD(actual, expected) 										\
	SECTION("isa::string must be identical to std::string") 						\
	{										 										\
		CHECK(actual.size() == expected.size());									\
		CHECK(actual.capacity() == expected.capacity());  							\
		CHECK(strncmp(actual.c_str(), expected.c_str(), expected.size()) == 0); 	\
	}
#endif // CMP_MINE_WITH_STD


#ifndef CHECK_MY_STRING
#define CHECK_MY_STRING(str, exp_size, exp_capacity, exp_cstr)			\
	{																	\
		CHECK( (str).size() == (exp_size) );							\
		CHECK( (str).capacity() == (exp_capacity) );  					\
		CHECK( strncmp((str).c_str(), (exp_cstr), exp_size) == 0 ); 	\
	}
#endif // CHECK_MY_STRING
