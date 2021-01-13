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
		const static size_t short_max = 15;

		size_t size;
		char* data;

		union 
		{
			size_t space;
			char small_buff[short_max + 1];
		};
		

	public:
		
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

		string& operator+=(const char ch)
		{
			if(size == short_max)
			{
				data = new char[size + size + 1 + 1];
				strcpy(data, small_buff);
				space = size;
			}
			else if(size > short_max)
			{
				if(space == 0)
				{
					char* new_mem = new char[size + size + 1 + 1];
					strcpy(new_mem, data);
					delete[] data;
					data = new_mem;
					space = size;
				}
				else 
				{
					--space;
				}
			}
			data[size] = ch;
			data[++size] = '\0';

			return *this;
		}

		string& operator+=(const string& other)
		{
			char* ch = other.data;

			while(*ch)
			{
				// operator+=(ch++);
				*this += (*ch++);
			}

			return *this;
		}

		// element access
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

		// capacity
		bool empty(void) const noexcept
		{
			return size == 0;
		}

		size_t size(void) const noexcept
		{
			return size;
		}
		size_t length(void) const noexcept
		{
			return size;
		}

		size_t capacity(void) const noexcept
		{
			return (size <= short_max ? short_max : size + space);
		}

		size_t max_size(void) const noexcept;
		void reserve(size_t new_cap);
		void shrink_to_fit(void);
			
		// operations
		void clear(void) noexcept
		{
			char* ptr = size <= short_max ? nullptr : data;
			delete[] ptr;
			size = 0;
			data = small_buffer;
			memset(small_buffer, 0, sizeof(small_buffer));
		}


	};

}
