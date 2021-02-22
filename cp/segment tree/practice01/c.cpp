#include <iostream>
#include <cstring>

using namespace std;
#define long long long

#define N 1000000
long n = N;
long q = 100000;

long a[N];
long t[4*N];

void st_build(long root, long L, long R)
{
	if(L == R)
	{
		t[root] = a[L];
		return;
	}

	long M = (L + R) / 2;

	st_build(root*2, L, M);
	st_build(root*2 + 1, M+1, R);

	t[root] = t[root*2] + t[root*2+1];
}

long st_query(long root, long L, long R, long l, long r)
{
	if(R==r && L==l)
	{
		return t[root];
	}

	long M = (L + R) / 2;

	if(r <= M)
		return st_query(root*2, L, M, l, r);
	if(l > M)
		return st_query(root*2+1, M+1, R, l, r);

	return st_query(root*2, L, M, l, M) + st_query(root*2+1, M+1, R, M+1, r);
}

void st_update(long root, long L, long R, long pos, long val)
{
	if(L == R)
	{
		t[root] = val;
		return;
	}

	long M = (L + R) / 2;
	if(pos <= M)
		st_update(root*2, L, M, pos, val);
	else
		st_update(root*2+1, M+1, R, pos, val);

	t[root] = t[root*2] + t[root*2+1];
}

int main()
{
	memset(a, 0, sizeof(a));
	cin >> n >> q;
	st_build(1, 0, n-1);
	
	char cmd;
	long l, r;
	while(q--)
	{
		cin >> cmd >> l >> r;
		if(cmd == 'A')
			st_update(1, 0, n-1, l-1, r);
		else
			cout << st_query(1, 0, n-1, l-1, r-1) << '\n';
	}	
}


