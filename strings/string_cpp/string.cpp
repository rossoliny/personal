#include "string.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	cout << "sizeof(isa::string): " << sizeof(isa::string) << endl;
	std::string string = "1234";
	cout << "sizeof(std::string): " << sizeof std::string << endl;


	cout << "sizeof(size_t): " << sizeof(size_t) << endl;
	cout << "sizeof(char*) " << sizeof(char*) << endl;
	cout << "sizeof(int) " << sizeof(int) << endl;

	isa::string s("abcdrfghij");

	cout << s << '\n';

	s += 'k';
	s += 'l';
	s += 'm';
	s += 'n';

	cout << s << '\n';

	isa::string s2 = "Hell";
	s2 += " and high water";
	cout << s2 << '\n';

	isa::string s3 = "qwerty";
	s3 = s3;

	isa::string s4 = "the quick brown dog jumped over the lazy dog";
	s4 = s4;

	cout << s3 << " " << s4 << "\n";
	cout << s + "." + s3 + isa::string(".") + "Hosrsefeathers\n";

	isa::string buf;

	while(cin >> buf && buf != "quit")
	{
		cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';
	}	

	return 0;
}
