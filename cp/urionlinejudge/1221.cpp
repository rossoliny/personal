#include <iostream>

using namespace std;




int main()
{
	int t, n;
	cin >> t;


	while(t--)
	{
		cin >> n;

		bool p = true;
		for(int i = 2; i * i <= n; i++)
		{
			if(n % i == 0)
			{
				p = false;
				break;	
			}
		}
		
		cout << (p ? "" : "Not ") << "Prime\n";
	}

}
