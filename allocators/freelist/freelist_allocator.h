#include <unistd.h>
#include <cstdint>
#include <utility>


namespace isa
{
	class freelist_allocator
	{
		using word_t = std::intptr_t;

		struct block
		{
			bool used;
			size_t sz;
			block* next;
			word_t data[1];
		};

		block* heap_start = nullptr;
		block* top = heap_start;

		#if defined(NEXTFIT) || defined(BESTFIT)
		#ifdef DEBUG
		public:
		#else
		private:
		#endif
		block* search_start = nullptr;
		#endif

		inline size_t align(size_t n) const noexcept
		{
			return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
		}

		inline size_t alloc_size(size_t n) const noexcept
		{
			// block already contains 1 word inside it, so we allocate 1 block + n - word bytes;
			return sizeof(block) + n - sizeof(std::declval<block>().data);
		}

		block* request_from_os(size_t n) const noexcept
		{
			block* block = (struct block*) sbrk(0); // get current brk pointer position

			if(sbrk(alloc_size(n)) == (void*)-1) // (void*)-1 = maximum possible integer value of a pointer. this means out of memory
			{
				return nullptr;
			}
			return block;
		}

		void init()
		{

			reset_heap();
		}

		void reset_heap() noexcept
		{
			if(heap_start == nullptr)
				return;

			brk(heap_start);
			heap_start = nullptr;
			top = nullptr;
			search_start = nullptr;
		}

	#ifdef SPLIT_ALLOC
		block* split(block* blk, size_t n)
		{
			blk->sz -= alloc_size(n);
			block* new_blk = (block*)	((char*)blk + sizeof(block) + blk->sz - sizeof(word_t));
			new_blk->next = blk->next;
			blk->next = new_blk;

			return new_blk;
		}

		inline bool can_split(block* blk, size_t n) const noexcept
		{
			// n and sz are already alligned
			return (blk->sz) > alloc_size(n); 
		}

		block* split_alloc(block* blk, size_t n) 
		{
			if(can_split(blk, n))
			{
				blk = split(blk, n);
			}

			blk->used = true;
			blk->sz = n;

			return blk;
		}
	#endif

	#ifdef DEBUG
	public:
	#endif
		inline block* get_header(word_t* data) const noexcept
		{
			//return (block*) ( (char*)data - sizeof(block) + sizeof(data));
			return (block*) ( (char*)data - sizeof(block) + sizeof(std::declval<block>().data));
		}
	#ifdef DEBUG
	private:
	#endif

		block* firstfit_search(size_t n)
		{
			block* curr = heap_start;

			while(curr != nullptr)
			{
				if(!curr->used && curr->sz >= n)
				{
					return curr;
				}
				curr = curr->next;
			}

			return nullptr;
		}

		#ifdef NEXTFIT
		block* nextfit_search(size_t n)
		{
			block* curr = search_start;

			if(curr == nullptr)
				return nullptr;

			do
			{
				if(!curr->used && curr->sz >= n)
				{
					search_start = curr;
					return curr;
				}
				curr = curr->next;
				if(curr == nullptr)
					curr = heap_start;
			} while(curr != search_start);

			return nullptr;
		}
		#endif

		#ifdef BESTFIT 
		block* bestfit_search(size_t n)
		{
			block* curr = search_start;

			if(curr == nullptr)
				return nullptr;

			do
			{
				if(!curr->used && curr->sz >= n)
				{
				#ifdef SPLIT_ALLOC
					block* res = split_alloc(curr, n);
					search_start = res;
					return res;
				#else
					if(curr->sz == n)
					{
						break;
					}
				#endif
				}
				curr = curr->next;
				if(curr == nullptr)
					curr = heap_start;
			} while(curr != search_start);

			#ifndef SPLIT_ALLOC
			search_start = curr ? curr : search_start;
			return curr;
			#else
			return nullptr;
			#endif
		}
		#endif

		block* find_block(size_t n)
		{
		#ifdef FIRSTFIT
			return firstfit_search(n);
		#elif defined(NEXTFIT)
			return nextfit_search(n);
		#elif defined(BESTFIT)
			return bestfit_search(n);
		#else
			return nullptr;
		#endif
		}

	public:

		freelist_allocator() 
		{
			init();
		}

		word_t* alloc(size_t n) noexcept
		{
			n = align(n);

			if(block* blk = find_block(n))
			{
				return blk->data;
			}
			
			block* block = request_from_os(n);
			block->sz = n;
			block->used = true;

			if(heap_start == nullptr) // very first allocation
			{
				heap_start = block;
				search_start = heap_start;
			}

			if(top != nullptr) // any but not first allocation
			{
				top->next = block;
			}

			// last allocated block is head.
			top = block;

			// return pointer to memory allocated for user;
			return block->data;
		}

		void free(word_t* data) {
 			block* block = get_header(data);
 		 	block->used = false;
		}
	};

	using falloc = freelist_allocator;

}
