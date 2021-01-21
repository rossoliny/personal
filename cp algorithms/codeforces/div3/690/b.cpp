#include <bits/stdc++.h>

using namespace std;


int main() 


{
	int t;
	cin >> t;

	string s;
	string ans;
	while(t--)
	{
		int n; 
		cin >> n;

		cin >> s;
		ans = "NO";
		if(n == 4)
		{
			ans = s == "2020" ? "YES" : "NO";
		}
		else {	
			// 2020...
			if(s[0] == '2' && s[1] == '0' &&  s[2] == '2' &&  s[3] == '0')
			{
				ans = "YES";
			}
			//...2020
			else if(s[n-4] == '2' && s[n-3] == '0' && s[n-2] == '2' && s[n-1] == '0')
			{
				ans = "YES";
			}
			// 20...20
			else if(s[0] == '2' && s[1] == '0' && s[n-2] == '2' && s[n-1] == '0' )
			{
				ans = "YES";
			}
			// 2...020
			else if(s[0] == '2' && s[n-3] == '0' && s[n-2] == '2' && s[n-1] == '0')
			{
				ans = "YES";
			}
			// 202..0
			else if(s[0] == '2' && s[1] == '0' && s[2] == '2' && s[n-1] == '0')
			{
				ans = "YES";
			}
		}

		cout << ans << '\n';
	}
}
