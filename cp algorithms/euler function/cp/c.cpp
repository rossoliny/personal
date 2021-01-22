#include <iostream>

using namespace std;

int main()

{
	while(1)
	{
		int n;
		 cin >> n;
		 if(!n) 
			 break;

		 if(n == 1)
		 { 
			 cout << 0 << '\n';
			 continue;
		 }
		 int res = n;

		 for(int i = 2; i*i <= n; ++i)
		 {
			if(n % i ==0)
			{
				while(n % i == 0)
					n /= i;
				res -= res/i;
			}
		 }
		 if(n > 1)
			 res -= res/n;

		 cout << res << '\n';
	}
}
