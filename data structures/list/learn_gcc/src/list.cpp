//
// Created by Isa on 3/13/21.
//

#include "list"
#include <utility>

namespace gcc
{

    namespace detail
    {

        void list_node_base::swap(list_node_base& x, list_node_base& y) noexcept
        {
            if(x.m_next != &x)
            {
                if (y.m_next != &y)
                {
                    // both x and y are not empty
                    std::swap(x.m_next, y.m_next);
                    std::swap(x.m_prev, y.m_prev);
                    // update neighbour nodes
                    x.m_next->m_prev = x.m_prev->m_next = &x;
                    y.m_next->m_prev = y.m_prev->m_next = &y;
                }
                else
                {
                    // x is not empty, y is empty
                    y.m_next = x.m_next;
                    y.m_prev = x.m_prev;
                    y.m_next->m_prev = y.m_prev->m_next = &y;
                    // make x empty
                    x.m_next = x.m_prev = &x;
                }
            }
            else if (y.m_next != &y)
            {
                // x is empty, y is not empty
                x.m_next = y.m_next;
                x.m_prev = y.m_prev;
                x.m_prev->m_next = x.m_next->m_prev = &x;
                // make y empty
                y.m_next = y.m_prev = &y;
            }
        }

        void list_node_base::m_transfer(list_node_base* const first, list_node_base* const last) noexcept
        {
            if(last != this)
            {

                list_node_base *pre_last = last->m_prev;

                // unlink [first, last) from original sequence
                last->m_prev = first->m_prev;
                first->m_prev->m_next = last;

                // link pre_this into first
                first->m_prev = this->m_prev;
                this->m_prev->m_next = first;

                // link this into pre_last
                this->m_prev = pre_last;
                pre_last->m_next = this;
            }
        }

        void list_node_base::m_reverse() noexcept
        {
            list_node_base* curr = this;

            do
            {
                std::swap(curr->m_next, curr->m_prev);

                curr = curr->m_prev; // forward traversal (not reversed)
            } while (curr != this);
        }

        // insert this before position
        void list_node_base::m_hook(list_node_base* const position) noexcept
        {
            this->m_next = position;
            position->m_prev->m_next = this;
            this->m_prev = position->m_prev;
            position->m_prev = this;
        }

        void list_node_base::m_unhook() noexcept
        {
            this->m_prev->m_next = this->m_next;
            this->m_next->m_prev = this->m_prev;
        }
    }

}