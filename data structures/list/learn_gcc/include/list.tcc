//
// Created by Isa on 3/13/21.
//

#ifndef LIST_TCC
#define LIST_TCC


namespace gcc
{
    template<typename Tp, typename Alloc>
    void list_base<Tp, Alloc>::m_clear() noexcept
    {
        using node = list_node<Tp>;
        detail::list_node_base* curr = m_impl.m_node.m_next;

        while(curr != &m_impl.m_node)
        {
            node* tmp = static_cast<node*> (curr);
            curr = tmp->m_next;
            Tp* val = tmp->m_valptr();

            node_alloc_traits::destroy(m_get_node_allocator(), val);

            m_put_node(tmp);
        }
    }


    template<typename Tp, typename Alloc>
    void list<Tp, Alloc>::m_default_append(size_type n)
    {
        size_type i = 0;
        try
        {
            for(; i < n; ++i)
            {
                emplace_back();
            }
        }
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
    void list<Tp, Alloc>::m_assign_dispatch(Input_iterator first2, Input_iterator last2, std::false_type)
    {
        iterator f = begin();
        iterator l = end();

        for(; f != l && first2 != last2; ++f, (void) ++first2)
        {
            *f = *first2;
        }

        if(first2 == last2)
        {
            erase(f, l);
        }
        else
        {
            insert(l, first2, last2);
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

    template<typename Tp, typename Alloc>
    typename list<Tp, Alloc>::const_iterator list<Tp, Alloc>::m_resize_pos(size_type& new_size) const
    {
        const_iterator i;
        // c++11 abi
        const size_type len = size();
        if(new_size < len)
        {
            if(new_size <= len / 2)
            {
                i = begin();
                std::advance(i, new_size);
            }
            else
            {
                i = end();
                ptrdiff_t num_erase = len - new_size;
                std::advance(i, -num_erase);
            }
            new_size = 0;
            return i;
        }
        else
        {
            i = end();
        }

        new_size -= len;
        return i;
    }

}


#endif //LIST_TCC
