#pragma one

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

	size_t size() const 
	{ 
		return m_size; 
	}

	const T& operator[](size_t pos) const
	{
		return m_data[pos];
	}

	T& operator[](size_t pos)
	{
		return m_data[pos];
	}

	void clear()
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
	void check_cap()
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

		/*
		m_size = m_size > new_capacity ? new_capacity : m_size;
		for(int i = 0; i < m_size; ++i)
		{
			m_data[i].~T();	
		}
		*/

		::operator delete(m_data, m_capacity * sizeof(T));
		m_data = reinterpret_cast<T*> (new_mem);
		m_capacity = new_capacity;
	}

	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};
