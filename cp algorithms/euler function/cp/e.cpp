#include <iostream>
#include <string.h>

using namespace std;


int main()
{


	cout << "start\n";
	int n = 10000;

	long long phi[n+1];
	for(int i = 0; i <= n; ++i)
	{
		phi[i] = i;
	}

	long long H[n+1];
	memset(H, 0, n+1);

	for(int i = 2; i <= n; ++i)
	{
		if(phi[i] == i)
		{
			for(int j = i; j <= n; j += i)
			{
				phi[j] -= phi[j] / i;
			}
		}
	}

	/*
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j)
			{
				H[i-1] = H[i-1] + phi[i] * phi[j];
			}		
		}
	*/
	cout << "finish\n";

	int t;
	cin >> t;
	while(t--)
	{
		int x;
		cin >> x;
		int h = 0;
		for(int i = 1; i <= x; i++)
		{
			for(int j = 1; j <= x; j++)
			{
				h += phi[i] * phi[j];
			}
		}
		cout << h << '\n';
	}
}
