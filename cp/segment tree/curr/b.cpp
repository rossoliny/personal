#include <iostream>

using namespace std;
#define N 1000001
#define long long long

long a[N];
long t[4*N];

void build(int v, int L, int R)
{
	if(L == R)
	{	
		t[v] = a[L];
		return;
	}

	int M = (L + R) / 2;
	build(2*v, L, M);
	build(2*v+1, M+1, R);

	t[v] = t[2*v] + t[2*v+1];
}

int find(int v, int L, int R, int s)
{
	if(L == R)
	{
		return t[v] <= s;
	}
	
	if(t[v] <= s)
		return R - L + 1;

	int M = (L + R) / 2;
	if(t[2*v] > s)
		return find(2*v, L, M, s);

	return M - L + 1 + find(2*v+1, M+1, R, s-t[2*v]);
}

void update(int v, int L, int R, int pos, int val)
{
	if(L == R)
	{
		t[v] = val;
		return;
	}
	int M = (L+R)/2;
	if(pos <= M)
		update(2*v, L, M, pos, val);
	else
		update(2*v+1, M+1, R, pos, val);

	t[v] = t[2*v] + t[2*v+1];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	build(1, 0, n-1);
	int q;
	cin >> q;
	int i, j, x;
	while(q--)
	{
		cin >> i;
		if(i == 1)
		{
			cin >> j;
			cout << find(1, 0, n-1, j) << '\n';
		}
		else
		{
			cin >> j >> x;
			update(1, 0, n-1, j-1, x);
		}
	}
}
