#include <iostream>

using namespace std;
#define long long long

void build_st(long* st, long root, long* inp, long L, long R)
{
	if(L == R)
	{
		st[root] = inp[L];
		return;
	}

	long M = (L + R) / 2;

	build_st(st, root * 2 + 1, inp, L, M);
	build_st(st, root * 2 + 2, inp, M + 1, R);

	st[root] = st[root*2+1] + st[root*2+2];
}

long sum_st(long* st, long pos, long L, long R, long l, long r)
{
	if(L == l && R == r)
	{
		return st[pos];
	}
	
	long M = (L + R) / 2;
	if(r <= M)
	{
		return sum_st(st, pos * 2 + 1, L, M, l, r);
	}
	if(l > M)
	{
		return sum_st(st, pos * 2 + 2, M + 1, R, l, r);
	}
	
	return sum_st(st, pos*2+1, L, M, l, M) + sum_st(st, pos*2+2, M+1, R, M+1, r);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long N = 100000;
	cin >> N;
	long arr[N];
	long st[4*N];

	for(size_t i = 0; i < N; ++i)
	{
		cin >> arr[i];
	}

	build_st(st, 0, arr, 0, N-1);

	long K, l, r;
	cin >> K;
	while(K--)
	{
		cin >> l >> r;
		cout << sum_st(st, 0, 0, N-1, l, r) << ' ';
	}
	cout << '\n';
}
