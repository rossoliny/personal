#include <iostream>

using namespace std;

typedef long long ll;

ll binpow(ll a, ll n, ll m)
{
	if(n == 0) return 1;
	if(n & 1)
	{
		return (binpow(a, n - 1, m) * a ) % m;
	}
	else
	{
		return binpow(a * a % m, n/2, m);
	}
}


int main()
{
	int t;

	ll a, b, c, m;

	m = 1000000000 + 7;
	cin >> t;

	while(t--)
	{
		cin >> a >> b >> c;	

		ll rem = binpow(b, c, m - 1);
		ll res = binpow(a, rem, m);
		cout << res << '\n';
	}


}
