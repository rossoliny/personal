#include <cstring>
#include <cstddef>


namespace isa
{
	
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
		
		string() noexcept
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
	};

}
