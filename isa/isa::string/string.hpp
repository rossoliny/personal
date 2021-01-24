
namespace isa
{
	template<class InputIterator>
	string::string(InputIterator first, InputIterator last)
		: _size { static_cast<size_t> (std::distance(first, last)) }
		, space { 0 }
	{
		check_new_size(_size);

		_data = _size <= short_max ? small_buff : new char[_size + 1];
		size_t i = 0;
		while(first != last)
		{
			_data[i++] = *first;
			++first;
		}
		_data[_size] = '\0';
	}

}

