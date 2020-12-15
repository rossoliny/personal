#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() 
{
	int t;

	cin >> t;

	string s;
	while(t--)
	{
		cin >> s;
		int n = s.length();
		vector<string> sub;
		sub.resize((n * (n + 1)) / 2);
		int postfixes[n-1];

		int idx = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = i; j < n; j++)
			{
				sub[idx++] = (s.substr(i, j - i + 1));
			}

		}

		//cout << sub.size() << '\n';
		int postfixes;
		cout << "postfixes\n";
		for(int i = ; i < n-1; i++)
		{
			cout << "\t" << sub[i] << endl;
		}

	}
}
