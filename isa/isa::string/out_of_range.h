#pragma once
#include <cstring>

// TODO: Learn standard implementation
namespace isa {

	class out_of_range {

		// TODO: Change to use isa::string&
		char* _what = nullptr;

		void cpy(const char* p) 
		{
			_what = new char[std::strlen(p) + 1];
			std::strcpy(_what, p);
		}

	public:
		out_of_range(void) = delete;
		out_of_range(const char* _what_arg)
		{
			cpy(_what_arg);
		}

		out_of_range(const out_of_range& other)
		{
			cpy(other._what);
		}

		out_of_range& operator=(const out_of_range& other)
		{
			if(this == &other)
			{
				return *this;
			}
			if(_what)
			{
				delete[] _what;
			}
			
			cpy(other._what);
			return *this;
		}

		/*virtual*/ const char* what(void) const noexcept
		{
			return _what;
		}

		~out_of_range(void) noexcept
		{
			delete[] _what;
		}
	};
}
