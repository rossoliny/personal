#include <iostream>
#include <string>
#include <cstring>
#include <map>

using namespace std;


#define ll long long

const ll MOD  = 1000000007;


ll binpow(ll a, ll n)
{
	ll res = 1;
	while(n > 0)
	{
		if(n & 1)
		{
			res = res * a % MOD;
			n--;
		}
		else
		{
			a = a * a % MOD;
			n /= 2;
		}
	}

	return res;
}


int main()
{
	const ll max_fac = 50 * 10;
	ll fac[max_fac + 1];
	fac[0] = 1;
	for(int i = 1; i <= max_fac; i++)
	{
		fac[i] = ((fac[i - 1] % MOD) * (i % MOD)) % MOD;
	}


	int t;
	cin>>t;
	
	char s[501];

	while(t--)
	{
		map<char, int> count;
		scanf("%s", s);
		
		for(char* ch = s; *ch;)
		{
			count[*ch] += 1;
			ch++;
		}

		unsigned ll num = 0;
		unsigned ll denum = 1;
		for(auto c : count)
		{
			num = (num + c.second) % MOD;
			denum = (denum % MOD) * (fac[c.second]) % MOD;
		}
		num = fac[num] ;
		//denum = fac[denum];

		ll inv = binpow(denum, MOD - 2) % MOD;
		ll res = (num % MOD) * (inv % MOD) % MOD;
		cout << res << '\n';
	}
}
