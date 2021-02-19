#include<iostream>

using namespace std;


int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long N = 100000;
	cin >> N;

	long long sum[N+1];
	sum[0] = 0;
	cin >> sum[1];

	long long num;
	for(long long i = 2; i < N+1; i++)
	{
		cin >> num;
		sum[i] = sum[i-1] + num;
	}
	
	long long K, l, r;
	cin >> K;
	while(K--)
	{
		cin >> l >> r;
		cout << (sum[r] - sum[l-1]) << ' ';
	}
	cout << '\n';

	return 0;
}
