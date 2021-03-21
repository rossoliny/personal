#include <iterator>
#include <cstddef>
#include <memory>

namespace isa
{

    template<typename T, typename Alloc = std::allocator<T>>
    class list
    {
        class list_iterator;
        class const_list_iterator;

		
        struct node_base
        {
            node* next;
            node* prev;

			void m_hook(node_base* pos)
			{

			}

			void m_unhook(node_base* pos)
			{

			}

			void m_transfer(node_base* pos)
			{

			}

			static void swap()
			{

			}

			void m_reverse()
			{

			}
        };


		struct node_header : public node_base
		{
		private:
			size_t m_size;

			inline bool m_empty()
			{
				return m_next == m_base();
			}

			m_init()
			{
				this->m_next = this->m_prev = this;
				this->m_size = 0;
			}

			node_base* m_base()
			{
				return this;
			}

		public:
			node_header() noexcept
			{
				m_init();
			}

			node_header(node_header&& rval) noexcept
				: node_base { rval.m_next, rval.m_prev }
				, m_size(rval.m_size)
			{
				if(rval.m_empty())
				{
					this->m_next = this->m_prev = this;
				}
				else
				{
					// prev -> this -> next
					this->m_prev->m_next = this->m_next->m_prev = this;
					rval.m_init();
				}

			}

			move_nodes(node_header&& rval) noexcept
			{
				if(rval.m_empty())
				{
					m_init();
				}
				else
				{
					this->m_next = rval.m_next;
					this->m_prev = rval.m_prev;

					this->m_prev->m_next = this->m_next->m_prev = this;
					this->m_size = rval.m_size;
					rval.m_init();
				}
			}
		};


		template<typename T>
		struct list_node : public node_base
		{
			T m_data;

			T* data_ptr()
			{
				std::addresof(m_data);
			}

			T const* data_ptr() const
			{
				std::addresof(m_data);
			}
		};

    public:
        using value_type = T;
        using allocator_type = Alloc;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = list_iterator;
        using const_iterator = const_list_iterator;
        using reverse_iterator = std::reverse_iterator<list_iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_list_iterator>;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;

    private:
        class list_iterator
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = list::difference_type;
            using value_type = list::value_type ;
            using pointer = list::pointer;
            using reference = list::reference;

            list_iterator(pointer ptr) : ptr(ptr)
            {
            }

            reference operator*() const
            {
                return *ptr;
            }

            pointer operator->()
            {
                return ptr;
            }

            list_iterator& operator--()
            {
                --ptr;
                return *this;
            }

            list_iterator& operator--(int)
            {
                list_iterator old = *this;
                --(*this);
                return old;
            }

            list_iterator& operator++()
            {
                ++ptr;
                return *this;
            }

            list_iterator& operator++(int)
            {
                list_iterator old = *this;
                ++(*this);
                return old;
            }

            friend bool operator==(const list_iterator& a, const list_iterator& b)
            {
                return a.ptr == b.ptr;
            }

            friend bool operator!=(const list_iterator& a, const list_iterator& b)
            {
                return !(a == b);
            }

        private:
            pointer ptr;
        };

        class const_list_iterator
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = list::difference_type;
            using value_type = list::value_type ;
            using pointer = list::pointer;
            using reference = list::reference;

            const_list_iterator(pointer ptr) : ptr(ptr)
            {	}

            // const reference == T& const. ref can not be const so it's meaningless
            const value_type& operator*() const
            {
                return *ptr;
            }

            const value_type& operator->() const
            {
                return ptr;
            }

            const_list_iterator& operator--()
            {
                --ptr;
                return *this;
            }

            const_list_iterator& operator--(int)
            {
                const_list_iterator old = *this;
                --(*this);
                return old;
            }

            const_list_iterator& operator++()
            {
                ++ptr;
                return *this;
            }

            const_list_iterator& operator++(int)
            {
                const_list_iterator old = *this;
                ++(*this);
                return old;
            }

            friend bool operator==(const const_list_iterator& a, const const_list_iterator& b)
            {
                return a.ptr == b.ptr;
            }

            friend bool operator!=(const const_list_iterator& a, const const_list_iterator& b)
            {
                return !(a == b);
            }

        private:
            const pointer ptr;
        };

    public:
        list_iterator begin() const
        {
            return list_iterator(head->content);
        }

        list_iterator end() const
        {
            return list_iterator(tail->content);
        }

        const_list_iterator cbegin() const
        {
            return const_list_iterator(head->content);
        }

        const_list_iterator cend() const
        {
            return const_list_iterator(tail->content);
        }

        std::reverse_iterator<list_iterator> rbegin() const
        {
            return std::make_reverse_iterator<list_iterator> (list_iterator(head->content));
        }

        std::reverse_iterator<list_iterator> rend() const
        {
            return std::make_reverse_iterator<list_iterator> (list_iterator(tail->content));
        }

        std::reverse_iterator<const_list_iterator> crbegin() const
        {
            return std::make_reverse_iterator<const_list_iterator> (const_list_iterator(head->content));
        }

        std::reverse_iterator<const_list_iterator> crend() const
        {
            return std::make_reverse_iterator<const_list_iterator> (const_list_iterator(tail->content));
        }



        // List
        list()
                : head(nullptr)
                , tail(nullptr)
        {

        }

        list_iterator insert(list_iterator& pos, value_type& val)
        {

        }


    private:
        node* head;
        node* tail;
    };

}
