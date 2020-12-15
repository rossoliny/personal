#include <iostream>
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
		int a[n];

		for(int i = 0; i < n; i++)
		{
			cin >> a[i];
		}

		int b = 0, e = n - 1;
		int i = 0;
		while(i < n)
		{
			cout << a[b] << ' ';
			b++;
			i++;
		 	if(i < n) 
			{	
				cout << a[e] << ' ';
				e--;
				i++;
			}
		}
		cout<<'\n';
	}
}
