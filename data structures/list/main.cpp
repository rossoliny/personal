#include "list.hpp"


int main()
{
	isa::list<int> l;

	l.end();
	l.begin();

	l.cend();
	l.cbegin();

	l.rend();
	l.rbegin();

	l.crend();
	l.crbegin();
}
