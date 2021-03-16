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
        iterator f = begin();
        iterator l = end();

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
        iterator i = begin();
        for(; i != end() && n > 0; ++i, --n)
        {
            *i = val;
        }

        if(n > 0)
        {
            insert(end(), n, val);
        }
        else
        {
            erase(i, end());
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
        const size_type len = size();
        //if list shrinks
        if(new_size < len)
        {
            // if position is inside first half
            // then it's faster to advance from begining
            if(new_size <= len / 2)
            {
                i = begin();
                std::advance(i, new_size);
            }
            // if position is inside second half
            else
            {
                i = end();
                ptrdiff_t num_erase = len - new_size;
                std::advance(i, -num_erase);
            }
            new_size = 0;
            return i;
        }
        // else list grows or stays as is
        else
        {
            i = end();
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
            if(node_alloc_traits::propagate_on_container_copy_assignment::value)
            {
                auto& this_alloc = this->m_get_node_allocator();
                auto& other_alloc = other.m_get_node_allocator();

                if (!node_alloc_traits::is_always_equal::value && this_alloc != other_alloc)
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
			erase(it, end());
		}
	}



    template<typename Tp, typename Alloc>
    typename list<Tp, Alloc>::iterator list<Tp, Alloc>::insert(const_iterator pos, size_type n, const value_type& val)
	{
		if(n)
		{
			list tmp(n, val, get_allocator());
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
        list tmp(first, last, get_allocator());
        if(!tmp.empty())
        {
            iterator it = tmp.begin();
            splice(position, tmp);
            return it;
        }
        return position.m_const_cast();
    }


}


#endif //LIST_TCC
