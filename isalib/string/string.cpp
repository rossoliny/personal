#include <cstring>
#include <cmath>

#include <stdexcept>
#include <algorithm>
#include "string.h"


namespace isa
{
	// UTILS

	void inline string::check_index(size_t index, size_t size) const
	{
		if(index > size)
		{
			throw isa::out_of_range("index is out of bounds");
		}
	}

	inline void string::check_new_size(size_t new_sz) const
	{
		if(new_sz > max_size())
		{
			throw std::length_error("resulting string would exceed maximum possible length");
		}
	}

	bool string::is_small() const
	{
		return (intptr_t)_data == (intptr_t)small_buff /*&& _size <= short_max*/;
	}

	void string::verify_capacity(size_t new_sz, bool copy)
	{
		if(new_sz > capacity())
		{
			size_t new_cap = capacity() * 2;
			new_cap = new_sz > new_cap ? new_sz : new_cap;

			char* new_mem = new char[new_cap + 1];
			if(copy) 
			{
				std::strcpy(new_mem, _data);
			}

			if(!is_small()) {
				delete[] _data; 
			}

			_data = new_mem;
			space = new_cap - new_sz;
		}
		else if(!is_small())
		{
			space = capacity() - new_sz;
		}
	}

	void string::copy_from(const string& other)
	{
		if(other._size <= short_max)
		{
			std::memcpy((void*)this, &other, sizeof(other));
			_data = small_buff;
		}
		else
		{
			_data = new char[other._size + 1];
			space = other.space;
			std::strcpy(_data, other._data);
		}
	}

	void string::steal_from(string&& other) noexcept
	{
		if(other.is_small())
		{
			std::memcpy(_data, other._data, other._size + 1);
			if(!is_small())
			{
				space += _size - other._size;	
			}
		}
		else
		{
			bool _small = is_small();
			std::swap(_data, other._data);
			std::swap(space, other.space);
			if(_small)
			{
				other._data = other.small_buff;
			}
		}
		std::swap(_size, other._size);
		other.clear();
	}

	// CONSTRUCTORS

	string::string(void) //noexcept
		: _size { 0 }
		, _data { small_buff }
	{
		small_buff[0] = '\0';
	}

	// never throws length_error as I dont know how to implement it
	string::string(const char* cstr)
		: _size { std::strlen(cstr) }
		, _data { _size <= short_max ? small_buff : new char[_size + 1] }
		, space { 0 } 
	{
		std::strcpy(_data, cstr);
	}

	string::string(const char* buff, size_t count) 
		: _size { count }
		, space { 0 }
	{
		check_new_size(count);
		_data = _size <= short_max ? small_buff : new char[_size + 1];
		std::memcpy(_data, buff, count);
		_data[_size] = '\0';
	}

	string::string(size_t count, char ch)
		: _size { count }
		, space { 0 }
	{
		check_new_size(count);
		_data = _size <= short_max ? small_buff : new char[_size + 1];
		std::memset(_data, ch, _size);
		_data[_size] = '\0';
	}

	string::string(const string& other) 
		: _size{ other._size }
	{
		copy_from(other);
	}

	string::string(const string& other, size_t start, size_t len)
		: space { 0 }
	{
		check_index(start, other._size);
		_size = other._size - start < len ? other._size - start : len; // choose min possible _size
		_data = _size <= short_max ? small_buff : new char[_size + 1];
		std::memcpy(_data, other._data + start, _size);
		_data[_size] = '\0';
	}

	string::string(string&& other) noexcept
		: _size { other._size }
		, _data { small_buff }
	{
		steal_from(std::move(other));
	}

	string::string(std::initializer_list<char> ilist)
		: string(ilist.begin(), ilist.end())
	{
		// begin() and end() return poiters so std::distance complexity should be constant
	}

	/****************************************************************
	 *	template<InputIterator>										*
	 * 	string::string(InputIterator first, InputIterator second)	*
	 *	{															*
	 *		Implementation in file string.hpp						*
	 *	}															*
	 ***************************************************************/

	// ASSIGNMENT OPERATORS
	string& string::operator=(const string& other)
	{
		return assign(other, 0, other._size);
	}

	string& string::operator=(string&& other) noexcept
	{
		return assign(std::move(other));
	}
	
	string& string::operator=(const char* cstr)
	{
		return assign(cstr);
	}
	string& string::operator=(std::initializer_list<char> ilist)
	{
		return assign<const_pointer>(ilist.begin(), ilist.end());
	}
	string& string::operator=(const char ch)
	{
		if(!is_small())
		{
			space += _size - 1;
		}
		_size = 1;
		_data[0] = ch;
		_data[_size] = '\0';

		return *this;
	}


	// CAPACITY FUNCTIONS
	size_t string::size(void) const noexcept
	{
		return _size;
	}
	size_t string::length(void) const noexcept 
	{
	   	return _size; 
	}

	size_t string::max_size(void) const noexcept
	{
		//return std::numeric_limits<size_type>::max() / sizeof(value_type);
		return (std::allocator_traits<allocator_type>::max_size(allocator_type()) - 1) / 2;
	}

	void string::resize(size_t new_sz)
	{
		resize(new_sz, '\0');
	}

	void string::resize(size_t new_sz, char ch)
	{
		check_new_size(new_sz);
		verify_capacity(new_sz, true);
		memset(_data + _size, ch, ((size_t)(new_sz > _size)) * (new_sz - _size));
		_size = new_sz;
		_data[_size] = '\0';
	}

	size_t string::capacity(void) const noexcept
	{
		return (is_small() ? short_max : _size + space); // null terminator is not counted
	}

	void string::reserve(size_t n)
	{
		check_new_size(n);
		if(n == 0)
		{
			shrink_to_fit();
			return;
		}
		verify_capacity(n, true);
		if(!is_small())
		{
			space += n - _size;
		}
	}

	void string::clear(void) noexcept
	{
		if(!is_small()) 
		{
			space += _size; 
		}
		_size = 0;
		_data[_size] = '\0';
	}

	bool string::empty(void) const noexcept
	{
		return _size == 0;
	}

	void string::shrink_to_fit(void)
	{
		if(is_small() || space == 0)
			return;

		char* new_mem = new char[_size + 1];
		std::strcpy(new_mem, _data);
		delete[] _data;
	}

	// ELEMET ACCESS FUNCTIONS
	const char& string::operator[](const size_t i) const noexcept
	{
		return _data[i];
	}
	char& string::operator[](const size_t i) noexcept
	{
		return _data[i];
	}

	const char& string::at(const size_t pos) const
	{
		check_index(pos, _size);
		return _data[pos];	
	}
	char& string::at(const size_t pos)
	{
		check_index(pos, _size);
		return _data[pos];
	}
	
	// why back and front are not noexcept?
	const char& string::back(void) const
	{
		return _data[_size - 1];
	}
	char& string::back(void)
	{
		return _data[_size - 1];
	}

	const char& string::front(void) const
	{
		return _data[0];
	}
	char& string::front(void)
	{
		return _data[0];
	}


	// MODIFIERS
	string& string::assign(string&& other) noexcept // move assignment
	{
		if(this == &other)
		{
			return *this;
		}
		steal_from(std::move(other));

		return *this;
	}

	string& string::assign(const string& other)
	{
		if(this == &other)
		{
			return *this;
		}

		return assign(other, 0, npos);
	}

	string& string::assign(const string& other, size_t start, size_t len)
	{
		check_index(start, other._size);

		size_t new_sz = other._size - start < len ? other._size - start : len;
		// other can never be longer than max_size();
		//check_new_capacity(new_sz);
		verify_capacity(new_sz);

		memmove(_data, other._data + start, new_sz);
		_data[new_sz] = '\0';
		_size = new_sz;

		return *this;
	}

	string& string::assign(const char* cstr)
	{
		if(_data == cstr)
		{
			return *this;
		}
		size_t new_sz = strlen(cstr);
		// c-string should not be longer than max_size()
		//check_new_size(new_sz);
		verify_capacity(new_sz);
		strcpy(_data, cstr);
		_size = new_sz;

		return *this;	
	}

	string& string::assign(const char* buff, size_t count)
	{
		if(_data == buff && _size == count)
		{
			return *this;
		}
		check_new_size(count);
		verify_capacity(count);
		memmove(_data, buff, count);
		_data[count] = '\0';
		_size = count;

		return *this;
	}

	string& string::assign(size_t count, char ch)
	{
		check_new_size(count);
		verify_capacity(count);
		memset(_data, ch, count);
		_data[count] = '\0';
		_size = count;

		return *this;
	}

	string& string::assign(std::initializer_list<char> ilist)
	{
		return assign(ilist.begin(), ilist.end());
	}

	/************************************************************************
	 *	template<class InputIterator>										*
	 *	string& string::assign(InputIterator first, InputIterator last)		*
	 *	{																	*	
	 * 		Implementation in file string.hpp								*
	 *	}																	*
	 ************************************************************************/


	string& string::operator+=(char ch)
	{
		if(_size == short_max)
		{
			_data = new char[_size + _size + 2]; // 32 
			std::strcpy(_data, small_buff);
			space = _size; // 32 - 15(_size) - 1(null_term) - 1(new_char)
		}
		else if(_size > short_max)
		{
			if(space == 0)
			{
				char* new_mem = new char[_size + _size + 2];
				std::strcpy(new_mem, _data);
				delete[] _data;
				_data = new_mem;
				space = _size;
			}
			else 
			{
				--space;
			}
		}
		_data[_size] = ch;
		_data[++_size] = '\0';

		return *this;
	}

	string& string::operator+=(const char* cstr)
	{
		size_t c_size = std::strlen(cstr);
		size_t new_sz = _size + c_size;

		// transforms from short to long string
		if(_size <= short_max && new_sz > short_max)
		{
			size_t ratio = (new_sz + 1) / (short_max + 1);
			size_t new_cap = (_size + 1) * (2 * ratio); // if new_sz=31 & _size=15 then allocates 64

			char* new_mem = new char[new_cap];
			std::strcpy(new_mem, _data);
			_data = new_mem;
			space = new_cap - new_sz - 1;
		}
		// already long string
		else if(_size > short_max)
		{
			if(space >= c_size)
			{
				space -= c_size;
			}
			else
			{
				size_t ratio = (new_sz + 1) / (_size + 1);
				size_t new_cap = (_size + 1) * (2 * (ratio));

				char* new_mem = new char[new_cap];
				std::strcpy(new_mem, _data);
				_data = new_mem;
				space = new_cap - new_sz - 1;
			}
		}
		std::strcpy(_data + _size, cstr);
		_data[new_sz] = '\0';
		_size = new_sz;
		
		return *this;
	}

	string& string::operator+=(const string& other)
	{
		// TODO: bad!!! too many reallocations
		char* ch = other._data;

		while(*ch)
		{
			// operator+=(ch++);
			*this += (*ch++);
		}

		return *this;
	}

	string& string::operator+=(std::initializer_list<char> ilist)
	{
		//TODO: impl
		return *this;
	}


	string& string::append(const string& other)
	{
		// TODO: impl
		return *this;
	}
	string& string::append(const string& other, size_t strart, size_t len) // substring
	{
		size_t new_sz = (other._size - start < len ? other._size - start : len) + _size;
		check_new_size(new_sz);
		verify_capacity(new_sz);
		_memmove(_data, other._data + start, new_sz);
		_size = new_sz;

		return *this;
	}
	string& string::append(const char* cstr) 
	{
		// TODO: impl
		return *this;
	}
	string& string::append(const char* buff, size_t count) // from buffer
	{
		// TODO: impl
		return *this;
	}
	string& string::append(size_t count, char ch) // fill
	{
		// TODO: impl
		return *this;
	}
	string& string::append(std::initializer_list<char> ilist) 
	{
		// TODO; impl
		return *this;
	}
	/*
	template<class InputIterator>
	string& string::append(InputIterator first, InputIterator last)
	{
		// TODO: impl
		return *this;
	}
	*/


	string& string::insert(size_t pos, const string& str)
	{
		// TODO: impl
		return *this;
	}
	string& string::insert(size_t pos, const string& str, size_t start, size_t len)
	{
		// TODO: impl
		return *this;
	}
	string& string::insert(size_t pos, const char* cstr)
	{
		// TODO: impl
		return *this;
	}
	string& string::insert(size_t pos, const char* buff, size_t count)
	{
		// TODO: impl
		return *this;
	}
	string& string::insert(size_t pos, size_t count, char ch)
	{
		// TODO: impl
		return *this;
	}
	string& string::insert(const_iterator pos, std::initializer_list<char> ilist)
	{
		// TODO: impl
		return *this;
	}
	string::iterator string::insert(const_iterator pos, size_t count, char ch)
	{
		// TODO: impl
		return iterator(_data);
	}
	string::iterator string::insert(const_iterator pos, char ch)
	{
		// TODO: impl
		return iterator(_data);
	}
	/*
	template<class InputIterator>
	iterator string::insert(InputIterator first, InputIterator last) // range
	{
		// TODO: impl
		return iterator(_data);
	}
	*/

	string& string::erase(const size_t pos, const size_t count) // sequence
	{
		// TODO: impl
		return *this;
	}
	string::iterator string::erase(const_iterator pos) // one character
	{
		// TODO: impl
		return iterator(_data);
	}
	string::iterator string::erase(const_iterator first, const_iterator last) // range
	{
		// TODO: impl
		return iterator(_data);
	}
	
	string& string::replace(size_t pos, size_t len, const string& str)
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(const_iterator b, const_iterator e, const string& str) // in current string from b to e string::replace with str
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(size_t pos, size_t len, const string& other, size_t subpos, size_t sublen)
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(size_t pos, size_t len, const char* cstr) // c-string
	{
		// TODO: impl
		return *this; 
	}
	string& string::replace(const_iterator b, const_iterator e, const char* cstr)
	{
		// TODO: impl
		return *this; 
	}
	string& string::replace(size_t pos, size_t len, const char* buff, size_t count) // buff
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(const_iterator b, const_iterator e, const char* buff, size_t count)
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(size_t pos, size_t len, size_t count, char ch) // fill
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(const_iterator b, const_iterator e, size_t count, char ch)
	{
		// TODO: impl
		return *this;
	}
	string& string::replace(size_t pos, size_t len, std::initializer_list<char> ilist)
	{
		// TODO: impl
		return *this;
	}
	/*
	template<class InputIterator>
	string& string::replace(const_iterator b, const_iterator e, InputIterator first, InputIterator last) // range
	{
		// TODO: impl
		return *this;
	}
	*/
	
	void string::swap(string& other) // noexcept since c++17
	{
		string old_this(*this);
		assign(std::move(other));
		other.assign(std::move(old_this));
	}

	void string::push_back(const char ch) //constexpre since c++20
	{
		// TODO; impl
		return;
	}
	
	void string::pop_back(void) // constexpr since c++20
	{
		// TODO: impl
		return;
	}


	// OPERATIONS
	const char* string::c_str(void) const noexcept
	{
		return _data;
	}

	const char* string::data(void) const noexcept
	{
		return _data;
	}

	 // std::string uses default allocator<char> -> return val is equal to allocator<char>()
	string::allocator_type string::get_allocator(void) const noexcept
	{
		// TODO: impl
		return std::allocator<char>();
	}

	size_t string::copy(char*const dest, const size_t len, const size_t start) const 
	{
		// TODO: impl
		return 0;
	}

	// search OPERATIONS
	string string::substr(const size_t start, const size_t len) const
	{
		// TODO: impl
		return *this;
	}

	// search OPERATIONS 
	
	// since c++11 until c++20; constexpr since c++20
	size_t string::find(const string& str, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find(const char* cstr, size_t start) const // string::find c-string
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find(const char* buff, size_t start, size_type buff_len) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find(char ch, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}

	size_t string::rfind(const string& str, size_t start) const noexcept // constexpr in c++20
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::rfind(const char* cstr, size_t start) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::rfind(const char* buff, size_t start, size_t buff_len) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::rfind(char ch, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}

	size_t string::find_first_of(const string& str, size_t start) const noexcept // constexpr in c++20
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_first_of(const char* cstr, size_t start) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_first_of(const char* buff, size_t start, size_t buff_len) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_first_of(char ch, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}

	size_t string::find_first_not_of(const string& str, size_t start) const noexcept // constexpr in c++20
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_first_not_of(const char* cstr, size_t start) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_first_not_of(const char* buff, size_t start, size_t buff_len) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_first_not_of(char ch, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}

	size_t string::find_last_of(const string& str, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_last_of(const char* cstr, size_t start) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_last_of(const char* buff, size_t start, size_t buff_len) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_last_of(char ch, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}

	size_t string::find_last_not_of(const string& str, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_last_not_of(const char* cstr, size_t start) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_last_not_of(const char* buff, size_t start, size_t buff_len) const
	{ 
		// TODO: impl
		return npos;
	}
	size_t string::find_last_not_of(char ch, size_t start) const noexcept
	{ 
		// TODO: impl
		return npos;
	}

	// string::compare OPERATIONS
	int string::compare(const string& other) const noexcept
	{
		// TODO: impl
		return -1;
	}
	int string::compare(size_t start, size_t len, const string& other) const
	{
		// TODO: impl
		return -1;
	}
	int string::compare(size_t start, size_t len, const string& other, size_t substart, size_t sublen) const
	{
		// TODO: impl
		return -1;
	}
	int string::compare(const char* cstr) const
	{
		// TODO: impl
		return -1;
	}
	int string::compare(size_t start, size_t len, const char* cstr) const
	{
		// TODO: impl
		return -1;
	}
	int string::compare(size_t start, size_t len, const char* buff, size_t buff_len) const
	{
		// TODO: impl
		return -1;
	}


	// ITERATORS
	string::iterator string::begin(void) noexcept
	{
		return iterator(_data);
	}
	string::const_iterator string::begin(void) const noexcept
	{
		return iterator(_data);
	}
	
	string::iterator string::end(void) noexcept
	{
		return iterator(_data + _size);
	}
	string::const_iterator string::end(void) const noexcept
	{
		return iterator(_data + _size);
	}

	// TODO: add remaining iterators


	// DESTRUCTOR
	string::~string(void)
	{
		if(!is_small())
		{
			delete[] _data;
		}
	}

};
