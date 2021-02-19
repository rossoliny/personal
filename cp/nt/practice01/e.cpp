#include <iostream>
#include <string.h>

using namespace std;


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	#define N 10000

	int phi[N+1];
	int sum[N+1];

	for(int i = 0; i <= N; ++i)
	{
		phi[i] = i;
	}

	for(int i = 2; i <= N; ++i)
	{
		if(phi[i] == i)
		{
			for(int j = i; j <= N; j += i)
			{
				phi[j] -= phi[j] / i;
			}
		}
	}

	sum[0] = 0;
	for(int i = 1; i <= N; ++i)
	{
		sum[i] = sum[i - 1] + phi[i];
	}

	int t, n;
	cin >> t;
	while(t--)
	{
		cin >> n;
		cout << ((long long)sum[n]) * sum[n] << '\n';
	}
}
