#define DEBUG
#include "sequentional_allocator.h"
#include <cassert>
#include <cstdio>

using word_t = std::intptr_t;

int main()
{
	isa::seq_alloc sa;

	auto p1 = sa.alloc(3);
	auto p1b = sa.get_header(p1);
	assert(p1b->sz == sizeof(word_t));

	auto p2 = sa.alloc(8);
  	auto p2b = sa.get_header(p2);
  	assert(p2b->sz == 8);

	sa.free(p2);
	assert(p2b->used == false) ;
	std::puts("\nAll assertions passed!\n");
}
