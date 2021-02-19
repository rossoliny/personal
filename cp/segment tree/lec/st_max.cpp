#include <iostream>

using namespace std;
#define long long long

const long ll_min = (unsigned long) -1/2 + 1;

long fmax(long a, long b)
{
	return a > b ? a : b;
}

void build_st(long* dst, long* src, long root, long l, long r)
{
	if(l == r)
	{
		dst[root] = l; // save index
		return;
	}

	long mid = (l + r) / 2;

	build_st(dst, src, root * 2 + 1, l, mid); // build left child
	build_st(dst, src, root * 2 + 2, mid + 1, r); // build right child

	long l_max = src[ dst[root * 2 + 1] ];
	long r_max = src[ dst[root * 2 + 2] ];
	dst[root] = l_max > r_max ? dst[root*2+1] : dst[root*2+2];
}

long max_st(long* stree, long* src, long curr, long L, long R, long l, long r)
{
	if(l <= L && r >= R) // node is fully nested
	{
		return stree[curr]; // index of max
	}

	if(l > R || r < L)
	{
		return -1;
	}

	long M = (L + R) / 2;

	long l_max_idx = max_st(stree, src, curr * 2 + 1, L, M, l, r);
	long r_max_idx = max_st(stree, src, curr * 2 + 2, M + 1, R, l, r);

	if(l_max_idx == -1) 
	{
		return r_max_idx;
	}
	if(r_max_idx == -1)
	{
		return l_max_idx;
	}

	return src[l_max_idx] > src[r_max_idx] ? l_max_idx : r_max_idx;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long N = 100000;
	long inp[N + 1];
	long segtree[4 * N];

	long max = ll_min;
//	cout << (unsigned long) -1/2 << endl;

	cin >> N;
	inp[N] = -1;
	for(size_t i = 0; i < N; ++i)
	{
		cin >> inp[i];
		max = inp[i] > max ? inp[i] : max;
	}

	segtree[0] = max;
	build_st(segtree, inp, 0, 0, N-1);

	long K, l, r, i;
	cin >> K;
	while(K--)
	{
		cin >> l >> r;
		long res = max_st(segtree, inp, 0, 0, N-1, l-1, r-1); 
		cout << inp[res] << ' ' << ++res << '\n';
	}
	
	return 0;
}











