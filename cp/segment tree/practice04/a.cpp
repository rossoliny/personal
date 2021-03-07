#include <iostream>
#include <cstring>

using namespace std;
#define N 1000001
#define long long long
#define pair pair<long, long>

int a[N];
int t[4*N];

int combine(int a, int b)
{
	return a + b;
}

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

	t[v] = combine(t[2*v], t[2*v+1]);
}

int query(int v, int L, int R, int l, int r)
{
	if(L == l && R == r)
	{
		return t[v];
	}
	int M = (L+R)/2;
	if(r <= M)
		return query(2*v, L, M, l, r);
	if(l > M)
		return query(2*v+1, M+1, R, l, r);
	
	return combine(query(2*v, L, M, l, M), query(2*v+1, M+1, R, M+1, r));
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

	t[v] = combine(t[2*v], t[2*v+1]);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int q, n, x;
	cin>>q;
	while(q--)
	{
		memset(t, 0, sizeof(t));
		cin>>n;
		long inv = 0;
		for(int i = 0; i < n; ++i)
		{
			cin >> x;
			
			if(x <= N-1)
			{
				inv += query(1, 0, N-1, 0, x);
			}
			update(1, 0, N-1, x-1, 1);
		}
		cout << inv << '\n';
		cout << t[1] << '\n';
	}
}
