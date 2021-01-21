



namespace isa
{
	template<class InputIterator>
	string::string(InputIterator first, InputIterator last)
		: _size { static_cast<size_t> (std::distance(first, last)) }
		, space { 0 }
	{
		if(_size > max_size())
		{
			throw std::length_error("string::string(InputIterator, InputIteartor) - size of constructed string will exceed maximum possible size");
		}
		_data = _size <= short_max ? small_buff : new char[_size + 1];
		size_t i = 0;
		while(first != last)
		{
			_data[i++] = *first;
			++first;
		}
	}

}
