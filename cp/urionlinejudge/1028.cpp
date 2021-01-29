#include <iostream>

using namespace std;



int gcd(int a, int b)
{
	int r;
	while(b > 0)
	{
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}


int main()
{
	int n, a, b;
	cin >> n;
	while(n--)
	{
		cin >> a >> b;
		cout << gcd(a, b) << '\n';
	}
}
