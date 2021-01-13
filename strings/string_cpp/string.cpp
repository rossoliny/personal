#include "string.h"

namespace isa
{
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
