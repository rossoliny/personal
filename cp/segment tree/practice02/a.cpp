#include <iostream>
#include <cmath>

using namespace std;

#define N 100000
int n = N;
int k = N;

int a[N];
int t[4*N];

int combine(int a, int b)
{
	if(a == 0 || b == 0)
		return 0;

	if(a < 0 ^ b < 0)
		return -1;
	return 1;
}

void build(int root, int L, int R)
{
	if(L == R)
	{
		t[root] = a[L];
		return;
	}

	int M = (L+R)/2;
	build(2*root, L, M);
	build(2*root+1, M+1, R);

	int prod = combine(t[root*2], t[root*2+1]);
	t[root] = prod;
}

int query(int root, int L, int R, int l, int r)
{
	if(l == L && r == R)
	{
		return t[root];
	}

	int M = (L+R)/2;
	if(r <= M)
		return query(2*root, L, M, l, r);
	if(l > M)
		return query(2*root+1, M+1, R, l, r);

	int prod = combine(query(2*root, L, M, l, M), query(2*root+1, M+1, R, M+1, r));
	return prod;
}

void update(int root, int L, int R, int pos, int val)
{
	if(L==R) {
		t[root] = val;
		return;
	}
	int M=(L+R)/2;
	if(pos <= M)
		update(root*2, L, M, pos, val);
	else
		update(root*2+1, M+1, R, pos, val);

	int prod = combine(t[root*2], t[root*2+1]);
	t[root] = prod;
}

inline char res(int p)
{
	if(p == 0)
		return '0';
	return p < 0 ? '-' : '+';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	char cmd;
	int i, j;
	while(cin >> n >> k) {

		for(int i = 0; i < n; ++i)
		{
			cin >> a[i];
		}

		build(1, 0, n-1);

		while(k--)
		{
			cin >> cmd;
			cin >> i >> j;
			if(cmd == 'P')
			{
				cout << res(query(1, 0, n-1, i-1, j-1));
			}
			else
			{
				update(1, 0, n-1, i-1, j);
			}
		}
		cout << '\n';
	}
}
