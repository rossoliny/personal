//
// Created by Isa on 3/13/21.
//

#ifndef LIST_TCC
#define LIST_TCC


namespace gcc
{
    // O(N)
    // calls allocator_traits::destroy on each element
    // calls allocator_traits::deallocate on each node.
    template<typename Tp, typename Alloc>
    void list_base<Tp, Alloc>::m_clear() noexcept
    {
        using node = list_node<Tp>;
        detail::list_node_base* curr = m_impl.m_node.m_next;

        while(curr != &m_impl.m_node)
        {
            node* node_to_delete = static_cast<node*> (curr);
            Tp* val_to_delete = node_to_delete->m_valptr();

            curr = node_to_delete->m_next;

            // only destroys object as its memory is part of node
            // so deallocation of node deallocates object's memory
            node_alloc_traits::destroy(m_get_node_allocator(), val_to_delete);

            m_put_node(node_to_delete);
        }
    }


    template<typename Tp, typename Alloc>
    void list<Tp, Alloc>::m_default_append(size_type n)
    {
        size_type i = 0;
        // try to default construct n elements and append to tail
        try
        {
            for(; i < n; ++i)
            {
                emplace_back();
            }
        }
        // if failed then rollback all changes
        catch (...)
        {
            for(; i; --i)
            {
                pop_back();
            }
            throw;
        }
    }

    template<typename Tp, typename Alloc>
    template<typename Input_iterator>
    void list<Tp, Alloc>::m_assign_dispatch(Input_iterator first, Input_iterator last, std::false_type)
    {
        iterator f = this->begin();
        iterator l = this->end();

        for(; f != l && first != last; ++f, (void) ++first)
        {
            *f = *first;
        }

        // if this list is longer than other then erase extra elements
        if(first == last)
        {
            erase(f, l);
        }
        // if this list is shorter then copy remaining elements from other
        else
        {
            insert(l, first, last);
        }
    }

    template<typename Tp, typename Alloc>
    void list<Tp, Alloc>::m_fill_assign(size_type n, const value_type& val)
    {
        iterator i = this->begin();
        for(; i != this->end() && n > 0; ++i, --n)
        {
            *i = val;
        }

        if(n > 0)
        {
            insert(this->end(), n, val);
        }
        else
        {
            erase(i, this->end());
        }
    }


    // returns iterator pointing to position at which to insert new elememts or after which to erase extra elememts
    // returns difference between list.size() and new_size if new_size >= list.size()
    // else returns 0
    template<typename Tp, typename Alloc>
    typename list<Tp, Alloc>::const_iterator list<Tp, Alloc>::m_resize_pos(size_type& new_size) const
    {
        const_iterator i;
        // c++11 abi
        const size_type len = this->size();
        //if list shrinks
        if(new_size < len)
        {
            // if position is inside first half
            // then it's faster to advance from begining
            if(new_size <= len / 2)
            {
                i = this->begin();
                std::advance(i, new_size);
            }
            // if position is inside second half
            else
            {
                i = this->end();
                ptrdiff_t num_erase = len - new_size;
                std::advance(i, -num_erase);
            }
            new_size = 0;
            return i;
        }
        // else list grows or stays as is
        else
        {
            i = this->nd();
        }
        // c++11 abi

        new_size -= len;
        return i;
    }

    // list public interface
    template<typename Tp, typename Alloc>
    list<Tp, Alloc>& list<Tp, Alloc>::operator=(const list<Tp, Alloc>& other)
    {
        if(this != std::addressof(other))
        {
            if(this->node_alloc_traits::propagate_on_container_copy_assignment::value)
            {
                auto& this_alloc = this->m_get_node_allocator();
                auto& other_alloc = other.m_get_node_allocator();

                if (!this->node_alloc_traits::is_always_equal::value && this_alloc != other_alloc)
                {
                    // replacement allocator cannot free existing storage
                    clear();
                }
                alloc_on_copy(this_alloc, other_alloc);
            }
        }
        m_assign_dispatch(other.begin(), other.end(), std::false_type());
        return *this;
    }

    template<typename Tp, typename Alloc>
    void list<Tp, Alloc>::resize(size_type new_size)
	{
		const_iterator it = m_resize_pos(new_size);
		if (new_size)
		{
			m_default_append(new_size);
		}
		else
		{
			erase(it, this->end());
		}
	}

	template<typename Tp, typename Alloc>
	void list<Tp, Alloc>::resize(size_type new_size, const value_type& val)
	{
		const_iterator it = m_resize_pos(new_size);
		if(new_size)
		{
			insert(this->end(), new_size, val);
		}
		else
		{
			erase(it, this->end());
		}
	}

	template<typename Tp, typename Alloc>
	template<typename... Args>
	typename list<Tp, Alloc>::iterator list<Tp, Alloc>::emplace(const_iterator position, Args&&... args)
	{
		node* _node = m_create_node(std::forward<Args>(args)...);

		_node->m_hook(position.m_const_cast().m_node);
		this->m_inc_size(1);

		return iterator(_node);
	}

	template<typename Tp, typename Alloc>
	typename list<Tp, Alloc>::iterator list<Tp, Alloc>:: insert(const_iterator position, const value_type& val)
	{
		node* _node = m_create_node(val);

		_node->m_hook(position.m_const_cast().m_node);
		this->m_inc_size(1);

		return iterator(_node);
	}


	template<typename Tp, typename Alloc>
    typename list<Tp, Alloc>::iterator list<Tp, Alloc>::insert(const_iterator pos, size_type n, const value_type& val)
	{
		if(n)
		{
			list tmp(n, val, this->get_allocator());
			iterator it = tmp.begin();
			splice(pos, tmp);
			return it;
		}
		return pos.m_const_cast();
	}

    template<typename Tp, typename Alloc>
    template<typename Input_iterator, typename>
    typename list<Tp, Alloc>::iterator list<Tp, Alloc>::insert(const_iterator position, Input_iterator first, Input_iterator last)
    {
        list tmp(first, last, this->get_allocator());
        if(!tmp.empty())
        {
            iterator it = tmp.begin();
            splice(position, tmp);
            return it;
        }
        return position.m_const_cast();
    }

	template<typename Tp, typename Alloc>
	typename list<Tp, Alloc>::iterator list<Tp, Alloc>::erase(const_iterator position) noexcept
	{
		iterator erased = iterator(position.m_node->m_next);
		m_erase(position.m_const_cast());
		return erased;
	}

	template<typename Tp, typename Alloc>
	void list<Tp, Alloc>::remove(const value_type& value)
	{
		list to_destroy(this->get_allocator());
		iterator first = this->begin();
		iterator last = this->end();

		while(first != last)
		{
			iterator next = first;
			++next;

			if(*first == value)
			{
				// _GLIBCXX_RESOLVE_LIB_DEFECTS
				// 526. Is it undefined if a function in the standard changes
				// in parameters?
				to_destroy.splice(to_destroy.begin(), *this, first);

			}

			first = next;
		}
	}


	template<typename Tp, typename Alloc>
	template <typename Predicate>
	void list<Tp, Alloc>::remove_if(Predicate pred)
	{
		list to_destroy(this->get_allocator());
		iterator first = this->begin();
		iterator last = this->end();

		while(first != last)
		{
			iterator next = first;
			++next;

			if(pred(*first))
			{
				to_destroy.splice(to_destroy.begin(), *this, first);
			}
			first = next;
		}
	}

	template<typename Tp, typename Alloc>
	void list<Tp, Alloc>::unique()
	{
		iterator first = this->begin();
		iterator last = this->end();
		if(first == last)
		{
			return;
		}

		list to_destroy(this->get_allocator());
		iterator next = first;

		while(++next != last)
		{
			if(*first == *next)
			{
				to_destroy.splice(to_destroy.begin(), *this, next);
			}
			else
			{
				first = next;
			}
			next = first;
		}

	}

	template<typename Tp, typename Alloc>
	template <typename Binary_predicate>
	void list<Tp, Alloc>::unique(Binary_predicate binary_pred)
	{
		iterator first = this->begin();
		iterator last = this->end();

		if(first == last)
		{
			return;
		}

		list to_destroy(this->get_allocator());
		iterator next = first;

		while(++next != last)
		{
			if(binary_pred(*first, *next))
			{
				to_destroy.splice(to_destroy.begin(), *this, next);
			}
			else
			{
				first = next;
			}
			next = first;
		}

	}


	template<typename Tp, typename Alloc>
	void list<Tp, Alloc>::merge(list&& rval)
	{
		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 300. list::merge() specification incomplete
		if(this != std::addressof(rval))
		{
			m_check_equal_allocators(rval);

			iterator first1 = this->begin();
			iterator last1 = this->end();
			iterator first2 = rval.begin();
			iterator last2 = rval.end();
			const size_t rval_orig_size = rval.size();

			try
			{
				while(first1 != last1 && first2 != last2)
				{
					if(*first2 < *first1)
					{
						iterator next = first2;
						m_transfer(first1, first2, ++next);
						first2 = next;
					}
					else
					{
						++first1;
					}
				}
				if(first2 != last2)
				{
					m_transfer(last1, first2, last2);
				}

				this->m_inc_size(rval.m_get_size());
				rval.m_set_size(0);
			}
			catch(...)
			{
				const size_t dist = std::distance(first2, last2);
				this->_inc_size(rval_orig_size - dist);
				rval.m_set_size(dist);

				throw;
			}
		}
	}



	template<typename Tp, typename Alloc>
	template <typename Strict_weak_ordering_comparator>
	void list<Tp, Alloc>::merge(list&& rval, Strict_weak_ordering_comparator comp)
	{
		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 300. list::merge() specification incomplete
		if(this != std::addressof(rval))
		{
			m_check_equal_allocators(rval);

			iterator first1 = this->begin();
			iterator last1 = this->end();
			iterator first2 = rval.begin();
			iterator last2 = rval.end();
			const size_t rval_orig_size = rval.size();

			try
			{
				while(first1 != last1 && first2 != last2)
				{
					if(comp(*first2, *first1))
					{
						iterator __next = first2;
						m_transfer(first1, first2, ++__next);
						first2 = __next;
					}
					else
					{
						++first1;
					}
				}
				if(first2 != last2)
				{
					m_transfer(last1, first2, last2);
				}

				this->m_inc_size(rval.m_get_size());
				rval.m_set_size(0);
			}
			catch(...)
			{
				const size_t dist = std::distance(first2, last2);
				this->m_inc_size(rval_orig_size - dist);
				rval.m_set_size(dist);

				throw;
			}
		}
	}



	template<typename Tp, typename Alloc>
	void list<Tp, Alloc>::sort()
	{
		// Do nothing if the list has length 0 or 1.
		if(this->m_impl.m_node.m_next != &this->m_impl.m_node
			&& this->m_impl.m_node.m_next->m_next != &this->m_impl.m_node)
		{
			list carry;
			list tmp[64];
			list* fill = tmp;
			list* counter;

			try
			{
				do
				{
					carry.splice(carry.begin(), *this, this->begin());

					for(counter = tmp; counter != fill && !counter->empty(); ++counter)
					{
						counter->merge(carry);
						carry.swap(*counter);
					}
					carry.swap(*counter);
					if(counter == fill)
					{
						++fill;
					}
				} while(!this->empty());

				for(counter = tmp + 1; counter != fill; ++counter)
				{
					counter->merge(*(counter - 1));
				}
				swap(*(fill - 1));
			}
			catch(...)
			{
				this->splice(this->end(), carry);
				for(int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
				{
					this->splice(this->end(), tmp[i]);
				}

				throw;
			}
		}
	}


	template<typename _Tp, typename _Alloc>
	template <typename _StrictWeakOrdering>
	void
	list<_Tp, _Alloc>::
	sort(_StrictWeakOrdering __comp)
	{
		// Do nothing if the list has length 0 or 1.
		if(this->m_impl.m_node.m_next != &this->m_impl.m_node
				&& this->m_impl.m_node.m_next->m_next != &this->m_impl.m_node)
		{
			list carry;
			list tmp[64];
			list* fill = tmp;
			list* counter;
			try
			{
				do
				{
					carry.splice(carry.begin(), *this, this->begin());

					for(counter = tmp;
							counter != fill && !counter->empty();
							++counter)
					{
						counter->merge(carry, __comp);
						carry.swap(*counter);
					}
					carry.swap(*counter);
					if(counter == fill)
					{
						++fill;
					}
				} while(!this->empty());

				for(counter = tmp + 1; counter != fill; ++counter)
				{
					counter->merge(*(counter - 1), __comp);
				}
				swap(*(fill - 1));
			}
			catch(...)
			{
				this->splice(this->end(), carry);
				for(int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
				{
					this->splice(this->end(), tmp[i]);
				}

				throw;
			}
		}
	}

}


#endif //LIST_TCC
