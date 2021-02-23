#include<iostream>

using namespace std;
#define long long long

#define N 100000
int a[N];
int t[4*N];

int gcd(int a, int b)
{
	int r;
	while(b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

void build(int v, int L, int R)
{
	if(L == R)
	{
		t[v] = a[L];
		return;
	}

	int M = (L + R) / 2;
	build(v*2 + 1, L, M);
	build(v*2 + 2, M+1, R);

	t[v] = gcd(t[v*2+1], t[v*2+2]);
}

void update(int v, int L, int R, int pos, int val)
{
	if(L == R)
	{
		t[v] = val;
		return;
	}

	int M = (L + R) / 2;
	if(pos <= M)
		update(v*2+1, L, M, pos, val);
	else
		update(v*2+2, M+1, R, pos, val);

	t[v] = gcd(t[v*2+1], t[v*2+2]);
}


int query(int v, int L, int R, int l, int r)
{
	if(L == l && R == r)
	{
		return t[v];
	}

	int M = (L+R)/2;
	if(r <= M)
		return query(v*2+1, L, M, l, r);
	if(l > M)
		return query(v*2+2, M+1, R, l, r);

	return gcd(query(v*2+1, L, M, l, M), query(v*2+2, M+1, R, M+1, r));
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
	build(0, 0, n-1);

	int k, q, l, r;
	cin >> k;
	while(k--)
	{
		cin >> q >> l >> r;
		if(q == 1)
		{
			cout << query(0, 0, n-1, l-1, r-1) << '\n';
		}
		else
		{
			update(0, 0, n-1, l-1, r);
		}
	}
}
