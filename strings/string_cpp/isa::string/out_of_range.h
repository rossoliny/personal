#include <cstring>

// TODO: Learn standard implementation
namespace isa {

	class out_of_range

		// TODO: Change to use isa::string&
		char* what = nullptr;

		void cpy(const char* p) 
		{
			what = new char[strlen(p) + 1];
			strcpy(what, p);
		}

	public:
		out_of_range(void) = delete;
		out_of_range(const char* what_arg)
		{
			cpy(what_arg);
		}

		out_of_range(const out_of_range& other)
		{
			cpy(other.what);
		}

		out_of_range& operator=(const out_of_range& other)
		{
			if(this == &other)
			{
				return *this;
			}
			if(what)
			{
				delete[] what;
			}
			
			cpy(other.what);
			return *this;
		}

		/*virtual*/ const char* what(void) const noexcept
		{
			return what;
		}

		~out_of_range(void) noexcept
		{
			delete[] what;
		}
	};
}
