#include <cstring>

#include "string.h"

namespace isa
{
	// CONSTRUSTORS
	
	string::string(void)
		: size{ 0 }
		, data{ small_buff }
	{
		small_buff[0] = '\0';
	}


	string::string(const char* cstr)
		: size{ strlen(cstr) }
		, data{ size <= short_max ? small_buff : new char[size + 1] }
		, space{ 0 } 
	{
		strcpy(data, cstr);
	}

	string::string(const string& other) 
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
	

	string::string(string&& other)
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
	string& string::operator=(const string& other)
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

	string& string::operator=(string&& other)
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
	const char& string::operator[](const size_t i) const noexcept
	{
		return data[i];
	}
	
	char& string::operator[](const size_t i) noexcept
	{
		return data[i];
	}

	const char& string::at(const size_t pos) const
	{
		if(pos >= size)
		{
			throw ::isa::out_of_range("isa::string::at() - index out of range");
		}
		return data[pos];	
	}

	char& string::at(const size_t pos)
	{
		if(pos >= size)
		{
			throw ::isa::out_of_range("isa::string::at() - index out of range");
		}
		return data[pos];
	}
	
	const char* string::c_str(void) const noexcept
	{
		return data;
	}

	const char* string::data(void) const noexcept
	{
		return data;
	}

	const char& string::front(void) const 
	{
		return data[0];
	}

	char& string::front(void)
	{
		return data[0];
	}

	const char& string::back(void) const
	{
		return data[size-1];
	}

	char& string::back(void)
	{
		return data[size-1];
	}

	// CAPACITY FUNCTIONS
	bool string::empty(void) const noexcept
	{
		return size == 0;
	}

	size_t string::size(void) const noexcept
	{
		return size;
	}
	size_t string::length(void) const noexcept 
	{
	   	return size; 
	}

	// CAPACITY FUNCTIONS
	size_t string::capacity(void) const noexcept;
	{
		return (size <= short_max ? short_max : size + space);
	}



	// OPERATIONS
	string& string::operator+=(const char ch)
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

	string& string::operator+=(const string& other)
	{
		char* ch = other.data;

		while(*ch)
		{
			// operator+=(ch++);
			*this += (*ch++);
		}

		return *this;
	}



	void string::clear(void) noexcept
	{
		char* ptr = size <= short_max ? nullptr : data;
		delete[] ptr;
		size = 0;
		data = small_buffer;
		memset(small_buffer, 0, sizeof(small_buffer));
	}

}
