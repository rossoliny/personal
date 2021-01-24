#include <catch2/catch.hpp>
#include "test_utils.h"

#include "../string.h"

// Unit tests for isa::string::assign functions
// C++11
// Assuming that all construtor tests passed

#define tag "[assign][function]"

const static size_t short_max = 15;

const isa::string short_src("short str <= 15");
const isa::string long_src("i am long string with length more than 15 chars");

const std::string short_std("short str <= 15");
const std::string long_std("i am long string with length more than 15 chars");

TEST_CASE("copy assignment", tag "[copy]")
{
	isa::string res("short string");
	std::string std_s("short string");

	SECTION("must result in short string")
	{
		res.assign(short_src);

		CHECK_MY_STRING(res, short_src.size(), short_src.capacity(), short_src.c_str());

		std_s.assign(short_std);
		CMP_MINE_WITH_STD(res, std_s);
	}
	SECTION("must result in long string")
	{
		res.assign(long_src);

		CHECK_MY_STRING(res, long_src.size(), long_src.capacity(), long_src.c_str());

		std_s.assign(long_std);
		CMP_MINE_WITH_STD(res, std_s);
	}
}

TEST_CASE("substring assignment", tag "[substring]")
{
	// std::string is much smarter than mine. When it already has enough space it does not reallocate.
	// in case when it has allocated mem and it's new size <= short_max <= capacity() it uses allocated mem.
	// And if you call capacity() you'll not get short_max, but it's previous capacity;
	//
	// My string checks its size to figure out if it's currently short or long, that is why
	// it is impossible to mimic std::string behaviour in such cases.
	// When my string has allocated mem and you assign a short string to it then it's size will be <= short_max
	// and that is why if you call capacity() it will return short_max, but not real size of allocated block;
	//
	// UPD: Fixed. Now my string uses pointer comparison to figure out wheather it's small or not.
	// It allowed to copy behabiour of std::string.
	
	SECTION("assign to long string")
	{
		isa::string str("I am not really short string");
		size_t old_cap = str.capacity();
		std::string std_s("I am not really short string");

		SECTION("must copy whole string and preserve old capacity as it's already enough")
		{
			str.assign(short_src, 0, short_src.size());
			CHECK_MY_STRING(str, short_src.size(), old_cap, short_src.c_str());

			std_s.assign(short_std, 0, short_std.size());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity and copy whole string")
		{	
			str.assign(long_src, 0, long_src.size());
			CHECK_MY_STRING(str, long_src.size(), old_cap * 2, long_src.c_str());

			std_s.assign(long_std, 0, long_std.size());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("from 0, but not whole string")
		{
			str.assign(short_src, 0, 5);
			const char* expected = strndup(short_src.c_str(), 5);
			CHECK_MY_STRING(str, 5, old_cap, expected);

			std_s.assign(short_std, 0, 5);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("from not 0 index to end")
		{
			str.assign(short_src, 4, short_src.size() - 4);
			CHECK_MY_STRING(str, short_src.size() - 4, old_cap, short_src.c_str() + 4);

			std_s.assign(short_std, 4, short_std.size() - 4);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("if len bigger than source string then copy until end")
		{
			str.assign(long_src, 10, 123456);
			CHECK_MY_STRING(str, long_src.size() - 10, old_cap * 2, long_src.c_str() + 10);

			std_s.assign(long_std, 10, 123456);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("if len is 'string::npos' then copy until end")
		{
			str.assign(long_src, 5, isa::string::npos);
			CHECK_MY_STRING(str, long_src.size() - 5, old_cap * 2, long_src.c_str() + 5);

			std_s.assign(long_std, 5, std::string::npos);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("assign to short string")
	{
		isa::string str("short string");
		size_t old_cap = str.capacity();
		std::string std_s("short string");
		
		SECTION("must remain short")
		{
			str.assign(short_src, 0, short_src.size());
			CHECK_MY_STRING(str, short_src.size(), short_max, short_src.c_str());

			std_s.assign(short_std, 0, short_std.size());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity")
		{	
			str.assign(long_src, 20, long_src.size());
			CHECK_MY_STRING(str, long_src.size() - 20, old_cap * 2, long_src.c_str() + 20);

			std_s.assign(long_std, 20, long_std.size());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("when doubled capacity isn't enough must allocate only required space (source's size)")
		{	
			str.assign(long_src, 0, long_src.size());
			CHECK_MY_STRING(str, long_src.size(), long_src.capacity(), long_src.c_str());

			std_s.assign(long_std, 0, long_std.size());
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("if pos is greater than source's length then must throw 'isa::out_of_range'")
	{
		isa::string str;
		//REQUIRE_THROWS_AS(std_s.assign(long_std, long_std.size() + 1, 10), std::out_of_range);
		REQUIRE_THROWS_AS(str.assign(long_src, long_src.size() + 1, 10), isa::out_of_range);
	}
}

TEST_CASE("c-string assignment", tag "[c-string]")
{
	SECTION("assign to long string")
	{
		isa::string str("c-string test not short = 28");
		size_t old_cap = str.capacity();
		std::string std_s("c-string test not short = 28");

		SECTION("must copy whole string and preserve old capacity as it's already enough")
		{
			str.assign(short_src.c_str());
			CHECK_MY_STRING(str, short_src.size(), old_cap, short_src.c_str());

			std_s.assign(short_std.c_str());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity and copy whole string")
		{	
			str.assign(long_src.c_str());
			CHECK_MY_STRING(str, long_src.size(), old_cap * 2, long_src.c_str());

			std_s.assign(long_std.c_str());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("from not 0 index to end")
		{
			str.assign(short_src.c_str() + 4);
			CHECK_MY_STRING(str, short_src.size() - 4, old_cap, short_src.c_str() + 4);

			std_s.assign(short_std.c_str() + 4);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("assign to short string")
	{
		isa::string str("test c-str");
		std::string std_s("test c-str");
		
		SECTION("must remain short")
		{
			str.assign(short_src.c_str());
			CHECK_MY_STRING(str, short_src.size(), short_max, short_src.c_str());

			std_s.assign(short_std.c_str());
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity")
		{	
			str.assign(long_src.c_str() + 20);
			CHECK_MY_STRING(str, long_src.size() - 20, short_max * 2, long_src.c_str() + 20);

			std_s.assign(long_std.c_str() + 20);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("when doubled capacity isn't enough must alloc only required space (source's size)")
		{
			str.assign(long_src.c_str());
			CHECK_MY_STRING(str, long_src.size(), long_src.capacity(), long_src.c_str());

			std_s.assign(long_std.c_str());
			CMP_MINE_WITH_STD(str, std_s);
		}
	}

}
