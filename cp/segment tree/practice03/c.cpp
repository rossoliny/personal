#include <iostream>

using namespace std;
#define N 1000001
#define long long long
#define pair pair<long, long>

pair t[4*N];

pair combine(pair a, pair b)
{
	/*
	if(a.second > b.second || (a.second == b.second && a.first < b.first))
		return a;
	else
		return b;
	*/
	return a.second < b.second ? b : a;
}

void build(int v, int L, int R)
{
	if(L == R)
	{	
		t[v] = make_pair(L, 0);
		return;
	}

	int M = (L + R) / 2;
	build(2*v, L, M);
	build(2*v+1, M+1, R);

	t[v] = combine(t[2*v], t[2*v+1]);
}

void update(int v, int L, int R, int pos, int val)
{
	if(L == R)
	{
		t[v].second += val;
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

	build(1, 0, N-1);
	char cmd;
	int q, x;
	cin >> q;
	while(q--)
	{
		cin >> cmd >> x;
		if(cmd == '+')
			update(1, 0, N-1, x, 1);
		else
			update(1, 0, N-1, x, -1);
		cout << t[1].first << '\n';
	}
}
