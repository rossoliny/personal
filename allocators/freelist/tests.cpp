#define DEBUG

#include "freelist_allocator.h"
#include <cassert>
#include <cstdio>

using word_t = std::intptr_t;
using isa::freelist_allocator;

int main()
{
	isa::falloc a;

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

	isa::freelist_allocator a2;
	 
	a2.alloc(8);
	a2.alloc(8);
	a2.alloc(8);
	 
	auto o1 = a2.alloc(16);
	auto o2 = a2.alloc(16);
	 
	// must merge
	a2.free(o1);
	a2.free(o2);
	 
	// must split previously merged block.
	auto o3 = a2.alloc(16);
	 
	assert(o3 == o1); // reused
	assert(a2.search_start == a2.get_header(o2)); // search start set to last successfuly found block
	 
	auto o4 = a2.alloc(16);
	assert(o4 == o2); // reused

	isa::freelist_allocator a3;
	a3.alloc(8);

	auto z1 = a3.alloc(64);
	auto z2 = a3.alloc(16);
	a3.alloc(8);

	a3.free(z2);
	a3.free(z1); // 64 and 16 must merge into 104 

	auto z3 = a3.alloc(16);
	// split 104-byte block. new 16 byte block is taken from begining of 104 block.
	assert(a3.get_header(z3) == a3.get_header(z1)); 

	auto z4 = a3.alloc(16); // split 64-byte block z1
	assert((char*)a3.get_header(z4) == (char*) (z3 + 2)); // z4 block start right where z3 data ends;


	isa::freelist_allocator a4;
	
	a4.alloc(8);

	auto m1 = a4.alloc(64);
	auto m2 = a4.alloc(64);

	a4.free(m2);
	a4.free(m1);

	auto m3 = a4.alloc(104);
	assert(m3 == m1);

	auto m4 = a4.alloc(24);
	assert((char*)m4 == (char*)m3 + 104 - sizeof(word_t) + 56); // 56 is sizeof(block)

	std::puts("\nAll assertions passed!\n");
}
