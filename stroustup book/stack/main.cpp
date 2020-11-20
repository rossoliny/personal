#include "stack.h"
#include <iostream>

int main () {
	using namespace std;
	Stack<int> s(10);
	s.push(10);
	
	cout << s.pop() << endl;

	Stack<float> ss(2);
	ss.push(10.4);
	cout << ss.pop() << endl;
	return 0;
}