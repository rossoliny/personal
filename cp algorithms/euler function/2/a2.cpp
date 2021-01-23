#include <iostream>
#include <numeric>
using namespace std;


long long phi(long long n, long long* div)
{
	int res = n;
	*div = 1;

	for(long long i = 1; i * i <= n; ++i)
	{
		if(i!=1 && n % i == 0)
		{
			long long c = 0;
			while(n % i == 0)
			{
				n /= i;
				c++;
			}

			*div++;
			*div += i != n/i;

			res -= res / i;
		}
	}

	if(n > 1)
	{
		res -= res/n;
	}

	return res;
}

int main()
{

	long long n;
	while(cin >> n)
	{
		long long divs;
		long long ph = phi(n, &divs);

		cout << (n - ph - divs + 1) << '\n';

	}
}
