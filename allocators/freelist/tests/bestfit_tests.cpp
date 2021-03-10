#define DEBUG
#define BESTFIT
#define SPLIT_ALLOC

#include "../freelist_allocator.h"
#include <cassert>
#include <cstdio>

using word_t = std::intptr_t;

int main()
{
	// general tests
	isa::freelist_allocator a;

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
	assert(p3b == p2b); // reused

	// nextfit specific
	isa::freelist_allocator a2;
	 
	a2.alloc(8);
	a2.alloc(8);
	a2.alloc(8);
	 
	auto o1 = a2.alloc(16);
	auto o2 = a2.alloc(16);
	 
	a2.free(o1);
	a2.free(o2);
	 
	auto o3 = a2.alloc(16);
	 
	assert(o1 == o3); // reused
	assert(a2.search_start == a2.get_header(o3)); // search start set to last successfuly found block
	 
	auto o4 = a2.alloc(16);
	assert(o4 == o2); // reused

	// bestfit specific
	isa::freelist_allocator a3;
	a3.alloc(8);

	auto z1 = a3.alloc(64);
	a3.alloc(8);
	auto z2 = a3.alloc(16);

	a3.free(z2);

	a3.free(z1);

	auto z3 = a3.alloc(16);
	auto z1b = a3.get_header(z1);
	assert((char*) a3.get_header(z3) == (char*)z1b + sizeof(*z1b) + z1b->sz - sizeof(*z1)); // split 64-byte block

	z3 = a3.alloc(16); // not enough mem to split, but z2 is free
	assert(a3.get_header(z3) == a3.get_header(z2));

	std::puts("\nAll assertions passed!\n");
}
