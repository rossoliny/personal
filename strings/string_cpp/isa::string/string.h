#include <cstring>
#include <cstddef>

#include "out_of_range.h"

namespace isa
{

	//template<class string_type>
	class string_iterator
	{
		//using iterator = string_iterator;
		using value_type = ::isa::string::value_type;
		using size_type = ::isa::string::size_type;

		value_type* ptr;

	public:
		string_iterator(value_type* ptr) noexcept
			: ptr(ptr) 
		{
		}
		string_iterator(const string_iterator&) noexcept = default;
		string_iterator(string_iterator&&) noexcept = default;

		operator=(const string_iterator&) noexcept = default;
		operator=(string_iterator&&) noexcept = default;

		string_iterator& operator++() noexcept
		{
			++ptr;
			return *this;
		}
		const string_iterator& operator++() const noexcept
		{
			++(const_cast<string_iterator*> (this)->ptr);
			return *this;
		}

		string_iterator operator++(int) noexcept
		{
			string_iterator it = *this;
			ptr++;
			return it;
		}
		const string_iterator operator++(int) const noexcept
		{
			const string_iterator it = *this;
			(const_cast<string_iterator*> (this)->ptr)++;
			return it;
		}

		string_iterator& operator--() noexcept
		{
			--ptr;
			return *this;
		}
		const string_iterator& operator--() const noexcept
		{
			--(const_cast<string_iterator*> (this)->ptr);
			return *this;
		}


		string_iterator operator--(int) noexcept
		{
			string_iterator it = *this;
			ptr--;
			return it;
		}
		const string_iterator operator--(int) const noexcept
		{
			const string_iterator it = *this;
			(const_cast<string_iterator*> (this)->ptr)--;
			return it;
		}

		value_type& operator[](size_type index) noexcept
		{
			return *(ptr + index);
		}
		const value_type& operator[](size_type index) const noexcept
		{
			return *(ptr + index);
		}

		value_type* operator->() noexcept
		{
			return ptr;
		}
		const value_type* operator->() const noexcept
		{
			return ptr;
		}

		value_type& operator*() noexcept
		{
			return *ptr;
		}
		const value_type& operator*() const noexcept
		{
			return *ptr;
		}

		bool operator==(const string_iterator& other) const noexcept
		{
			return ptr == other.ptr;
		}

		bool operator!=(const string_iterator& other) const noexcept
		{
			return ptr != other.ptr;
		}
	};



	class string
	{

		static const size_t short_max = 15;

		size_t size;
		char* data;

		union 
		{
			size_t space;
			char small_buff[short_max + 1];
		};

		// UTILS		
		void copy_from(const string& str);

	public:
		// MEMBER TYPES

		// TODO: create const_iterator
		// TODO: create reverse_iterator
		// TODO: create const_reverse_iterato
		// TODO: create traits_type
		using value_type = char;
		using reference = char&;
		using const_reference = const char&;
		using pointer = char*;
		using const_pointer = const char*;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using iterator = ::isa::string_iterator;
		using const_iterator = const ::isa::string_iterator;
		using allocator_type = std::allocator<char>;


		// MEMBER CONSTANTS
		static const size_t npos = -1;
		
		// CONSTRUCTORS
		string(void) noexcept; // default
		string(const char* cstr); // from c-string
		string(const char* buff, size_t count); // from buffer
		string(size_t count, char ch); // fill
		string(const string& other); // copy
		string(const string& other, size_t start, size_t len = npos); // substring
		string(std::initializer_list<char> ilist); // initializer list
		string(string&& other) noexcept; // move
		template<class InputIterator>
		string(InputIterator first, InputIterator last); // range

		// ASSIGNMENT
		string& operator=(const char* cstr); // from c-string
		string& operator=(const char ch);
		string& operator=(const string& other); // copy
		string& operator=(string&& other) noexcept; // move
		string& operator=(std::initializer_list<char> ilist);
		
		// CAPACITY FUNCTIONS
		size_t size(void) const noexcept;

		size_t length(void) const noexcept;

		size_t max_size(void) const noexcept;

		void resize(size_t new_sz);
		void resize(size_t new_sz, char ch);

		size_t capacity(void) const noexcept; // since c++11 until c++20
		
		void reserve(size_t n = 0);

		void clear(void) noexcept;
		
		bool empty(void) const noexcept;

		void shrink_to_fit(void);


		// ELEMENT ACCESS FUNCTIONS
		const char& operator[](const size_t i) const noexcept;
		char& operator[](const size_t i) noexcept;

		const char& at(const size_t pos) const;
		char& at(const size_t pos);
		
		const char& back(void) const;
		char& back(void);

		const char& front(void) const;
		char& front(void);

		// MODIFIERS
		string& operator+=(const char ch);
		string& operator+=(const char* cstr);
		string& operator+=(const string& other);
		string& operator+=(std::initializer_list<char> ilist);
		
		// TODO: append() function and all its overloads
		string& append(const string& other);
		string& append(const string& other, size_t strart, size_t len); // substring
	   	string& append(const char* cstr);
		string& append(const char* buff, size_t count); // from buffer
		string& append(size_t count, char ch); // fill
		string& append(std::initializer_list<char> ilist); 
		template<class InputIterator>
		string& append(InputIterator first, InputIterator last);

		void push_back(const char ch); // until c++20

		string& assign(const string& other);
		string& assign(const string& other, size_t start, size_t len);
		string& assign(const char* cstr);
		string& assign(const char* buff, size_t count);
		string& assign(size_t count, char ch);
		string& assign(string&& other) noexcept; // move
		string& assign(std::initializer_list<char> ilist);
		template<class InputIterator>
		string& assign(InputIterator first, InputIterator last);

		string& insert(size_t pos, const string& str);
		string& insert(size_t pos, const string& str, size_t start, size_t len);
		string& insert(size_t pos, const char* cstr);
		string& insert(size_t pos, const char* buff, size_t count);
		string& insert(size_t pos, size_t count, char ch);
		string& insert(const_iterator pos, std::initializer_list<char> ilist);
		iterator insert(const_iterator pos, size_t count, char ch);
		iterator insert(const_iterator pos, char ch);
		template<class InputIterator>
		iterator insert(InputIterator first, InputIterator last); // range

		string& erase(const size_t pos = 0, const size_t count = npos); // sequence
		iterator erase(const_iterator pos); // character
		iterator erase(const_iterator first, const_iterator last); // range
		
		string& replace(size_t pos, size_t len, const string& str);
		string& replace(const_iterator b, const_iterator e, const string& str); // in current string from b to e replace with str
		string& replace(size_t pos, size_t len, const string& other, size_t subpos, size_t sublen);
		string& replace(size_t pos, size_t len, const char* cstr); // c-string
		string& replace(const_iterator b, const_iterator e const char* cstr); 
		string& replace(size_t pos, size_t len, const char* buff, size_t count); // buff
		string& replace(const_iterator b, const_iterator e, const char* buff, size_t count);
		string& replace(size_t pos, size_t len, size_t count, char ch); // fill
		string& replace(const_iterator b, const_iterator e, size_t count, char ch);
		string& replace(size_t pos, size_t len, std::initialize_list<char> ilist);
		template<class InputIterator>
		string& replace(const_iterator b, const_iterator e, InputIterator first, InputIterator last); // range
		
		void swap(string& other); // noexcept since c++17
		
		void pop_back(void); // constexpr since c++20


		// OPERATIONS
		const char* c_str(void) const noexcept;

		const char* data(void) const noexcept;

		allocator_type get_allocator() const noexcept; // std::string uses default allocator<char> -> return val is equal to allocator<char>()

		size_t copy(char*const dest, const size_t len, const size_t start = 0) const;

		// SEARCH FUNCTIONS
		size_t find(const string& str, size_t start = 0) const noexcept; // since c++11 until c++20; constexpr since c++20
		size_t find(const char* cstr, size_t start = 0) const; // find c-string
		size_t find(const char* buff, size_t start, size_type buff_len) const;
		size_t find(char ch, size_t start = 0) const noexcept;

		size_t rfind(const string& str, size_t start = npos) const noexcept; // constexpr in c++20
		size_t rfind(const char* cstr, size_t start = npos) const;
		size_t rfind(const char* buff, size_t start, size_t buff_len) const;
		size_t rfind(char ch, size_t start = npos) const noexcept;

		size_t find_first_of(const string& str, size_t start = 0) const noexcept; // constexpr in c++20
		size_t find_first_of(const char* cstr, size_t start = 0) const;
		size_t find_first_of(const char* buff, size_t start, size_t buff_len) const;
		size_t find_first_of(char ch, size_t start = 0) const noexcept;

		size_t find_first_not_of(const string& str, size_t start = 0) const noexcept; // constexpr in c++20
		size_t find_first_not_of(const char* cstr, size_t start = 0) const;
		size_t find_first_not_of(const char* buff, size_t start, size_t buff_len) const;
		size_t find_first_not_of(char ch, size_t start = 0) const noexcept;

		size_t find_last_of(const string& str, size_t start = npos) const noexcept;
		size_t find_last_of(const char* cstr, size_t start = npos) const;
		size_t find_last_of(const char* buff, size_t start, size_t buff_len) const;
		size_t find_last_of(char ch, size_t start = npos) const noexcept;

		size_t find_last_not_of(const string& str, size_t start = npos) const noexcept;
		size_t find_last_not_of(const char* cstr, size_t start = npos) const;
		size_t find_last_not_of(const char* buff, size_t start, size_t buff_len) const;
		size_t find_last_not_of(char ch, size_t start = npos) const noexcept;

		string substr(const size_t start = 0, const size_t len = npos) const;

		int compare(const string& other) const noexcept;
		int compare(size_t start, size_t len, const string& other) const;
		int compare(size_t start, size_t len, const string& other, size_t substart, size_t sublen) const;
		int compare(const char* cstr) const;
		int compare(size_t start, size_t len, const char* cstr) const;
		int compare(size_t start, size_t len, const char* buff, size_t buff_len) const;

		// ITERATORS
		iterator begin(void) noexcept;
		const_iterator begin(void) const noexcept;
		
		iterator end(void) noexcept;
		const_iterator end(void) const noexcept;

		// TODO: add remaining iterators




		// c++20 and higher only
		/*
		bool starts_with(const isa::string_view sv) const noexcept;
		bool starts_with(const char ch) const noexcept;
		bool starts_with(const char* str) const;

		bool ends_with(const isa::string_view sv) const noexcept;
		bool ends_with(char ch) const noexcept;
		bool ends_with(const char* str) const;

		bool contains(const isa::string_view sv) const noexcept;
		bool contains(const char c) const noexcept;
		bool contains(const char* str) const;
		*/

		// DESTRUCTOR
		~string(void);
	};

}
