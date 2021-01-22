#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;



int main()
{
#define int __int128_t
	int64_t a, b, c, n;
	
	cin >> a >> b >> c >> n;

	int t1 = std::gcd(a, b);
	int64_t g = std::gcd(t1, c);

	int ans = n % 2 == 0 ? pow(g, n) : pow(g, n - 1);

	a /= g;
	b /= g;
	c /= g;
	
	int p = pow(10, 9) + 7;
	ans %= p;

	vector<int> primes;
	for(int64_t i = 0; i < n; i++)
	{
		int f = a * i * i + b * i + c;
		
		while(f % 2 == 0)
		{
			primes.push_back(2);
			f /= 2;
		}
		for(int64_t j = 3; j*j < f; j += 2)
		{
			while(f % j == 0)
			{
				primes.push_back(j);
				f /= j;
			}
		}
	}

	sort(primes.begin(), primes.end());

	for(int64_t i = 1; i < primes.size(); i++)
	{
		if(primes[i] == primes[i - 1])
		{
			ans *= primes[i] * primes[i];
			ans %= p;
			i++;
		}
	}
	uint64_t answer = ans;
	cout << answer << '\n';
}
