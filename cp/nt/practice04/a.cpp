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


		if(c == 0)
		{
			cout << a % M << '\n';
		}
		else if(b == 0)
		{
			cout << "1\n";
		}
		else if(a % M == 0)
		{
			cout << "0\n";
		}
		else
		{
			long long R = binpow(b, c, phiM);
			long long ans = binpow(a, R, M);
			cout << ans << '\n';
		}
		
	}


}
