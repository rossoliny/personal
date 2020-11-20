#include <iostream>

using namespace std;

int main(int c, char** v) {
	if(c > 1) {
		for(int i = 1; i < c; ++i) {
			cout << "Hello " << v[i] << "!\n";
		}
	} else {
		cout << "Hello world!\n";
	}
}
