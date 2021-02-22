#include <iostream>

using namespace std;
#define ll long long

ll m;

ll binpow(ll a, ll n)
{
	ll res = 1;
	while(n > 0)
	{
		if(n & 1)
		{
			res = res * a % m;
			n--;
		}
		else
		{
			a = a * a % m;
			n /= 2;
		}
	}
	return res;
}

int main()
{
	int a, b;

	cin >> a >> b >> m;

//	ll x = binpow(b, m - 1);
	ll res = a * binpow(b, m - 2) % m;

	cout << res << '\n';
}
