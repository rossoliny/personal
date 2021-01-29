#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int a, b;

	while(1)
	{
		cin >> a >> b;
		if(!a && !b) break;

		int count = 0;
		int carr = 0;
		while(a > 0 || b > 0)
		{
			int diga = a % 10;
			int digb = b % 10;

			int newd = diga + digb + carr;
			if(newd > 9)
			{
				count++;
				carr = 1;
			}
			else
			{
				carr = 0;
			}

			a /= 10;
			b /= 10;
		}

		if(count == 1)
		{
			cout << count << " carry operation.\n";
		}
		else if(count)
		{
			cout << count << " carry operations.\n";
		}
		else
		{
			cout << "No carry operation.\n";
		}
	}	

}
