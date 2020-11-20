#include <iostream>



// problems with operation precedence
// cout << MAX(1, 2) will not compile
// #define MAX(a, b) a>b?a:b
// fixed
#define MAX(a, b) ((a)>(b)? (a) : (b))

// compile error
// preprocessor can not resolve recursive calls;
#define fac(a) ((a) * fac((a)-1))
int main () {
	using namespace std;
	int x = 1, y = 2;
	cout << 4 + MAX(x, y);
	cout << fac(5);
	return 0;
}
