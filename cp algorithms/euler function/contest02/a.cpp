#include <iostream>


using namespace std;

// if n = p1^s1 * p2^s2 * ... * pn^sn
// then divs = (s1 + 1) * (s2 + 1) * ... * (sn + 1)
int phi(int n, int& divs)
{
	int res = n;
	divs = 1;

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
			divs *= c + 1;
			res -= res / i;
		}
	}

	if(n > 1)
	{
		res -= res / n;
		divs *= 1 + 1;
	}
	return res;
}

int main()
{


	int n, d, ph;
	while(cin >> n)
	{
		ph = phi(n, d);
		cout << (n - ph - d + 1) << '\n';
	}
}

