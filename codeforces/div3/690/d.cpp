#include <bits/stdc++.h>

using namespace std;


int main()
{
	int t;
	cin >> t;

	while(t--)
	{
		int n;
		cin >> n;

		int arr[n];
		int sum = 0;

		for(int i = 0; i < n; i++)
		{
			cin >> arr[i];
			sum += arr[i];
		}
		
		int b = true;
		int N = n;
		while(b)
		{
			if(n == 1)
			{
				cout << (N - n) << endl;
				b = false;
			}
			else if(sum % n == 0)
			{
				int goal = sum / n;
				
				int buf = 0;
				int counter = 0;
				for(int i = 0; i < N; i++)
				{
					if(buf == goal) 
					{
						counter++;
						buf = arr[i];
					}
					else if(buf < goal)
					{
						buf += arr[i];
					}
					else 
					{
						break;
					}
				}
				
				if(buf == goal)
				{
					counter++;
				}

				if(counter == n)
				{
					cout << (N - n) << endl;
					b = false;
				}
			}
			n--;
		}
	}

}
