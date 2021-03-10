#include <unistd.h>
#include <cstdint>
#include <utility>
#include <list>

namespace isa
{
	class freelist_allocator
	{
		using word_t = std::intptr_t;

		struct block
		{
			block* next;
			block* prev;
			block* next_free;
			block* prev_free;
			size_t sz;
			bool used;
			word_t memory[1];
		};


		block* heap_head = nullptr;
		block* heap_tail = nullptr;
		block* free_head = nullptr;
		block* free_tail = nullptr;

	#ifdef DEBUG
	public:
	#endif
		block* search_start = nullptr;

		inline static block* get_header(word_t* memory) noexcept
		{
			return (block*) ( (char*)memory - sizeof(block) + sizeof(std::declval<block>().memory));
		}
	#ifdef DEBUG
	private:
	#endif

		inline static size_t align(size_t n) noexcept
		{
			return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
		}

		inline static size_t alloc_size(size_t n) noexcept
		{
			// block already contains 1 word inside it, so we allocate 1 block + n - word bytes;
			return sizeof(block) + n - sizeof(std::declval<block>().memory);
		}

		static block* request_from_os(size_t n) noexcept
		{
			block* blk = (block*) sbrk(0); // get current brk pointer position

			if(sbrk(alloc_size(n)) == (void*)-1) // (void*)-1 = maximum possible integer value of a pointer. this means out of memory
			{
				return nullptr;
			}
			return blk;
		}

		inline static bool can_split(block* blk, size_t n) noexcept
		{
			return (blk->sz) > alloc_size(n); 
		}

		static block* split(block* blk, size_t n) noexcept
		{
			if(can_split(blk, n))
			{
				block* new_blk = (block*)	((char*)blk + alloc_size(n));
				new_blk->sz = blk->sz - alloc_size(n);

				new_blk->next = blk->next;
				new_blk->next->prev = new_blk;
				blk->next = new_blk;
				new_blk->prev = blk;

				new_blk->next_free = blk->next_free;
				new_blk->next_free->prev_free = new_blk;
				blk->next_free = new_blk;
				new_blk->prev_free = blk;
			}

			blk->sz = n;

			return blk;
		}

		inline bool not_tail(block* blk) const noexcept
		{
			return blk != heap_tail;
		}

		inline bool not_head(block* blk) const noexcept
		{
			return blk != heap_head;
		}

		block* try_merge(block* blk) noexcept
		{
			block* next = blk->next;
			block* next_free = blk->next_free;
		
			if(not_head(blk) && !blk->prev->used)
			{
				blk = try_merge(blk->prev);
			}

			if(not_tail(blk) && !next->used)
			{
				remove_free_block(next);

				blk->sz += alloc_size(next->sz);
				blk->next = next->next;
				next->next->prev = blk;

				//add_free_block(blk);
			}

			return blk;
		}

		void remove_free_block(block* blk) noexcept
		{
			if(blk == free_tail && free_tail == free_head)
			{
				free_head = free_tail = nullptr;
				search_start = free_head;
			}
			else
			{
				blk->prev_free->next_free = blk->next_free;
				blk->next_free->prev_free = blk->prev_free;
				search_start = blk->next_free;
			}
			
			blk->used = true;
		}

		void add_free_block(block* blk) noexcept
		{
			if(free_head == nullptr)
			{
				free_head = blk;
				free_head->next_free = free_head->prev_free = blk;
				search_start = free_head;
			}
			else
			{
				free_tail->next_free = blk;
				blk->prev_free = free_tail;
			}
			free_tail = blk;
			free_tail->next_free = free_head;
			free_head->prev_free = free_tail;
			blk->used = false;
		}

		block* find_free_block(size_t n)
		{
			block* curr = search_start;

			if(curr == nullptr)
				return nullptr;

			do
			{
				if(curr->sz >= n)
				{
					block* res = split(curr, n);
					remove_free_block(res);
					return res;
				}
				curr = curr->next_free;
			} while(curr != free_head);

			return nullptr;
		}

	public:

		word_t* alloc(size_t n) noexcept
		{
			n = align(n);

			if(block* blk = find_free_block(n))
			{
				return blk->memory;
			}
			
			block* block = request_from_os(n);
			block->sz = n;
			block->used = true;

			if(heap_head == nullptr) // very first allocation
			{
				heap_head = block;
				heap_head->prev = heap_head->next = block;
			}
			if(heap_tail != nullptr) // any but not first
			{
				heap_tail->next = block;
				block->prev = heap_tail;
			}

			heap_tail = block;
			heap_tail->next = heap_head;
			heap_head->prev = heap_tail;

			// return pointer to memory allocated for user;
			return block->memory;
		}

		void free(word_t* memory) {
 			block* block = get_header(memory);
			block->used = false;
			add_free_block(block);
			try_merge(block);
		}
	};

	using falloc = freelist_allocator;

}
