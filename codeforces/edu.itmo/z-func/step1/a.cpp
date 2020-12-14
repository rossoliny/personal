#include <iostream>
#include <string>

using namespace std;

bool check(string::iterator i, string::iterator j)
{
	for(; i < j; i++, j--)
	{
		if(*i != * j)
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	int t;
	cin >> t;

	string s;
	while(t--)
	{
		cin >> s;
		
		for(auto i = s.end() - 1; i >= s.begin(); i--)
		{
			if(check(s.begin(), i))
			{
				cout << (i - s.begin()) + 1<< '\n';
				break;
			}
		}
		
	};
	return 0;
};
