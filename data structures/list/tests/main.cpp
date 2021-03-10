#include "../src/list.hpp"


int main()
{
	isa::list<int> l;

	isa::list<int>::iterator i = l.end();
    isa::list<int>::iterator i2 = l.begin();

    isa::list<int>::const_iterator i3 = l.cend();
    isa::list<int>::const_iterator i4 = l.cbegin();

    isa::list<int>::reverse_iterator i5 = l.rend();
    isa::list<int>::reverse_iterator i6 = l.rbegin();

    isa::list<int>::const_reverse_iterator i7 = l.crend();
    isa::list<int>::const_reverse_iterator i8 = l.crbegin();
}
