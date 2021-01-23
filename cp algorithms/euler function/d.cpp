#include <iostream>

using namespace std;


int main()
{

	int n = 1000000;
	int phi[n+1];

	for(int i = 0; i<=n; ++i)
	{
		phi[i] = i;
	}


	for(int i = 2; i <= n; ++i)
	{
		if(phi[i] == i)
		{
			for(int p = i; p <= n; p += i)
			{
				phi[p] -= phi[p] / i;
			}
		}
	}

	while(1)
	{
		int n;
		cin >> n;
		if(!n) break;

		long long sum = -1;
		for(int i = 0; i <= n; ++i)
		{
			sum += phi[i];
		}
		cout << (sum) << '\n';;
	}

}
