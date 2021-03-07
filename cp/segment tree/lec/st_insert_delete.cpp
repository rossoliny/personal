#include <iostream>

// store sum
using namespace std;
#define N 1000000
int T[N * 4];

// insert -> update(0, 1, N-1, x, 1);
// delete -> update(0, 1, N-1, x, x);
//
void update(int root, int L, int R, int pos, int add)
{
	if(L == R)
		T[root] += add;

	int M = (L + R) / 2;
	if(pos <= M)
		update(root*2, L, M, pos, val);
	else
		update(root*2, M+1, R, pos, val);

	T[root] = T[root*2] + T[root*2+1];
}
// frequency -> query(0, 1, N-1, x, x);
