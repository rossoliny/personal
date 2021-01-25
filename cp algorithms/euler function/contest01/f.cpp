#include <iostream>

using namespace std;

long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	const long long N = 200000;	

	long long phi[N + 1];

	for(long long i = 0; i <= N; ++i)
	{
		phi[i] = i;
	}
	for(long long i = 2; i <= N; ++i)
	{
		if(phi[i] == i)
		{
			for(long long j = i; j <= N; j += i)
			{
				phi[j] -= phi[j] / i;
			}
		}
	}
	phi[0] = 1;

	long long sum[N + 1];
	sum[0] = phi[0];

	for(long long i = 1; i <= N; ++i)
	{
		sum[i] = sum[i - 1] + phi[i];
	}

	long long k;
	while(1)
	{
		cin >> k;
		if(!k) break;

		if(k == 1)
		{
			cout << "0/1\n";
			continue;
		}

		// find denumenator by observing at least first k fractions
		long long d;
		for(long long i = 0; i <= N; ++i)
		{
			if(sum[i] >= k)
			{
				d = i;
				break;
			}
		}
		// total to check is sum[d] fractions. 
		// but first 'sum[d - 1]' fractions do not match. 
		// so we need to examine only sum[d] - sum[d-1] fractions.
		long long n = k - sum[d - 1]; 
		
		// now subtask is to find n-th irreduceble fraction with denumenator equal to d
		long long count = 0;
		for(long long i = 1; i <= d; ++i)
		{
			if(gcd(i, d) == 1)
			{
				++count;
				if(count == n)
				{
					cout << i << "/" << d << '\n';
				}
			}
		}
	}

}
