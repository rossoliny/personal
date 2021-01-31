#include <iostream>

using namespace std;

#define M (1000000007)
#define phiM (M-1)

long long binpow(long long a, long long n, long long m)
{
	long long r = 1;

	while(n > 0)
	{
		if(n & 1)
		{
			r = r * a % m;
			n --;
		}
		else
		{
			a = a * a % m;
			n /= 2;
		}
	}
	return r;
}

int main()
{
	long long a, b, c;

	while(1)
	{
		cin >> a >> b >> c;

		if(a == -1 && b == -1 && c == -1)
		{
			break;
		}

		switch(a)
		{
			case 2*M: 
			{
				// only case then gcd(a, M) != 1
				long long R = binpow(b, c, phiM);
	//			cout << "R: " << R << endl; 
				long long ans = -1;
				if(R == 1)
				{
					ans = a % M;
				}
				else if(R == 0)
				{
					ans = 1;
				}
				else
				{
					ans = binpow(a, R, M);
				}
				cout << ans << '\n';
				break;
			}
			default: 
			{
				// gcd(a, M) == ! is true
				long long R = binpow(b, c, phiM);
				long long ans = binpow(a, R, M);
				cout << ans << '\n';
			}
		}
		
	}


}
