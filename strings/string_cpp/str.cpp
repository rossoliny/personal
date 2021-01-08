#include "str.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	str s("abcdrfghij");

	cout << s << '\n';

	s += 'k';
	s += 'l';
	s += 'm';
	s += 'n';

	cout << s << '\n';

	str s2 = "Hell";
	s2 += " and high water";
	cout << s2 << '\n';

	str s3 = "qwerty";
	s3 = s3;

	str s4 = "the quick brown dog jumped over the lazy dog";
	s4 = s4;

	cout << s3 << " " << s4 << "\n";
	cout << s + "." + s3 + str(".") + "Hosrsefeathers\n";

	str buf;

	while(cin >> buf && buf != "quit")
	{
		cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';
	}	



	return 0;
}
