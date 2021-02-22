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

	build_st(t, arr, 2 * root + 1, L, M);
	build_st(t, arr, 2 * root + 2, M + 1, R);

	t[root] = t[root * 2 + 1] + t[root * 2 + 2];
}

long query_st(long* t, long pos, long L, long R, long l, long r)
{
	if(R == r && L == l)
	{
		return t[pos];
	}

	long M = (L + R) / 2;

	if(r <= M)
	{
		return query_st(t, pos*2 +1, L, M, l, r);
	}
	if(l > M)
	{
		return query_st(t, pos * 2 + 2, M+1, R, l, r);
	}

	return query_st(t, pos*2+1, L, M, l, M) + query_st(t, pos*2 + 2, M+1, R, M+1, r);
}

void update_st(long* t, long root, long L, long R, long pos, long val)
{
	if(L == R)
	{
		t[root] = val;
		return;
	}

	long M = (L + R) / 2;
	if(pos <= M)
	{
		update_st(t, root*2 +1, L, M, pos, val);
	}
	else
	{
		update_st(t, root*2 +2, M+1, R, pos, val);
	}

	t[root] = t[root * 2 + 1] + t[root * 2 + 2];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long n = 100000;
	long q = 100000;

	cin >> n >> q;
	long arr[n];
	long tre[4 * n];

	for(long i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	build_st(tre, arr, 0, 0, n-1);

	long l, r;
	char cmd;
	while(q--)
	{
		cin >> cmd >> l >> r;
		if(cmd == '=')
		{
			update_st(tre, 0, 0, n-1, l-1, r);
		}
		else
		{
			cout << query_st(tre, 0, 0, n-1, l-1, r-1) << '\n';
		}
	}

}
