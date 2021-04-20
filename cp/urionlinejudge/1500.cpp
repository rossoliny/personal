#include <iostream>
#include <string.h>
#include <algorithm>

#define int_t long long

struct node
{
	int_t add;
	int_t sum;
};

void push(node* t, int_t v, int_t L, int_t M, int_t R)
{
	if(t[v].add != 0)
	{
		t[2 * v + 1].add += t[v].add;
		t[2 * v + 1].sum += t[v].add * (M - L + 1);

		t[2 * v + 2].add += t[v].add;
		t[2 * v + 2].sum += t[v].add * (R - M);

		t[v].add = 0;
	}
}

int_t get_sum(node* t, int_t root, int_t L, int_t R, int_t l, int_t r)
{
	if(l == L && r == R)
	{
		return t[root].sum;
	}

	int_t M = (L + R) / 2;
	push(t, root, L, M, R);

	if(r <= M)
	{
		return get_sum(t, root*2+1, L, M, l, r);
	}
	if(l > M)
	{
		return get_sum(t, root*2+2, M+1, R, l, r);
	}

	return get_sum(t, root*2+1, L, M, l, M) + get_sum(t, root*2+2, M+1, R, M+1, r);
}

void add(node* t, int_t root, int_t L, int_t R, int_t l, int_t r, int_t val)
{
	if(l == L && r == R)
	{
		t[root].add += val;
		t[root].sum += (R - L + 1) * val;
		return;
	}

	int_t M = (L + R) / 2;

	push(t, root, L, M, R);

	if(r <= M)
	{
		add(t, 2 * root + 1, L, M, l, r, val);
	}
	else if(l > M)
	{
		add(t, 2 * root + 2, M+1, R, l, r, val);
	}
	else
	{
		add(t, 2 * root + 1, L, M, l, M, val);
		add(t, 2 * root + 2, M+1, R, M+1, r, val);
	}

	t[root].sum = t[2*root+1].sum + t[2*root+2].sum;
}

using namespace std;

#define N 100001

node tree[4 * N];

#undef int_t
int main()
{
#define int_t long long
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int_t t;
	cin >> t;

	while(t--)
	{
		int_t n, q;
		cin >> n >> q;
		memset(tree, 0, sizeof(tree));

		while(q--)
		{
			int_t cmd, l, r, v;
			cin >> cmd >> l >> r;

			l--; r--;
			if(l > r)
			{
				swap(l, r);
			}
			if(cmd == 1)
			{
				cout << get_sum(tree, 1, 0, n - 1, l, r) << '\n';
			}
			else
			{
				cin >> v;
				add(tree, 1, 0, n - 1, l, r, v);
			}
		}
	}
}
