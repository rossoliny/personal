#include <iostream>

using namespace std;



int main()
{
	long long f[21];
	f[0] = 1;
	for(int i = 1; i <= 20; i++)
	{
		f[i] = f[i-1] * i;
	}


	int n,m;

	while(cin >> n >> m)
	{
		cout << (f[n] + f[m]) << '\n';
	}
}
