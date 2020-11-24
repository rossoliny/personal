#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct mpair
{
	int pos;
};

int main()
{
	int t;
	cin >> t;

next_test:
	while(t--)
	{
		int n;
		cin >> n;

		vector<int> a(n+1);
		a[0] = -1;
		map<int, int> m;


		for(int i = 1; i < n + 1; i++)
		{
			cin >> a[i];
			
			m[a[i]] = i;
		}


		/*
		for(int i = 0; i < a.size(); i++)
		{
			cout << a[i] << ' ';
		}
		cout << endl;
		*/

		sort(a.begin(), a.end());

		
		int curr = a[0];


		int i = 1;
		while(i < n + 1)
		{
			if(curr != a[i])
			{
				curr = a[i];

				if(a[i] != a[i+1])
				{
					cout << m[a[i]] << "\n";
					goto next_test;
				}
			}
			i++;
		}

		cout << "-1\n";

	}
}	
