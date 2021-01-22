
#include <iostream>


using namespace std;

int main() 
{
	int n;

	while(1)
	{
		cin >> n;
		if(!n) break;

		int count = n;
		for(int p = 2; p*p <= n; ++p)
		{
			if(n % p == 0)
			{
				while(n % p == 0)
				{
					n /= p;
				}

				count -= count / p;
			}
		}

		if(n > 1)
		{
			count -= count / n;
		}

		cout << count << '\n';
	}


	return 0;
}
