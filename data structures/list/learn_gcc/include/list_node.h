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

            // swaps two nodes at any positions (not necessary adjacent nodes)
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

            // inserts [first, last) before this node
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

            // links this before position
            void m_hook(list_node_base *const position) noexcept
            {
                this->m_next = position;
                position->m_prev->m_next = this;
                this->m_prev = position->m_prev;
                position->m_prev = this;
            }

            // unlinks this from sequence
            void m_unhook() noexcept
            {
                this->m_prev->m_next = this->m_next;
                this->m_next->m_prev = this->m_prev;
            }

        };




        // LIST HEAD
        struct list_node_header : public list_node_base
        {
            std::size_t m_size;

            void m_init() noexcept
            {
                // if next == this then node is empty
                this->m_next = this->m_prev = this;
                this->m_size = 0;
            }

        private:

            // implicitly casts this into to list_node_base and return pointer;
            list_node_base* m_base()
            {
                return this;
            }

        public:

            // constructs empty header node
            list_node_header() noexcept
            {
                m_init();
            }


            // move constructor
            list_node_header(list_node_header&& rval) noexcept
                    : list_node_base { rval.m_next, rval.m_prev }
                    , m_size(rval.m_size)
            {
                // if rval is empty then this is also empty
                if(rval.m_base()->m_next == rval.m_base())
                {
                    // in delegating ctor next and prev initialized to point to rval's next and rval's prev
                    // make this be empty
                    this->m_next = this->m_prev = this;
                }
                else
                {
                    // next and prev are initialized in delegating constructor
                    // now use them to make next->prev and prev->next point to this
                    this->m_next->m_prev = this->m_prev->m_next = this->m_base();

                    // clear rval
                    rval.m_init();
                }
            }

            // move assignment
            void m_move_nodes(list_node_header&& rval)
            {
                list_node_base* const rval_base = rval.m_base();

                // if rval is empty then this is also empty
                if(rval_base->m_next == rval_base)
                {
                    m_init();
                }
                else
                {
                    list_node_base* const this_base = this->m_base();
                    // copy next and prev addresses
                    this_base->m_next = rval_base->m_next;
                    this_base->m_prev = rval_base->m_prev;

                    // use copied addresses to make next->prev and prev->next point to this
                    this_base->m_prev->m_next = this_base->m_next->m_prev = this_base;
                    this->m_size = rval.m_size;

                    rval.m_init();
                }
            }
        };

    } // namespace detail



    // ORDINARY LIST NODE
    template<typename Tp>
    struct list_node : public detail::list_node_base
    {
        gcc::aligned_membuf<Tp> m_storage;

        // pointer to actual data
        Tp* m_valptr()
        {
            return m_storage.m_ptr();
        }

        // const ptr to actual data
        Tp const* m_valptr() const
        {
            return m_storage.m_ptr();
        }
    };
}


#endif //LIST_NODE_H
