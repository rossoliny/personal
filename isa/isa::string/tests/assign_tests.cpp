#include <catch2/catch.hpp>
#include "test_utils.h"

#include "../string.h"

// Unit tests for isa::string::assign functions
// C++11
// Assuming that all construtor tests are passed

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




TEST_CASE("move assignment", tag "[move]")
{
	size_t long_len = 25;
	char long_cstr[long_len + 1] = "rvalue with 25 characters";
	isa::string long_rval(long_cstr);
	std::string long_std_r(long_cstr);

	size_t short_len = 14;
	char short_cstr[short_len + 1] = "rvalue with 14";
	isa::string short_rval(short_cstr);
	std::string short_std_r(short_cstr);


	SECTION("assign to short")
	{
		isa::string str("short str");
		std::string std_s("short str");

		SECTION("steal from short string, remain short, dont change src")
		{
			str.assign(std::move(short_rval));
			
			CHECK_MY_STRING(str, short_len, short_max, short_cstr);
			CHECK_MY_STRING(short_rval, short_len, short_max, short_cstr);

			std_s.assign(std::move(short_std_r));
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("steal from long string and become long, change src")
		{
			str.assign(std::move(long_rval));
			
			CHECK_MY_STRING(str, long_len, long_len, long_cstr);
			CHECK_MY_STRING(long_rval, 0, short_max, "");

			std_s.assign(std::move(long_std_r));
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("assign to long")
	{
		
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
	SECTION("when assign itself then do not do anything")
	{
		isa::string str("c-string self assignment test");
		std::string std_s("c-string self assignment test");

		const char* old_data = str.c_str();
		size_t old_sz = str.size();
		size_t old_cap = str.capacity();

		str.assign(str.c_str());
		REQUIRE(old_data == str.c_str());
		CHECK_MY_STRING(str, old_sz, old_cap, old_data);

		std_s.assign(std_s.c_str());
		CMP_MINE_WITH_STD(str, std_s);
	}
}




TEST_CASE("buffer assignment", tag "[buffer]")
{
	char buff[4096];
	memset(buff, 'c', sizeof(buff));

	SECTION("assign to long string")
	{
		isa::string str("buffer test not short str 28");
		size_t old_cap = str.capacity();
		std::string std_s("buffer test not short str 28");

		SECTION("must copy 3 chars and preserve old capacity")
		{
			str.assign(buff, 3);
			CHECK_MY_STRING(str, 3, old_cap, "ccc");

			std_s.assign(buff, 3);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity")
		{	
			str.assign(buff, old_cap + 10);
			buff[old_cap + 10] = '\0';
			CHECK_MY_STRING(str, old_cap + 10, old_cap * 2, buff);

			std_s.assign(buff, std_s.capacity() + 10);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("assign to short string")
	{
		isa::string str("test c-str");
		std::string std_s("test c-str");
		
		SECTION("must remain short")
		{
			str.assign(buff, 3);
			CHECK_MY_STRING(str, 3, short_max, "ccc");

			std_s.assign(buff, 3);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity")
		{	
			str.assign(buff, 20);
			buff[20] = '\0';
			CHECK_MY_STRING(str, 20, short_max * 2, buff);

			std_s.assign(buff, 20);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("when doubled capacity isn't enough must alloc only required space (source's size)")
		{
			str.assign(buff, sizeof(buff) - 1);
			buff[sizeof(buff) - 1] = '\0';
			CHECK_MY_STRING(str, sizeof(buff) - 1, sizeof(buff) - 1, buff);

			std_s.assign(buff, sizeof(buff) - 1);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("when assign itself then do not do anything")
	{
		isa::string str("buffer self assignment test");
		std::string std_s("buffer self assignment test");

		const char* old_data = str.c_str();
		size_t old_sz = str.size();
		size_t old_cap = str.capacity();

		str.assign(str.data(), str.size());
		REQUIRE(old_data == str.c_str());
		CHECK_MY_STRING(str, old_sz, old_cap, old_data);

		std_s.assign(std_s.c_str());
		CMP_MINE_WITH_STD(str, std_s);
	}
	SECTION("if 'count' > 'string::max_size()' then must throw 'std::length_error'")
	{
		isa::string str;
		//REQUIRE_THROWS_AS(std_s.assign(long_std, long_std.size() + 1, 10), std::out_of_range);
		REQUIRE_THROWS_AS(str.assign(long_src.c_str(), str.max_size() + 1), std::length_error);
	}

}





TEST_CASE("fill assignment", tag "[fill]")
{
	char expected[4096];
	char ch = 'n';
	memset(expected, ch, sizeof(expected));

	SECTION("assign to long string")
	{
		isa::string str("fill test not short len = 28");
		size_t old_cap = str.capacity();
		std::string std_s("fill test not short len = 28");

		SECTION("must adjust capacity and fill with 2000 chars")
		{
			str.assign(2000, ch);
			expected[2000] = '\0';
			CHECK_MY_STRING(str, 2000, 2000, expected);

			std_s.assign(2000, ch);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must fill 20 chars and preserve old capacity")
		{
			str.assign(20, ch);
			expected[20] = '\0';
			CHECK_MY_STRING(str, 20, old_cap, expected);

			std_s.assign(20, ch);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity")
		{	
			str.assign(old_cap + 10, ch);
			expected[old_cap + 10] = '\0';
			CHECK_MY_STRING(str, old_cap + 10, old_cap * 2, expected);

			std_s.assign(std_s.capacity() + 10, ch);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("assign to short string")
	{
		isa::string str("test c-str");
		std::string std_s("test c-str");
		
		SECTION("must remain short")
		{
			str.assign(10, ch);
			expected[10] = '\0';
			CHECK_MY_STRING(str, 10, short_max, expected);

			std_s.assign(10, ch);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("must double the capacity")
		{	
			str.assign(20, ch);
			expected[20] = '\0';
			CHECK_MY_STRING(str, 20, short_max * 2, expected);

			std_s.assign(20, ch);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("if 'count' > 'string::max_size()' then must throw 'std::length_error'")
	{
		isa::string str;
		//REQUIRE_THROWS_AS(std_s.assign(long_std, long_std.size() + 1, 10), std::out_of_range);
		size_t count = str.max_size();
		REQUIRE_THROWS_AS(str.assign(count + 1, ch), std::length_error);
	}

}



TEST_CASE("range assignment", tag "[range]")
{
	using const_ptr = isa::string::const_pointer;
	using std_const_ptr = std::string::const_pointer;

	const_ptr first_long = long_src.c_str();
	const_ptr last_long = long_src.c_str() + long_src.size();

	const_ptr first_short = short_src.c_str();
	const_ptr last_short = short_src.c_str() + short_src.size();

	SECTION("long string as target")
	{
		isa::string str("range test long string as target");
		size_t old_cap = str.capacity();
		std::string std_s("range test long string as target");

		SECTION("assign short as source")
		{
			str.assign<const_ptr>(first_short + 1, last_short);
			
			CHECK_MY_STRING(str, short_src.size() - 1, old_cap, first_short + 1);

			std_s.assign<std_const_ptr>(first_short + 1, last_short);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("assign long as source")
		{
			str.assign<const_ptr>(first_long + 2, last_long - 3);
			
			CHECK_MY_STRING(str, long_src.size() - 5, old_cap * 2, strndup(first_long + 2, long_src.size() - 3));

			std_s.assign<std_const_ptr>(first_long + 2, last_long - 3);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("short string as target")
	{
		isa::string str("short");
		std::string std_s("short");
		
		SECTION("short source, preserve capacity")
		{
			str.assign<const_ptr>(first_short, last_short);
			CHECK_MY_STRING(str, short_src.size(), short_max, first_short);

			std_s.assign<std_const_ptr>(first_short, last_short);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("long source, double capacity")
		{
			str.assign<const_ptr>(first_long, last_long - 20);
			CHECK_MY_STRING(str, long_src.size() - 20, short_max * 2, strndup(first_long, long_src.size() - 20));

			std_s.assign<std_const_ptr>(first_long, last_long - 20);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("long source, allocate required capacity")
		{
			str.assign<const_ptr>(first_long, last_long);
			
			CHECK_MY_STRING(str, long_src.size(), long_src.capacity(), first_long);

			std_s.assign<std_const_ptr>(first_long, last_long);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("assignment of too long string throws 'std::length_error'")
	{
		isa::string str;
		REQUIRE_THROWS_AS(str.assign<const_ptr>(nullptr, (const_ptr) str.max_size() + 1), std::length_error);
	}
}




TEST_CASE("initializer list assignment", tag "[assign]")
{
	std::initializer_list long_il = {'l', 'o', 'n', 'g', ' ', 'i', 'n', 'i', 't', 'i', 'a', 'l', 'i', 'z', 'e', 'r', ' ', 'l', 'i', 's', 't'};
	std::initializer_list short_il = {'s', 'h', 'o', 'r', 't', ' ', 'i', 'l'};

	const char* long_exp = std::string(long_il).c_str();
	const char* short_exp = std::string(short_il).c_str();

	SECTION("short string target")
	{
		isa::string str("short str");
		std::string std_s("short_str");

		SECTION("assign short initializer list")
		{
			str.assign(short_il);
			CHECK_MY_STRING(str, short_il.size(), short_max, short_exp);

			std_s.assign(short_il);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("assign long initializer list")
		{
			str.assign(long_il);
			CHECK_MY_STRING(str, long_il.size(), short_max * 2, long_exp);

			std_s.assign(long_il);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("long string target")
	{
		isa::string str("long string test");
		size_t old_cap = str.capacity();
		std::string std_s("long string test");

		SECTION("assign short initializer list")
		{
			str.assign(short_il);
			CHECK_MY_STRING(str, short_il.size(), old_cap, short_exp);

			std_s.assign(short_il);
			CMP_MINE_WITH_STD(str, std_s);
		}
		SECTION("assign long initializer list")
		{
			str.assign(long_il);
			CHECK_MY_STRING(str, long_il.size(), old_cap * 2, long_exp);

			std_s.assign(long_il);
			CMP_MINE_WITH_STD(str, std_s);
		}
	}
	SECTION("when provided initializer list is too long then throw 'std::length_error'")
	{
		// TODO: figure out how to test this case.
	}
}
