#include <iterator>
#include <cstddef>

namespace isa
{

	template<typename T>
	class list
	{
		class node
		{
			friend class list;
			node* next;
			node* prev;
			T* content;
		};

	public:
		
		class iterator
		{
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = value_type*;
			using reference = value_type&;

			iterator(pointer ptr) : ptr(ptr)
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

			iterator& operator--()
			{
				--ptr;
				return *this;
			}

			iterator& operator--(int)
			{
				iterator old = *this;
				--(*this);
				return old;
			}

			iterator& operator++()
			{
				++ptr;
				return *this;
			}

			iterator& operator++(int)
			{
				iterator old = *this;
				++(*this);
				return old;
			}

			friend bool operator==(const iterator& a, const iterator& b) 
			{
				return a.ptr == b.ptr;
			}

			friend bool operator!=(const iterator& a, const iterator& b) 
			{
				return !(a == b);
			}

		private:
			pointer ptr;
		};

		class const_iterator
		{
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = value_type*;
			using reference = value_type&;

			const_iterator(pointer ptr) : ptr(ptr)
			{	}

			const reference operator*() const
			{
				return *ptr;
			}

			const pointer operator->() const
			{
				return ptr;
			}

			const_iterator& operator--() 
			{
				--ptr;
				return *this;
			}

			const_iterator& operator--(int)
			{
				const_iterator old = *this;
				--(*this);
				return old;
			}

			const_iterator& operator++() 
			{
				++ptr;
				return *this;
			}

			const_iterator& operator++(int)
			{
				const_iterator old = *this;
				++(*this);
				return old;
			}

			friend bool operator==(const const_iterator& a, const const_iterator& b) 
			{
				return a.ptr == b.ptr;
			}

			friend bool operator!=(const const_iterator& a, const const_iterator& b) 
			{
				return !(a == b);
			}

		private:
			const pointer ptr;
		};


		iterator begin() const 
		{
			return iterator(head->content);
		}

		iterator end() const 
		{
			return iterator(tail->content);
		}

		const_iterator cbegin() const 
		{
			return const_iterator(head->content);
		}

		const_iterator cend() const 
		{
			return const_iterator(tail->content);
		}

		std::reverse_iterator<iterator> rbegin() const
		{
			return std::make_reverse_iterator<iterator> (iterator(head->content));
		}

		std::reverse_iterator<iterator> rend() const
		{
			return std::make_reverse_iterator<iterator> (iterator(tail->content));
		}

		std::reverse_iterator<const_iterator> crbegin() const
		{
			return std::make_reverse_iterator<const_iterator> (const_iterator(head->content));
		}

		std::reverse_iterator<const_iterator> crend() const
		{
			return std::make_reverse_iterator<const_iterator> (const_iterator(tail->content));
		}

		list() 
			: head(nullptr)
			, tail(nullptr)
		{

		}


	private:
		node* head;
		node* tail;
	};

}
