#include <iostream>

using namespace std;


int main()
{
	int n;

	cin >> n;
	
	int phi[n + 1];

	for(int i = 0; i <= n; ++i)
	{
		phi[i] = i;
	}

	for(int i = 2; i <= n; ++i)
	{
		if(phi[i] == i)
		{
			for(int p = i; p <=n; p += i)
			{
				phi[p] -= phi[p] / i;
			}
		}
	}
	

	for(int i = 1; i <= n; i++)
	{
		cout << i << ' ';
	}
	cout << '\n';
	for(int i = 1; i <= n; ++i)
	{
		cout << phi[i] << ' ';
	}
	cout << '\n';

}
