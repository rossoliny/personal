#include "str.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	str s;
	cout << s << endl;

	s += 'i';
	s += 's';
	s += 'a';
	cout << s << endl;

	s = "iisaisaisaisaisaisaiasiasisaisaisaisaisaisaiasiasiisaisaisaisaisaisaiasiasi";
	cout << s << endl;

	return 0;
}
