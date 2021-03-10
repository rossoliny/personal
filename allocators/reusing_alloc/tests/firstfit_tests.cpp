#define DEBUG
#define FIRSTFIT
#include "../reusing_allocator.h"
#include <cassert>
#include <cstdio>

using word_t = std::intptr_t;

int main()
{
	isa::reusing_allocator a;

	auto p1 = a.alloc(3);
	auto p1b = a.get_header(p1);
	assert(p1b->sz == sizeof(word_t));

	auto p2 = a.alloc(8);
  	auto p2b = a.get_header(p2);
  	assert(p2b->sz == 8);

	a.free(p2);
	assert(p2b->used == false);

	auto p3 = a.alloc(8);
	auto p3b = a.get_header(p3);
	assert(p3b->sz == 8);
	assert(p3b == p2b);

	std::puts("\nAll assertions passed!\n");
}
