#include <iostream>

using namespace std;
int main()
{
	int t;
	cin >> t;


	while(t--)
	{
		int n;
		cin >> n;
		
		int index = 1;
		int to_print = n;
		int step = -1;

		while(index <= n)
		{
			if(to_print == index)
			{
				to_print = 1;
				step = 1;
			}

			cout << to_print << ' ';

			to_print += step;
			index++;
		}
		cout << '\n';
	}
}
