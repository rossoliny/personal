#include <iostream>
#include <stack>
using namespace std;


int main()
{

	int t;
	cin >> t;

	while(t--)
	{
		stack<char> L;
		string s;
		char l, r, ex;
		l = r = ex = 0;
		cin >> s;

		l = s[0];
		bool fail = false;
		for(int i = 0; i < s.length() ; i++)
		{
			if(s[i] != l && r == 0)
			{
				r = s[i];
			}

			if(s[i] == l)
			{
				L.push(l);
			}

			if(s[i] == r)
			{
				if(L.empty())
				{
					fail = true;
					break;
				}
				L.pop();
			}

			if(s[i] != l && s[i] != r && ex == 0) 
			{
				ex = s[i];

				if(L.empty())
				{
					for(int j = i; j < s.length(); j++)
					{
						if(s[j] == ex)
						{
							s[j] = l;
						}
					}
					L.push(s[i]);
				}
				else
				{
					for(int j = i; j < s.length(); j++)
					{
						if(s[j] == ex)
						{
							s[j] = r;
						}
					}
					L.pop();
				}
			}

		}	
		if(L.empty() && !fail)
		{
			cout << "YES\n";
		}
		else
		{
			cout << "NO\n";
		}
		
	}

}

