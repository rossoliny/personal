#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool myless(const string& a, const string& b)
{
	return a.size() > b.size();
}

int main(int argc, char** argv)
{
	int n;
	cin >> n;
	
	char ch;
	cin.get(ch);
	while(n--)
	{
		vector<string> v;

		string s;
		do
		{
			if(!cin.get(ch)) 
			{
				break;
			}
			if(ch == ' ' || ch == '\n')
			{
				v.push_back(s);
				s.clear();
				continue;
			}
			s += ch;
		} while(ch != '\n');

		stable_sort(v.begin(), v.end(), myless);


		for(int i = 0; i < v.size(); i++)
		{
			string str = v[i];
			if(i != v.size() - 1)
			{
				cout << str << ' ';
			}
			else 
			{
				cout << str << '\n';
			}
		}
	}
	return 0;
}
