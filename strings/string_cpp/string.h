#include <cstring>
#include <cstddef>


namespace isa
{
	class out_of_range
	{
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

	class string
	{
		static const size_t npos = -1;
		static const size_t short_max = 15;

		size_t size;
		char* data;

		union 
		{
			size_t space;
			char small_buff[short_max + 1];
		};
		

	public:
		
		// CONSTRUCTORS
		string(void) noexcept
			: size{ 0 }
			, data{ small_buff }
		{
			small_buff[0] = '\0';
		}

		string(const char* cstr)
			: size{ strlen(cstr) }
			, data{ size <= short_max ? small_buff : new char[size + 1] }
			, space{ 0 } 
		{
			strcpy(data, cstr);
		}

		string(const string& other) 
			: size{ other.size }
			, space{ 0 }
		{
			if(other.size <= short_max)
			{
				memcpy(this, &other, sizeof(other));
				data = small_buff;
			}
			else
			{
				data = new char[other.size + 1];
				strcpy(data, other.data);
			}
		}

		string(string&& other)
			: size { other.size }
			, data { other.data }
		{
			if(other.size <= short_max)
			{
				memcpy(this, &other, sizeof(other));
				data = small_buff;
			}
			else 
			{
				space = other.space;

				other.data = other.small_buff;
				other.size = 0;
				other.small_buff[0] = 0;
			}
		}

		// ASSIGNMENT OPERATORS
		string& operator=(const string& other)
		{
			if(this == &other)
			{
				return *this;
			}

			char* ptr = size <= short_max ? nullptr : data;
			if(other.size <= short_max)
			{
				memcpy(this, &other, sizeof(other));
				data = small_buff;
			}
			else
			{
				data = new char[other.size + 1];
				strcpy(data, other.data);
				size = other.size;
				space = 0;
			}

			delete[] ptr;
			return *this;
		}

		string& operator=(string&& other)
		{
			if(this == &other)
			{
				return *this;
			}
			if(sz > short_max)
			{
				delete[] data;
			}

			if(other.size <= short_max)
			{
				memcpy(this, &other, sizeof(other));
				data = small_buff;
			}
			else
			{
				data = other.data;
				size = other.size;
				space = other.space;

				other.data = other.small_buff;
				other.data[0] = '\0';
				other.size = 0;
			}
		}


		// DATA ACCESS FUNCTIONS
		const char& operator[](const size_t i) const noexcept
		{
			return data[i];
		}
		
		char& operator[](const size_t i) noexcept
		{
			return data[i];
		}

		const char& at(const size_t pos) const
		{
			if(pos >= size)
			{
				throw ::isa::out_of_range("isa::string::at() - index out of range");
			}
			return data[pos];	
		}

		char& at(const size_t pos)
		{
			if(pos >= size)
			{
				throw ::isa::out_of_range("isa::string::at() - index out of range");
			}
			return data[pos];
		}
		
		const char* c_str(void) const noexcept
		{
			return data;
		}

		const char* data(void) const noexcept
		{
			return data;
		}

		const char& front(void) const 
		{
			return data[0];
		}

		char& front(void)
		{
			return data[0];
		}

		const char& back(void) const
		{
			return data[size-1];
		}

		char& back(void)
		{
			return data[size-1];
		}

		// CAPACITY FUNCTIONS
		bool empty(void) const noexcept
		{
			return size == 0;
		}

		size_t size(void) const noexcept
		{
			return size;
		}
		size_t length(void) const noexcept { return size; }

		size_t capacity(void) const ; // until c++11
		size_t capacity(void) const noexcept; // since c++11 until c++20
		constexpr size_t capacity(void) const noexcept; // since c++20

		// TODO: implement
		size_t max_size(void) const noexcept;
		void reserve(const size_t new_cap);
		void shrink_to_fit(void);
			
		// OPERATIONS
		void clear(void); // until c++11
		void clear(void) noexcept; // since c++11 until c++20
		constexpr void clear(void) noexcept; // since c++20

		// TODO: insert() funciton and all its overloads

		string& erase(const size_t index = 0, const size_t count = npos);
		// TODO: erase() overloads

		void push_back(const char ch); // until c++20
		constexpr void push_back(const char ch); // since c++20

		void pop_back(void); // until c++20
		constexpr void pop_back(void); // since c++20

		// TODO: append() function and all its overloads
		
		string& operator+=(const char ch);
		string& operator+=(const string& other);
		// TODO: operator+=() all remaining overloads

		// TODO: compare() function and all its overloads

		bool starts_with(const isa::string_view sv) const noexcept;
		bool starts_with(const char ch) const noexcept;
		bool starts_with(const char* str) const;

		bool ends_with(const isa::string_view sv) const noexcept;
		bool ends_with(char ch) const noexcept;
		bool ends_with(const char* str) const;

		bool contains(const isa::string_view sv) const noexcept;
		bool contains(const char c) const noexcept;
		bool contains(const char* str) const;

		//TODO: replace() function and all its overloads

		string substr(const size_t start = 0, const size_t len = npos) const;

		size_t copy(char*const dest, const size_t len, const size_t start = 0) const;

		void resize(const size_t new_sz); // until c++20
		constexpr void resize(const size_t new_sz); // since c++20
		void resize(const size_t new_sz, const char ch); // until c++20
		constexpr void resize(const size_t new_sz, const char ch); // since c++20

		void swap(string& other); // until c++17
		void swap(string& other) noexcept; // since c++17 until c++20
		constexpr void swap(string& other) noexcept; // since c++20


		// SEARCH FUNCTIONS
		size_t find(const string& str, size_t start = 0) const; // until c++11
		size_t find(const string& str, size_t start = 0) const noexcept; // since c++11 until c++20
		constexpr size_t find(const string& str, size_t start = 0) const noexcept; // since c++20
		// TODO: find() function and all its overloads


		size_t rfind(const string& str, size_t start = npos) const; // until c++11
		size_t rfind(const string& str, size_t start = npos) const noexcept; // since c++11 until c++20
		constexpr size_t rfing(const string& str, size_t start = npos) const noexcept; // since c++20
		// TODO: rfind() function and all its overloads


		size_t find_first_of(const string& str, size_t start = 0) const; // until c++11
		size_t find_first_of(const string& str, size_t start = 0) const noexcept; // since c++11 until c++20
		constexpr size_t find_first_of(const string& str, size_t start = 0) const noexcept; // since c++20
		// TODO: find_first_of() function and all its overloads

		
		size_t find_first_not_of(const string& str, size_t start = 0) const; // until c++11
		size_t find_first_not_of(const string& str, size_t start = 0) const noexcept; // since c++11 until c++20
		constexpr size_t find_first_not_of(const string& str, size_t start = 0) const noexcept; // since c++20
		// TODO: find_first_not_of() and all its overloads


		size_t find_last_of(const string& str, size_t start = npos) const; // until c++11
		size_t find_last_of(const string& str, size_t start = npos) const noexcept; // since c++11 until c++20
		constexpr size_t find_last_of(const string& str, size_t start = npos) const noexcept; // since c++20
		// TODO: find_last_of() and all its overloads


		size_t find_last_not_of(const string& str, size_t start = npos) const; // until c++11
		size_t find_last_not_of(const string& str, size_t start = npos) const noexcept; // since c++11 until c++20
		constexpr size_t find_last_not_of(const string& str, size_t start = npos) const noexcept; // since c++20
		// TODO: find_last_not_of() and all its overloads


		// DESTRUCTOR
		~string();

	};

}
