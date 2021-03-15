//
// Created by Isa on 3/13/21.
//

#ifndef GCC_STL_LIST_H
#define GCC_STL_LIST_H


#include "list_iterator.h"
#include "list_node.h"

#include "tmp_utils.h"

#include <type_traits>
#include <memory>


namespace gcc
{
    // list_base
    template<typename Tp, typename Alloc>
    class list_base
    {
    protected:
        using Tp_alloc_type = typename std::allocator_traits<Alloc>::template rebind_alloc<Tp>;
        using Tp_alloc_traits = std::allocator_traits<Tp_alloc_type>;

        using node_alloc_type = typename Tp_alloc_traits::template rebind_alloc<list_node<Tp>>;
        using node_alloc_traits = std::allocator_traits<node_alloc_type>;

        // if not inline version
        static size_t s_distance(const detail::list_node_base *first, const detail::list_node_base *last)
        {
            size_t n = 0;
            while (first != last) {
                first = first->m_next;
                ++n;
            }
            return n;
        }


        // list_impl
        struct list_impl : public node_alloc_type
        {
            detail::list_node_header m_node;

            list_impl() noexcept(std::is_nothrow_default_constructible<node_alloc_type>::value)
                : node_alloc_type()
            {
            }

            list_impl(const node_alloc_type& other_base) noexcept
                : node_alloc_type(other_base)
            {
            }

            list_impl(list_impl&&) = default;

            list_impl(node_alloc_type&& rval_base, list_impl&& rval)
                : node_alloc_type(std::move(rval_base), std::move(rval))
            {
            }

            list_impl(node_alloc_type&& rval_base) noexcept
                : node_alloc_type(std::move(rval_base))
            {
            }

        };

        list_impl m_impl;

        size_t m_get_size() const
        {
            return m_impl.m_node.m_size;
        }

        void m_set_size(size_t n)
        {
            m_impl.m_node.m_size = n;
        }

        void m_inc_size(size_t n)
        {
            m_impl.m_node.m_size += n;
        }

        void m_dec_size(size_t n)
        {
            m_impl.m_node.m_size -= n;
        }

        // if not inline version
        size_t m_distance(const detail::list_node_base* first, const detail::list_node_base* last) const
        {
            return s_distance(first, last);
        }

        // if not inline version
        // return the stored size
        size_t m_node_count() const
        {
            // return m_impl.m_node.m_size
            return m_get_size();
        }


        // uses m_impl.allocate to allocate m_impl::value_type (aka list_node<Tp>)
        // return pointer (aka allocator_traits< allocator<list_node<Tp>> >*)
        typename node_alloc_traits::pointer m_get_node()
        {
            return node_alloc_traits::allocate(m_impl, 1);
        }

        void m_put_node(typename node_alloc_traits::pointer p) noexcept
        {
            node_alloc_traits::deallocate(m_impl, p, 1);
        }

    public:
        using allocator_type = Alloc;

        // returns reference to instance of used allocator
        node_alloc_type& m_get_node_allocator() noexcept
        {
            return m_impl;
        }

        const node_alloc_type& m_get_node_allocator() const noexcept
        {
            return m_impl;
        }

        list_base() = default;

        list_base(list_base&&) = default;

        // constructs list_base with provided node_allocator
        list_base(const node_alloc_type& alloc) noexcept
            : m_impl(alloc) // calls allocator_type's ctor and passes args there
        {
        }

        // if not inline version
        list_base(list_base&& rval, node_alloc_type&& rval_alloc)
            : m_impl(std::move(rval_alloc)) // calls allocator_type's ctor and passes args there
        {
            if (rval.m_get_node_allocator() == m_get_node_allocator())
                m_move_nodes(std::move(rval));
            // else caller must move individual elements.
        }

        // Used when allocator !is_always_equal.
        //
        list_base(node_alloc_type&& impl, list_base&& other)
            : m_impl(std::move(impl), std::move(other.m_impl)) // calls allocator_type's ctor and passes args there
        {
        }

        // Used when allocator !is_always_equal.
        list_base(node_alloc_type&& impl)
            : m_impl(std::move(impl)) // calls allocator_type's ctor and passes args there
        {
        }

        // unlinks r_val.m_impl.m_node (header) from entire sequence
        // and links that sequence with this->m_impl.m_node
        void m_move_nodes(list_base&& rval)
        {
            m_impl.m_node.m_move_nodes(std::move(rval.m_impl.m_node));
        }

        ~list_base() noexcept
        {
            m_clear();
        }

        // in file list.tcc
        void m_clear() noexcept;

        // makes m_node empty and size = 0
        void m_init() noexcept
        {
            this->m_impl.m_node.m_init();
        }

    };



    // finally list itself
    template<typename Tp, typename Alloc = std::allocator<Tp>>
    class list : protected list_base<Tp, Alloc>
    {
        static_assert(std::is_same<typename std::remove_cv<Tp>::type, Tp>::value, "gcc::list must have a non-const, non-volatile value_type");

        using base = list_base<Tp, Alloc>;
        using Tp_alloc_type = typename base::Tp_alloc_type;
        using Tp_alloc_traits = typename base::Tp_alloc_traits;

        using node_alloc_type = typename base::node_alloc_type;
        using node_alloc_traits = typename base::node_alloc_traits;


    public:

        using value_type = Tp;
        using pointer           = typename Tp_alloc_traits::pointer;
        using const_pointer     = typename Tp_alloc_traits::const_pointer;

        // C++11 allocators do not define reference or const_reference
        using reference         = value_type&;
        using const_reference   = const value_type&;

        using iterator              = list_iterator<Tp>;
        using const_iterator        = list_const_iterator<Tp>;
        using reverse_iterator      = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using allocator_type = Alloc;

    protected:
        using node = list_node<Tp>;

        using base::m_impl;
        using base::m_put_node;
        using base::m_get_node;
        using base::m_get_node_allocator;


        // allocates node and constructs new object(elemnt) in allocated memory
        template<typename... Args>
        node* m_create_node(Args&&... args)
        {
            // calls allocator_traits::allocate(m_impl, 1)
            auto p = this->m_get_node();
            // return m_impl
            auto& alloc = m_get_node_allocator();
            // allocated_ptr<node_alloc_type> guard{alloc, p};
            node_alloc_traits::construct(alloc, p->m_valptr(), std::forward<Args>(args)...);
            // guard = nullptr;
            return p;
        }


        static size_t s_distance(const_iterator first, const_iterator last)
        {
            return std::distance(first, last);
        }

        // return the stored size
        size_t m_node_count() const
        {
            // m_get_size returns super->m_impl.m_node.m_size
            return this->m_get_size();
        }


    public:

        // Public interface

        list() = default;

        explicit list(allocator_type& alloc) noexcept
            : base(node_alloc_type(alloc))
        {
        }

        /**
         *  This constructor fills the list with n default
         *  constructed elements.
         */
        explicit list(size_type n, const allocator_type& alloc = allocator_type())
            : base(node_alloc_type(alloc))
        {
            m_default_initialize(n);
        }

        /**
         *
         *  This constructor fills the list with n copies of value.
         */
        explicit list(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
            : base(node_alloc_type(alloc))
        {
            m_fill_initialize(n, val);
        }

        /**
         *  The newly-created list uses a copy of the allocation object used
         *  by other (unless the allocator traits dictate a different object).
         */
        list(const list& other)
            : base(node_alloc_traits::select_on_container_copy_construction(other.m_get_node_allocator()))
        {
            m_initialize_dispatch(other.begin(), other.end(), std::false_type());
        }

        /**
         *  The newly-created list contains the exact contents of the moved
         *  instance. The contents of the moved instance are a valid, but
         *  unspecified list.
         */
        list(list&&) = default;

        /**
         *  Create a list consisting of copies of the elements in the
         *  initializer_list il.  This is linear in il.size().
         */
        list(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type())
            : base(node_alloc_type(alloc))
        {
            m_initialize_dispatch(il.begin(), il.end(), std::false_type());
        }

        list(const list& other, const allocator_type& alloc)
            : base(node_alloc_type(alloc))
        {
            m_initialize_dispatch(other.begin(), other.end(), std::false_type());
        }
    private:
        list(list&& rval, const allocator_type& alloc, std::true_type) noexcept
            : base(node_alloc_type(alloc), std::move(rval))
        {
        }

        list(list&& rval, const allocator_type& alloc, std::false_type)
            : base(node_alloc_type(alloc))
        {
            if(rval.m_get_node_allocator() == this->m_get_node_allocator())
            {
                this->m_move_nodes(std::move(rval));
            }
            else
            {
                insert(
                        begin(),
                        gcc::make_move_iterator_if_noexcept(rval.begin()),
                        gcc::make_move_iterator_if_noexcept(rval.end())
                      );
            }
        }

    public:
        list(list&& rval, const allocator_type& alloc) noexcept(node_alloc_traits::is_always_equal::value)
            : list(std::move(rval), alloc, typename node_alloc_traits::is_always_equal{})
        {
        }

        /**
         *  Create a list consisting of copies of the elements from
         *  [first, last).  This is linear in N (where N is
         *  std::distance(first, last)).
         */
        template<typename Input_iterator, typename = gcc::require_input_iter<Input_iterator>>
        list(Input_iterator first, Input_iterator last, const allocator_type& alloc = allocator_type())
                : base(node_alloc_type(alloc))
        {
            m_initialize_dispatch(first, last, std::false_type());
        }

        /**
         *  No explicit dtor needed as the $base dtor takes care of
         *  things.  The $base dtor only erases the elements, and note
         *  that if the elements themselves are pointers, the pointed-to
         *  memory is not touched in any way.  Managing the pointer is
         *  the user's responsibility.
         */
        ~list() = default;

        // assign operators

        /**
         *  All the elements of other are copied.
         *
         *  Whether the allocator is copied depends on the allocator traits.
         */
        list& operator=(const list& other); // impl in list.tcc

        /**
         *
         *  The contents of rval are moved into this list (without copying).
         *
         *  Afterwards rval is a valid, but unspecified list
         *
         *  Whether the allocator is moved depends on the allocator traits.
         */
        list& operator=(list&& rval)
                noexcept(node_alloc_traits::propagate_on_container_move_assignment::value || node_alloc_traits::is_always_equal::value)
        {
            constexpr bool move_storage =
                    node_alloc_traits::propagate_on_container_move_assignment::value || node_alloc_traits::is_always_equal::value;

            m_move_assign(std::move(rval), gcc::bool_constant<move_storage>());
            return *this;
        }

        /**
         *  Replace the contents of the list with copies of the elements
         *  in the std::initializer_list il.  This is linear in il.size().
         */
        list& operator=(std::initializer_list<value_type> il)
        {
            this->assign(il.begin(), il.end());
            return *this;
        }


        // assign funciton
        /**
         *  This function fills a list with n copies of the given
         *  value.  Note that the assignment completely changes the list
         *  and that the resulting list's size is the same as the number
         *  of elements assigned.
         */
        void assign(size_type n, const value_type& val)
        {
            m_fill_assign(n, val);
        }

        /**
         *  This function fills a %list with copies of the elements in the
         *  range [@a __first,@a __last).
         *
         *  Note that the assignment completely changes the %list and
         *  that the resulting %list's size is the same as the number of
         *  elements assigned.
         */
        template<typename Input_iterator,
                typename = gcc::require_input_iter<Input_iterator>>
        void assign(Input_iterator first, Input_iterator last)
        {
            m_assign_dispatch(first, last, std::false_type());
        }



        /**
         *  Replace the contents of the list with copies of the elements
         *  in the std::initializer_list il.  This is linear in il.size().
         */
        void
        assign(std::initializer_list<value_type> il)
        {
            this->m_assign_dispatch(il.begin(), il.end(), std::false_type());
        }


        // Get a copy of the memory allocation object.
        allocator_type get_allocator() const noexcept
        {
            return allocator_type(base::m_get_node_allocator());
        }


        // iterator functions

        /**
         *  Returns a read/write iterator that points to the first element in the
         *  list.  Iteration is done in ordinary element order.
         */
        iterator begin() noexcept
        {
            return iterator(this->m_impl.m_node.m_next);
        }

        /**
         *  Returns a read-only (constant) iterator that points to the
         *  first element in the list.  Iteration is done in ordinary
         *  element order.
         */
        const_iterator begin() const noexcept
        {
            return const_iterator(this->m_impl.m_node.m_next);
        }

        /**
         *  Returns a read/write iterator that points one past the last
         *  element in the list.  Iteration is done in ordinary element
         *  order.
         */
        iterator end() noexcept
        {
            return iterator(&this->m_impl.m_node);
        }

        /**
         *  Returns a read-only (constant) iterator that points one past
         *  the last element in the list.  Iteration is done in ordinary
         *  element order.
         */
        const_iterator end() const noexcept
        {
            return const_iterator(&this->m_impl.m_node);
        }

        /**
         *  Returns a read/write reverse iterator that points to the last
         *  element in the list.  Iteration is done in reverse element
         *  order.
         */
        reverse_iterator rbegin() noexcept
        {
            return reverse_iterator(end());
        }

        /**
         *  Returns a read-only (constant) reverse iterator that points to
         *  the last element in the list.  Iteration is done in reverse
         *  element order.
         */
        const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator(end());
        }

        /**
         *  Returns a read/write reverse iterator that points to one
         *  before the first element in the list.  Iteration is done in
         *  reverse element order.
         */
        reverse_iterator rend() noexcept
        {
            return reverse_iterator(begin());
        }

        /**
         *  Returns a read-only (constant) reverse iterator that points to one
         *  before the first element in the list.  Iteration is done in reverse
         *  element order.
         */
        const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator(begin());
        }

        /**
         *  Returns a read-only (constant) iterator that points to the
         *  first element in the list.  Iteration is done in ordinary
         *  element order.
         */
        const_iterator cbegin() const noexcept
        {
            return const_iterator(this->m_impl.m_node.m_next);
        }

        /**
         *  Returns a read-only (constant) iterator that points one past
         *  the last element in the list.  Iteration is done in ordinary
         *  element order.
         */
        const_iterator cend() const noexcept
        {
            return const_iterator(&this->m_impl.m_node);
        }

        /**
         *  Returns a read-only (constant) reverse iterator that points to
         *  the last element in the list.  Iteration is done in reverse
         *  element order.
         */
        const_reverse_iterator crbegin() const noexcept
        {
            return const_reverse_iterator(end());
        }

        /**
         *  Returns a read-only (constant) reverse iterator that points to one
         *  before the first element in the list.  Iteration is done in reverse
         *  element order.
         */
        const_reverse_iterator crend() const noexcept
        {
            return const_reverse_iterator(begin());
        }

        size_type size() const noexcept
        {
            return m_node_count();
        }

        /**
         *  This is a typical stack operation.  The function creates an
         *  element at the end of the list and assigns the given data to
         *  it.  Due to the nature of a %list this operation can be done
         *  in constant time, and does not invalidate iterators and
         *  references.
         */
        void push_back(const value_type& x)
        {
            // end points to element after last which is first
            // m_insert inserts before first element which is after last
            this->m_insert(end(), x);
        }

        void push_back(value_type&& x)
        {
            this->m_insert(end(), std::move(x));
        }

        template<typename... Args>
        void emplace_back(Args&&... args)
        {
            this->m_insert(end(), std::forward<Args>(args)...);
        }


        /**
         *  This is a typical stack operation.  It shrinks the list by
         *  one.  Due to the nature of a list this operation can be done
         *  in constant time, and only invalidates iterators/references to
         *  the element being removed.
         *
         *  Note that no data is returned, and if the last element's data
         *  is needed, it should be retrieved before pop_back() is called.
         */
        void pop_back() noexcept
        {
            this->m_erase(iterator(this->m_impl.m_node.m_prev));
        }



        /**
         *  Erases all the elements.  Note that this function only erases
         *  the elements, and that if the elements themselves are
         *  pointers, the pointed-to memory is not touched in any way.
         *  Managing the pointer is the user's responsibility.
         */
        void clear() noexcept
        {
            base::m_clear();
            base::m_init();
        }





        // INTERNAL IMPLEMENTATION FUNCTIONS
    protected:
        // Internal constructor functions

        // Called by range constructor
        // seems to be used only until c++11
        // seems to be kind a fix of some corner cases
        template<typename Integer>
        void m_initialize_dispatch(Integer n, Integer x, std::true_type)
        {
            m_fill_initialize(static_cast<size_type> (n), x);
        }

        // Called by range constructor
        template<typename Input_iterator>
        void m_initialize_dispatch(Input_iterator first, Input_iterator last, std::false_type)
        {
            for(; first != last; ++first)
            {
                // c++11
                emplace_back(*first);
                // if stdc++ < c++11 then push_back
            }
        }


        // O(N)
        // Called by list(n,v,a), and the range constructor when it turns out
        // to be the same thing.
        void m_fill_initialize(size_type n, const value_type& x)
        {
            for(; n; --n)
            {
                push_back(x);
            }
        }

        // if >= c++11
        // Called by list(n)
        void m_default_initialize(size_type n)
        {
            for(; n; --n)
            {
                emplace_back();
            }
        }

        // if >= c++11
        // Used to implement resize
        // default construct n consecutive elements at list's tail
        void m_default_append(size_type n); // in list.tcc



        // Internal assign functions follow.

        // Called by range assign
        // seems also to be used only until c++11
        template<typename Integer>
        void m_assign_dispatch(Integer n, Integer val, std::true_type)
        {
            m_fill_assign(n, val);
        }

        // Called by range assign
        // copies min(this.size(), other.size()) elements into container by calling Tp's copy ctor
        // and if this is shorter than other then append remaining elements
        template<typename Input_iterator>
        void m_assign_dispatch(Input_iterator first, Input_iterator last, std::false_type); // in list.tcc

        // Called by assigh(n, t) and the range assign when it turns out to be the same thing
        void m_fill_assign(size_type n, const value_type& val); // in list.tcc

        // Moves the elements from [first, last) before position
        void m_transfer(iterator position, iterator first, iterator last)
        {
            position.m_node->m_transfer(first.m_node, last.m_node);
        }

        // Inplace cinstructs new element before position with value given
        template<typename... Args>
        void m_insert(iterator position, Args&&... args)
        {
            node* new_node = m_create_node(std::forward<Args>(args)...);
            new_node->m_hook(position.m_node);
            this->m_inc_size(1);
        }

        // Erases element at posigion given
        void m_erase(iterator position) noexcept
        {
            this->m_dec_size(1);
            position.m_node->m_unhook();
            node* _node = static_cast<node*> (position.m_node);
            //if >= c++11
            node_alloc_traits::destroy(m_get_node_allocator(), _node->m_valptr());
            // if < c++11
            // Tp_alloc_type(m_get_node_allocator()).destroy(node->m_valptr());
            m_put_node(_node);
        }




        // To implement the splice (and merge)
        void m_check_equal_allocators(list& x) noexcept
        {
            if(gcc::alloc_not_equal<typename base::node_alloc_type>::_so_do_it(m_get_node_allocator(), x.m_get_node_allocator()))
            {
                // TODO: __builtin_abort();
                // force compile error;
            }
        }

        // Used to implement resize
        const_iterator m_resize_pos(size_type& new_size) const; // in list.tcc



        void m_move_assign(list&& other, std::true_type) noexcept
        {
           this->clear();
           this->m_move_nodes(std::move(other));
           alloc_on_move(this->m_get_node_allocator(), other.m_get_node_allocator());
        }

        void m_move_assign(list&& other, std::false_type)
        {
            if(other.m_get_node_allocator() == this->m_get_node_allocator())
            {
                m_move_assign(std::move(other), std::true_type());
            }
            else
            {
                // the rvalue's allocator cannot be moved or is not equal
                // so we need to individually move each element
                m_assign_dispatch(std::make_move_iterator(other.begin(), std::make_move_iterator(other.end()), std::false_type()));
            }
        }


    }; // list


}

#endif // GCC_STL_LIST_H











