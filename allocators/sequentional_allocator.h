#include <unistd.h>
#include <cstdint>
#include <utility>


namespace isa
{
	// statefull allocator.
	// allocates memory by just bumping brk pointer
	// does not reuse freed memory
		
	class sequentional_allocator
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

	public:
		word_t* alloc(size_t n) noexcept
		{
			n = align(n);
			
			block* block = request_from_os(n);
			block->sz = n;
			block->used = true;

			if(heap_start == nullptr) // very first allocation
			{
				heap_start = block;
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

	using seq_alloc = sequentional_allocator;

}
