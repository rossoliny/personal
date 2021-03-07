#include <iostream>

using namespace std;


// find prefix sum <= s
int find(int* t, int root, int L, int R, int s)
{
	if(L==R)
	{
		return t[root] <= s;
	}

	if(t[root] <= s)
		return R - L + 1;

	int M = (L + R) / 2;
	if(t[root * 2] > s)
		return find(t, root * 2, L, M, s);

	return R - L + 1 + find(t, root * 2 + 1, M + 1, R, s - t[root * 2]);
}

// find first index i such that a[i] >= x
int find2(int* t, int root, int L, int R, int x)
{
	if(L == R)
	{
		if(a[L] >= x)
		{
			return L;
		}
		else
		{
			return -1;
		}
	}

	int M = (L + R) / 2;
	if(t[root * 2] >= x)
		return find_2(t, root * 2, L, M, x);

	return  find_2(t, root * 2 + 1, M + 1, R, x);

}

int main()
{
	//build
}
