#include <iostream>


using namespace std;
#define long long long


void build_st(long* t, long* arr, long root, long L, long R)
{
	if(L == R)
	{
		t[root] = arr[L];
		return;
	}

	long M = (L + R) / 2;
	build_st(t, arr, root * 2 + 1, L, M);
	build_st(t, arr, root * 2 + 2, M+1, R);

	t[root] = t[root * 2 + 1] + t[root * 2 + 2];
}

long query_st(long* t, long root, long L, long R, long l, long r)
{
	if(L == l && R == r)
	{
		return t[root];
	}

	long M = (R + L) / 2;
	if(r <= M)
	{
		return query_st(t, root * 2 + 1, L, M, l, r);
	}
	if(l > M)
	{
		return query_st(t, root * 2 + 2, M+1, R, l, r);
	}

	return query_st(t, root * 2 + 1, L, M, l, M) + query_st(t, root * 2 + 2, M + 1, R, M+1, r);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	long n = 100000;
	long arr[n];
	long tree[4 * n];
   	long q = 100000;
	long l, r;
	while(t--)
	{
		cin >> n >> q;
		for(long i = 0; i < n; i++)
		{
			cin >> arr[i];
		}

		build_st(tree, arr, 0, 0, n-1);

		while(q--)
		{
			cin >> l >> r;
			cout << query_st(tree, 0, 0, n-1, l, r) << '\n';
		}
		cout << '\n';
	}

	return 0;
}
