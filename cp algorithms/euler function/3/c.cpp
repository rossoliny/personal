#include <iostream>


using namespace std;


#define ll long long


ll binpow(ll a, ll n, ll m)
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
/*	
	ll N = 1000000;

	ll res[N + 1];
	for(int i = 1; i < n; i++)
	{
		res[i] = binpow(i, n - 2);
	}
*/

	ll n;

	cin >> n;
	
	ll ans[n];
	for(size_t i = 1; i < n; i++)
	{
		ans[i] = binpow(i, n - 2, n);
	}

	for(size_t i = 1; i < n; i++)
	{
		cout << ans[i] << ' ';
	}

	cout << '\n';
}
