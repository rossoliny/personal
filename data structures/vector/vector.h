#pragma once


template<typename T>
class vec
{
public:
	vec() 
		: m_data((T*)::operator new(2 * sizeof(T)))
		, m_size(0)
		, m_capacity(2)
   	{ }

	void push_back(const T& val)
	{
		check_cap();	
		new (m_data + m_size) T(val);
		m_size++;
	}

	void push_back(T&& val)
	{
		check_cap();
		new (m_data + m_size) T(std::move(val));
		m_size++;
	}

	void assign(size_t n, const T& val)
	{
		clear();
		free();
		m_data = new T[n](val);
		m_size = n;
		m_capacity = n;
	}

	template<typename... Args>
	T& emplace(size_t pos, Args&&... args)
	{
		char* mem_ptr = reinterpret_cast<char*> (m_data);

		if(m_size >= m_capacity)
		{
			char* new_mem = static_cast<char*> (::operator new(m_capacity * 1.5L));

			for(int i = 0; i < (pos + 1) * sizeof(T); ++i)
			{
				new_mem[i] = mem_ptr[i];
			}
			mem_ptr = new_mem;
		}

		for(int i = (pos + 1) * sizeof(T); i < m_data * sizeof(T); ++i)
		{
			mem_ptr[i] = reinterpret_cast<char*> (m_data)[i - sizeof(T)];
		}
		
		new (mem_ptr + (pos * sizeof(T))) T(std::forward<Args>(args)...);

		if(m_size >= m_capacity)
		{
			free();
			m_capacity *= 1.5L;
		}
		m_data = mem_ptr;
		m_size++;
	}

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		check_cap();
		new(m_data + m_size) T(std::forward<Args>(args)...);
		return m_data[m_size++];
	}

	void pop_back()
	{
		if(m_size > 0)
		{
			m_size--;
			m_data[m_size].~T();
		}
	}

	void resize(size_t sz) 
	{
		m_size = sz;
		if(m_size >= m_capacity)
		{
			realloc(sz);
		}
	}

	size_t size() const noexcept
	{ 
		return m_size; 
	}

	size_t capacity() const noexcept
	{
		return m_capacity;
	}

	const T* data() const noexcept
	{
		return m_data;
	}

	T* data() noexcept 
	{
		return m_data;
	}

	const T& operator[](size_t pos) const noexcept
	{
		return m_data[pos];
	}

	T& operator[](size_t pos) noexcept
	{
		return m_data[pos];
	}

	const T& at(size_t pos) const
	{
		if(pos >= m_size)
		{
			throw std::out_of_range("vec::at index out of bounds");
		}
		return m_data[pos];
	}

	T& at(size_t pos)
	{
		if(pos >= m_size)
		{
			throw std::out_of_range("vec::at index out of bounds");
		}
		return m_data[pos];
	}

	const T& back() const noexcept
	{
		return m_data[m_size - 1];
	}

	T& back() noexcept
	{
		return m_data[m_size - 1];
	}

	void clear() noexcept
	{
		for(int i = 0; i < m_size; ++i)
		{
			m_data[i].~T();
		}
		m_size = 0;
	}

	~vec()
	{
		clear();
		::operator delete(m_data, m_capacity * sizeof(T));
	}

private:
	inline void check_cap()
	{
		if(m_size == m_capacity)
		{
			realloc(m_capacity * 1.5L);
		}
	}

	void realloc(size_t new_capacity)
	{
		char* new_mem = static_cast<char*> (::operator new(new_capacity * sizeof(T)));
		char* old_mem = reinterpret_cast<char*> (m_data);

		for(int i = 0; i < m_size * sizeof(T); ++i)
		{
			new_mem[i] = old_mem[i];
		}

		free();
		m_data = reinterpret_cast<T*> (new_mem);
		m_capacity = new_capacity;
	}

	inline void free()
	{
		::operator delete(m_data, m_capacity * sizeof(T));
	}

	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 2;
};
