#pragma once

namespace isa
{
	template<class InputIterator>
	string::string(InputIterator first, InputIterator last)
		: _size { static_cast<size_t> (std::distance(first, last)) }
		, space { 0 }
	{
		check_new_size(_size);

		_data = _size <= short_max ? small_buff : new char[_size + 1];
		std::copy(static_cast<const value_type*> (first), static_cast<const value_type*> (last), _data);
		_data[_size] = '\0';
	}

	template<class InputIterator>
	string& string::assign(InputIterator first, InputIterator last)
	{
		if(static_cast<const value_type*> (first) == _data && static_cast<const value_type*> (last) == _data + _size)
		{
			return *this;
		}
		size_t new_sz = static_cast<size_t> (std::distance(first, last));
		check_new_size(new_sz);

		verify_capacity(new_sz);
		std::copy(static_cast<const value_type*> (first), static_cast<const value_type*> (last), _data);
		_data[new_sz] = '\0';
		_size = new_sz;

		return *this;
	}

	template<class InputIterator>										
	string& string::append(InputIterator first, InputIterator last)		
	{																	
		size_t len = static_cast<size_t> (std::distance(first, last));
		check_new_size(len + _size);
		verify_capacity(len + _size);

		std::copy(static_cast<const value_type*> (first), static_cast<const value_type*> (last), _data + _size);
		_size += len;
		_data[_size] = '\0';

		return *this;
	}																	
}

