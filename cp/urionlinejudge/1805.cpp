#include <iostream>

using namespace std;

int main()

{
	unsigned long long a, b;

	cin >> a >> b;

	b++;
	unsigned long long res = (b*(b-1) / 2) - (a * (a-1) / 2);
	cout << res << '\n';
}
