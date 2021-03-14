#include "list"


int main()
{
	gcc::list<int> l;

	gcc::list<int>::iterator i = l.end();
    gcc::list<int>::iterator i2 = l.begin();

    gcc::list<int>::const_iterator i3 = l.cend();
    gcc::list<int>::const_iterator i4 = l.cbegin();

    gcc::list<int>::reverse_iterator i5 = l.rend();
    gcc::list<int>::reverse_iterator i6 = l.rbegin();

    gcc::list<int>::const_reverse_iterator i7 = l.crend();
    gcc::list<int>::const_reverse_iterator i8 = l.crbegin();
}
