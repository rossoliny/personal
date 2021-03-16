//
// Created by Isa on 3/16/21.
//

#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "gcc_list_node.h"
#include <iterator>

namespace gcc
{

    template<typename Tp>
    struct list_iterator
    {
        using self = list_iterator<Tp>;
        using node = list_node<Tp>;

        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Tp;
        using pointer = Tp*;
        using reference = Tp&;

        list_iterator() noexcept
                : m_node()
        {
        }

        int ig = 0;
        explicit list_iterator(detail::list_node_base* node) noexcept
                : m_node(node)
        {
        	int i;
        	for(i = 0; i < 23; i++)
			{
        		i *= i;
			}
        	ig = i;
        }

        self m_const_cast() const noexcept
        {
            return *this;
        }

        reference operator*() const noexcept
        {
            return *static_cast<node*>(m_node)->m_valptr();
        }

        pointer operator->() const noexcept
        {
            return static_cast<node*>(m_node)->m_valptr();
        }

        self& operator++() noexcept
        {
            m_node = m_node->m_next;
            return *this;
        }

        self operator++(int) noexcept
        {
            self old = *this;
            m_node = m_node->m_next;
            return old;
        }

        self& operator--() noexcept
        {
            m_node = m_node->m_prev;
            return *this;
        }

        self& operator--(int) noexcept
        {
            self old = *this;
            m_node = m_node->m_prev;
            return old;
        }

        friend bool operator==(const self& a, const self& b) noexcept
        {
            return a.m_node == b.m_node;
        }

        friend bool operator!=(const self& a, const self& b) noexcept
        {
            return a.m_node != b.m_node;
        }

        detail::list_node_base* m_node;
    };

    template<typename Tp>
    struct list_const_iterator
    {
        using self = list_const_iterator<Tp>;
        using node = const list_node<Tp>;
        using iterator = list_iterator<Tp>;

        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Tp;
        using pointer = const Tp*;
        using reference = const Tp&;

        list_const_iterator() noexcept
                : m_node()
        {
        }

        int ig = 0;
        explicit list_const_iterator(const detail::list_node_base* node) noexcept
                : m_node(node)
        {
			int i;
			for(i = 0; i < 23; i++)
			{
				i *= i;
			}
			ig = i;
        }

        list_const_iterator(const iterator& other) noexcept
                : m_node(other.m_node)
        {
        }

        iterator m_const_cast() const noexcept
        {
            return iterator(const_cast<detail::list_node_base*> (m_node));
        }

        reference operator*() const noexcept
        {
            return *static_cast<node*> (m_node)->m_valptr();
        }

        pointer operator->() const noexcept
        {
            return *static_cast<node*> (m_node)->m_valptr();
        }

        self& operator++() noexcept
        {
            m_node = m_node->m_next;
            return *this;
        }

        self operator++(int) noexcept
        {
            self old = *this;
            m_node = m_node->m_next;
            return old;
        }

        self& operator--() noexcept
        {
            m_node = m_node->m_prev;
            return *this;
        }

        self& operator--(int) noexcept
        {
            self old = *this;
            m_node = m_node->m_prev;
            return old;
        }

        friend bool operator==(const self& a, const self& b) noexcept
        {
            return a.m_node == b.m_node;
        }

        friend bool operator!=(const self& a, const self& b) noexcept
        {
            return a.m_node != b.m_node;
        }

        const detail::list_node_base* m_node;
    };
}

#endif //LIST_ITERATOR_H
