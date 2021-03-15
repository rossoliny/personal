//
// Created by Isa on 3/16/21.
//

#ifndef LIST_NODE_H
#define LIST_NODE_H
#include "aligned_buffer.h"

namespace gcc
{

    namespace detail
    {

        struct list_node_base
        {
            list_node_base *m_next;
            list_node_base *m_prev;

            static void swap(list_node_base &x, list_node_base &y) noexcept
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

            void m_transfer(list_node_base *const first, list_node_base *const last) noexcept
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

            void m_reverse() noexcept
            {
                list_node_base* curr = this;

                do
                {
                    std::swap(curr->m_next, curr->m_prev);

                    curr = curr->m_prev; // forward traversal (not reversed)
                } while (curr != this);
            }

            void m_hook(list_node_base *const position) noexcept
            {
                this->m_next = position;
                position->m_prev->m_next = this;
                this->m_prev = position->m_prev;
                position->m_prev = this;
            }

            void m_unhook() noexcept
            {
                this->m_prev->m_next = this->m_next;
                this->m_next->m_prev = this->m_prev;
            }

        };

        struct list_node_header : public list_node_base
        {
            std::size_t m_size;

            void m_init() noexcept
            {
                this->m_next = this->m_prev = this;
                this->m_size = 0;
            }

        private:
            list_node_base* m_base()
            {
                return this;
            }

        public:
            list_node_header() noexcept
            {
                m_init();
            }

            list_node_header(list_node_header&& other) noexcept
                    : list_node_base { other.m_next, other.m_prev }
                    , m_size(other.m_size)
            {
                if(other.m_base()->m_next == other.m_base())
                {
                    this->m_next = this->m_prev = this;
                }
                else
                {
                    this->m_next->m_prev =
                    this->m_prev->m_next = this->m_base();

                    other.m_init();
                }
            }

            void m_move_nodes(list_node_header&& other)
            {
                list_node_base* const other_base = other.m_base();
                if(other_base->m_next == other_base)
                {
                    m_init();
                }
                else
                {
                    list_node_base* const mbase = this->m_base();
                    mbase->m_next = other_base->m_next;
                    mbase->m_prev = other_base->m_prev;
                    mbase->m_prev->m_next = mbase->m_next->m_prev = mbase;
                    this->m_size = other.m_size;

                    other.m_init();
                }
            }
        };

    } // namespace detail

    template<typename Tp>
    struct list_node : public detail::list_node_base
    {
        gcc::aligned_membuf<Tp> m_storage;
        Tp* m_valptr()
        {
            return m_storage.m_ptr();
        }

        Tp const* m_valptr() const
        {
            return m_storage.m_ptr();
        }
    };
}


#endif //LIST_NODE_H
