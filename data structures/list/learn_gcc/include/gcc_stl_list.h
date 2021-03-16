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
#include <algorithm>

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

        // capacity funstions

        bool empty() const noexcept
        {
            return this->m_impl.m_node.m_next == &this->m_impl.m_node;
        }

        size_type size() const noexcept
        {
            return m_node_count();
        }

        //  Returns the size() of the largest possible list.
        size_type max_size() const noexcept
        {
            return node_alloc_traits::max_size(m_get_node_allocator());
        }

        /**
         *  This function will resize the list to the specified number
         *  of elements.  If the number is smaller than the list's
         *  current size the list is truncated, otherwise default
         *  constructed elements are appended.
         */
        void resize(size_type new_size); // in list.tcc

        /**
         *  This function will resize the list to the specified number
         *  of elements.  If the number is smaller than the list's
         *  current size the list is truncated, otherwise the list is
         *  extended and new elements are populated with given val by copy construction.
         */
        void resize(size_type new_size, const value_type& val); // in list.tcc



        // element access functions

        /**
         *  Returns a read/write reference to the data at the first
         *  element of the list.
         */
        reference front() noexcept
        {
            return *begin();
        }

        /**
         *  Returns a read-only (constant) reference to the data at the first
         *  element of the list.
         */
        const_reference front() const noexcept
        {
            return *begin();
        }

        /**
         *  Returns a read/write reference to the data at the last element
         *  of the list.
         */
        reference back() noexcept
        {
            iterator tmp = end();
            --tmp;
            return *tmp;
        }

        /**
         *  Returns a read-only (constant) reference to the data at the last
         *  element of the list.
         */
        const_reference back() const noexcept
        {
            const_iterator tmp = end();
            --tmp;
            return *tmp;
        }


        // modifiers functions

        /**
         *  This is a typical stack operation.  The function creates an
         *  element at the front of the list and assigns the given data
         *  to it.  Due to the nature of a list this operation can be
         *  done in constant time, and does not invalidate iterators and
         *  references.
         */
        void push_front(const value_type& val)
        {
            this->m_insert(begin(), val);
        }


        void push_front(value_type&& rval)
        {
            this->m_insert(begin(), std::move(rval));
        }

        template<typename... Args>
        void emplace_front(Args&&... args)
        {
            this->m_insert(begin(), std::forward<Args>(args)...);
        }


        /**
         *  This is a typical stack operation.  It shrinks the list by
         *  one.  Due to the nature of a list this operation can be done
         *  in constant time, and only invalidates iterators/references to
         *  the element being removed.
         *
         *  Note that no data is returned, and if the first element's data
         *  is needed, it should be retrieved before pop_front() is
         *  called.
         */
        void pop_front() noexcept
        {
            this->m_erase(begin());
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
         *  This function will insert an object of type T constructed
         *  with T(std::forward<Args>(args)...) before the specified
         *  location.  Due to the nature of a list this operation can
         *  be done in constant time, and does not invalidate iterators
         *  and references.
         */
        template<typename... Args> iterator emplace(const_iterator position, Args&&... args); // in list.tcc

        /**
         *  This function will insert a copy of the given value before
         *  the specified location.  Due to the nature of a list this
         *  operation can be done in constant time, and does not
         *  invalidate iterators and references.
         */
        iterator insert(const_iterator position, const value_type& val); // in list.tcc


        /**
         *  This function will insert a copy of the given rvalue before
         *  the specified location.  Due to the nature of a list this
         *  operation can be done in constant time, and does not
         *  invalidate iterators and references.
         */
        iterator insert(const_iterator position, value_type&& rval)
        {
            return emplace(position, std::move(rval));
        }

        /**
         *  This function will insert copies of the data in the
         *  std::initializer_list il into the list before the location
         *  specified by pos.
         *
         *  This operation is linear in the number of elements inserted and
         *  does not invalidate iterators and references.
         */
        iterator insert(const_iterator pos, std::initializer_list<value_type> il)
        {
            return this->insert(pos, il.begin(), il.end());
        }

        /**
         *  This function will insert a specified number of copies of the
         *  given data before the location specified by position.
         *
         *  This operation is linear in the number of elements inserted and
         *  does not invalidate iterators and references.
         */
        iterator insert(const_iterator pos, size_type n, const value_type& val); // in list.tcc

        /**
         *  This function will insert copies of the data in the range [first, last)
         *  into the list before the location specified by position.
         *
         *  This operation is linear in the number of elements inserted and
         *  does not invalidate iterators and references.
         */
        template<typename Input_iterator,
                typename = gcc::require_input_iter<Input_iterator>>
        iterator insert(const_iterator position, Input_iterator first, Input_iterator last); // in list.tcc


        /**
         *  This function will erase the element at the given position and thus
         *  shorten the list by one.
         *
         *  Due to the nature of a list this operation can be done in
         *  constant time, and only invalidates iterators/references to
         *  the element being removed.  The user is also cautioned that
         *  this function only erases the element, and that if the element
         *  is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
         iterator erase(const_iterator position) noexcept; // in list.tcc

        /**
         *  returns an iterator pointing to the element pointed to by last
         *  prior to erasing (or end()).
         *
         *  This function will erase the elements in the range
         *  [first, last) and shorten the list accordingly.
         *
         *  This operation is linear time in the size of the range and only
         *  invalidates iterators/references to the element being removed.
         *  The user is also cautioned that this function only erases the
         *  elements, and that if the elements themselves are pointers, the
         *  pointed-to memory is not touched in any way.  Managing the pointer
         *  is the user's responsibility.
         */
         iterator erase(const_iterator first, const_iterator last) noexcept
        {
             while(first != last)
             {
                 first = erase(first);
             }
             return last.m_const_cast();
        }

        /**
         *  This exchanges the elements between two lists in constant
         *  time.  Note that the global std::swap() function is
         *  specialized such that std::swap(l1,l2) will feed to this
         *  function.
         *
         *  Whether the allocators are swapped depends if the allocator traits return true_type as propagate_on_container_swap.
         */
        void swap(list& other) noexcept
        {
            detail::list_node_base::swap(this->m_impl.m_node, other.m_impl.m_node);

            size_t other_size = other.m_get_size();
            other.m_set_size(this->m_get_size());
            this->m_set_size(other_size);

            alloc_on_swap(this->m_get_Node_allocator(), other.m_get_Node_allocator());
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


        // list operations
        /**
         *  The elements of rval are inserted in constant time in front of
         *  the element referenced by position.  rval becomes an empty
         *  list.
         *
         *  Requires this != rval.
         */
        void splice(const_iterator position, list&& rval) noexcept
        {
            if (!rval.empty()) {
                m_check_equal_allocators(rval);

                this->m_transfer(position.m_const_cast(), rval.begin(), rval.end());

                this->m_inc_size(rval.m_get_size());
                rval.m_set_size(0);
            }
        }


        void splice(const_iterator position, list& other) noexcept
        {
            splice(position, std::move(other));
        }


        /**
         *  Removes the element in list rval referenced by rval_pos and
         *  inserts it into the current list before position.
         */
        void
        splice(const_iterator position, list&& rval, const_iterator element) noexcept
        {
            iterator it = element.m_const_cast();
            ++it;

            if (position == element || position == it)
            {
                return;
            }

            if (this != std::addressof(rval))
            {
                m_check_equal_allocators(rval);
            }

            this->m_transfer(position.m_const_cast(), element.m_const_cast(), it);

            this->m_inc_size(1);
            rval.m_dec_size(1);
        }

        /**
         *  Removes the element in list x referenced by i and
         *  inserts it into the current list before position.
         */
        void splice(const_iterator position, list& other, const_iterator element) noexcept
        {
            splice(position, std::move(other), element);
        }

        /**
         *  Removes elements from the range [first, last) and inserts them
         *  before position in constant time.
         *
         *  Undefined if position is in [first, last).
         */
        void splice(const_iterator position, list&& rval, const_iterator first, const_iterator last) noexcept
        {
            if (first != last) {
                if (this != std::addressof(rval))
                {
                    m_check_equal_allocators(rval);
                }

                size_t n = s_distance(first, last);
                this->m_inc_size(n);
                rval.m_dec_size(n);

                this->m_transfer(position.m_const_cast(), first.m_const_cast(), last.m_const_cast());
            }
        }


        /**
         *  Removes elements in the range [first, last) and inserts them
         *  before position in constant time.
         *
         *  Undefined if position is in [first, last).
         */
        void splice(const_iterator position, list& other, const_iterator first, const_iterator last) noexcept
        {
            splice(position, std::move(other), first, last);
        }

    private:
         //if c++11
         using remove_return_type = void;
         //if __cplusplus > 201703L then size_type
    public:
        /**
         *  Removes every element in the list equal to value.
         *  Remaining elements stay in list order.  Note that this
         *  function only erases the elements, and that if the elements
         *  themselves are pointers, the pointed-to memory is not
         *  touched in any way.  Managing the pointer is the user's
         *  responsibility.
         */
        remove_return_type remove(const Tp& value); // in list.tcc

        /**
         *  Removes every element in the list for which the predicate
         *  returns true.  Remaining elements stay in list order.  Note
         *  that this function only erases the elements, and that if the
         *  elements themselves are pointers, the pointed-to memory is
         *  not touched in any way.  Managing the pointer is the user's
         *  responsibility.
         */
        template<typename Predicate>
        remove_return_type remove_if(Predicate); // in list.tcc

        /**
         *  For each consecutive set of elements with the same value,
         *  remove all but the first one.  Remaining elements stay in
         *  list order.  Note that this function only erases the
         *  elements, and that if the elements themselves are pointers,
         *  the pointed-to memory is not touched in any way.  Managing
         *  the pointer is the user's responsibility.
         */
        remove_return_type unique(); // in list.tcc


        /**
         *  For each consecutive set of elements [first,last) that
         *  satisfy predicate(first,i) where i is an iterator in
         *  [first,last), remove all but the first one.  Remaining
         *  elements stay in list order.  Note that this function only
         *  erases the elements, and that if the elements themselves are
         *  pointers, the pointed-to memory is not touched in any way.
         *  Managing the pointer is the user's responsibility.
         */
        template<typename Binary_predicate>
        remove_return_type unique(Binary_predicate); // in list.tcc


        /**
         *  Assumes that both rval and this list are sorted according to
         *  operator<().  Merges elements of rval into this list in
         *  sorted order, leaving rval empty when complete.  Elements in
         *  this list precede elements in rval that are equal.
         */
        void merge(list&& rval); // in list.tcc

        void merge(list & other)
        {
            merge(std::move(other));
        }

        /**
         *  Assumes that both rval and this list are sorted according to
         *  Strict_weak_ordering_comparator.  Merges elements of rval into this list
         *  in sorted order, leaving rval empty when complete.  Elements
         *  in this list precede elements in rval that are equivalent
         *  according to Strict_weak_ordering_comparator().
         */
        template<typename Strict_weak_ordering_comparator>
        void merge(list&& rval, Strict_weak_ordering_comparator comp); // in list.tcc

        template<typename Strict_weak_ordering_comparator>
        void
        merge(list& other, Strict_weak_ordering_comparator comp)
        {
            merge(std::move(other), comp);
        }

        /**
         *  Reverse the order of elements in the list in linear time.
         */
        void reverse() noexcept
        {
            this->m_impl.m_node.m_reverse();
        }


        /**
         *  Sorts the elements of this list in O(N log(N)) time.  Equivalent
         *  elements remain in list order.
         */
        void sort(); // in list.tcc

        /**
         *  Sorts the elements of this list in NlogN time.  Equivalent
         *  elements remain in list order.
         */
        template<typename Strict_weak_ordering_comparator>
        void sort(Strict_weak_ordering_comparator); // in list.tcc








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

        // copy assigns val to all  elements in list
        // if n > list then inserts remaining elements at tail
        // if n < list then erases extra elements
        // Called by assigh(n, t) and the range assign when it turns out to be the same thing
        void m_fill_assign(size_type n, const value_type& val); // in list.tcc


        // O(1)
        // Moves the elements from [first, last) before position
        void m_transfer(iterator position, iterator first, iterator last)
        {
            position.m_node->m_transfer(first.m_node, last.m_node);
        }

        // Inplace constructs 1 new element before position with value given
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
            // destroy contained element
            node_alloc_traits::destroy(m_get_node_allocator(), _node->m_valptr());
            // if < c++11
            // Tp_alloc_type(m_get_node_allocator()).destroy(node->m_valptr());
            // deallocate node
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



        // clear list
        // m_impl.m_node->m_move_nodes
        // if possible then move assign allocator
        void m_move_assign(list&& rval, std::true_type) noexcept
        {
           this->clear();
           this->m_move_nodes(std::move(rval));
           // if pocma is present in allocator then move assigns rval's allocator
           alloc_on_move(this->m_get_node_allocator(), rval.m_get_node_allocator());
        }

        void m_move_assign(list&& rval, std::false_type)
        {
            if(rval.m_get_node_allocator() == this->m_get_node_allocator())
            {
                m_move_assign(std::move(rval), std::true_type());
            }
            else
            {
                // the rvalue's allocator cannot be moved or is not equal
                // so we need to individually move each element in linear time
                m_assign_dispatch(std::make_move_iterator(rval.begin(), std::make_move_iterator(rval.end()), std::false_type()));
            }
        }


    }; // list




    //

    /**
     *  This is an equivalence relation.  It is linear in the size of
     *  the lists.  Lists are considered equivalent if their sizes are
     *  equal, and if corresponding elements compare equal.
     */
    template<typename Tp, typename Alloc>
    inline bool operator==(const list<Tp, Alloc>& a, const list<Tp, Alloc>& b)
    {
        if (a.size() != b.size())
            return false;

        using const_iterator = typename list<Tp, Alloc>::const_iterator;
        const_iterator a_end = a.end();
        const_iterator b_end = b.end();

        const_iterator a_it = a.begin();
        const_iterator b_it = b.begin();
        while (a_it != a_end && b_it != b_end && *a_it == *b_it)
        {
            ++a_it;
            ++b_it;
        }

        return a_it == a_end && b_it == b_end;
    }


    /**
     *  This is a total ordering relation.  It is linear in the size of the
     *  lists.  The elements must be comparable with @c <.
     *
     *  See std::lexicographical_compare() for how the determination is made.
    */
    template<typename Tp, typename Alloc>
    inline bool operator<(const list<Tp, Alloc>& a, const list<Tp, Alloc>& b)
    {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    // Based on operator==
    template<typename Tp, typename Alloc>
    inline bool operator!=(const list<Tp, Alloc>& a, const list<Tp, Alloc>& b)
    {
        return !(a == b);
    }

    // Based on operator<
    template<typename Tp, typename Alloc>
    inline bool operator>(const list<Tp, Alloc>& a, const list<Tp, Alloc>& b)
    {
        return b < a;
    }

    /// Based on operator<
    template<typename Tp, typename Alloc>
    inline bool operator<=(const list<Tp, Alloc>& a, const list<Tp, Alloc>& b)
    {
        return !(b < a);
    }

    /// Based on operator<
    template<typename Tp, typename Alloc>
    inline bool operator>=(const list<Tp, Alloc>& a, const list<Tp, Alloc>& b)
    {
        return !(a < b);
    }


    /// See std::list::swap().
    template<typename Tp, typename Alloc>
    inline void swap(list<Tp, Alloc>& a, list<Tp, Alloc>& b) NOEXCEPT_IF(noexcept(a.swap(b)))
    {
        a.swap(b);
    }



    // Detect when distance is used to compute the size of the whole list.
    template<typename Tp>
    inline ptrdiff_t distance(gcc::list_iterator<Tp> first, gcc::list_iterator<Tp> last, std::input_iterator_tag tag)
    {
        using const_iter = gcc::list_const_iterator<Tp>;
        return std::distance(const_iter(first), const_iter(last), tag);
    }

    template<typename Tp>
    inline ptrdiff_t distance(gcc::list_const_iterator <Tp> first, gcc::list_const_iterator <Tp> last, std::input_iterator_tag tag)
    {
        using sentinel = detail::list_node_header;
        gcc::list_const_iterator<Tp> beyond = last;
        ++beyond;

        const bool whole = first == beyond;

        if (__builtin_constant_p (whole) && whole)
        {
            return static_cast<const sentinel*> (last.m_node)->m_size;
        }

        ptrdiff_t n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }
}

#endif // GCC_STL_LIST_H











