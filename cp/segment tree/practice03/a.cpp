#include <iostream>
#include <map>

using namespace std;
#define N 100000

int a[N];
pair<int, int> t[4*N];

int _max(int l, int r)
{
	if(l >= r)
		return l;
	return r;
}

void build(int v, int L, int R)
{
	if(L == R)
	{
		t[v] = make_pair(a[L], a[L]);
		return;
	}
	int M = (L+R) / 2;
	build(2*v, L, M);
	build(2*v+1, M+1, R);

	t[v].first = t[2*v].first + t[2*v+1].first;
	t[v].second = _max(t[2*v].second, t[2*v+1].second);
}

void update(int v, int L, int R, int order)
{
	if(L == R)
	{
		if(t[v].second >= order)
		{
			t[v].first -= order;
			t[v].second -= order;
		}
		return;
	}

	int M = (R + L) / 2;
	if(t[v * 2].second >= order)
		update(2*v, L, M, order);
	else
		update(2*v+1, M+1, R, order);

	t[v].first = t[2*v].first + t[2*v+1].first;
	t[v].second = _max(t[2*v].second, t[2*v+1].second);
}

int main()
{
	int n;
	cin >> n;

	for(int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	build(1, 0, n-1);
	
	int k;
	cin >> k;
	int order;
	while(k--)
	{
		cin >> order;
		update(1, 0, n-1, order);
	}
	cout << t[1].first << '\n';
}
