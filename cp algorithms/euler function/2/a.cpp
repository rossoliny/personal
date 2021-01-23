#include <iostream>
#include <numeric>
using namespace std;


long long phi(long long n, long long* div)
{
	int res = n;
	*div = 1;

	for(int i = 2; i * i <= n; ++i)
	{
		if(n % i == 0)
		{
			int c = 0;
			while(n % i == 0)
			{
				n /= i;
				c++;
			}

			*div *= c+1;
			res -= res / i;
		}
	}

	if(n > 1)
	{
		res -= res/n;
		*div *= 1 + 1;
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
