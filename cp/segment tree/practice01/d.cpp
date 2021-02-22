#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;
#define long long long

#define N 131072 // 2^17
#define pair pair<int, int>

long a[N];
pair t[2*N];

pair combine(pair L, pair R)
{
	pair res;
	res.first = max(L.first, R.first);
	res.second= min(L.second, R.second);
	return res;
}

void build(long root, long L, long R)
{
	if(L == R)
	{
		t[root] = make_pair(a[L], a[L]);
		return;
	}

	long M = (L + R) / 2;

	build(root*2+1, L, M);
	build(root*2+2, M+1, R);

	t[root] = combine(t[root*2+1], t[root*2+2]);
}

pair query(long root, long L, long R, long l, long r)
{
	if(R == r && l == L)
	{
		return t[root];
	}
	long M = (L + R) / 2;
	if(r <= M)
	{
		return query(root * 2 + 1, L, M, l, r);
	}
	if(l > M)
	{
		return query(root * 2 + 2, M+1, R, l, r);
	}

	auto left = query(root * 2 + 1, L, M, l, M);
	auto right= query(root * 2 + 2, M+1, R, M+1, r);

	return combine(left, right);
}

void update(long root, long L, long R, long pos, long val)
{
	if(L == R)
	{
		t[root] = make_pair(val, val);
		return;
	}
	long M = (L + R) / 2;
	if(pos <= M)
		update(root*2+1, L, M, pos, val);
	else
		update(root*2+2, M+1, R, pos, val);

	t[root] = combine(t[root*2+1], t[root*2 + 2]);
}


void calc_sequence()
{
	for(long i = 1; i <= N; i++)
	{
		long f = i * i % 12345;
		long s = ((i * i) % 23456) * i % 23456;

		a[i] = (f + s);
	}
}

int main()
{
	calc_sequence();
	build(0, 0, N-1);
	long k;
	cin >> k;

	long i, j;
	while(k--)
	{
		cin >> i >> j;

		if(i >= 0)
		{
			auto res = query(0, 0, N-1, i, j);
			cout << (res.first - res.second) << '\n';
		}
		else
		{
			update(0, 0, N-1, -i, j);
		}
	}
}
