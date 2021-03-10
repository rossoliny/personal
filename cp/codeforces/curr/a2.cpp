#include <iostream>

using namespace std;


int main()
{
	int t;
	cin >> t;


	while(t--)
	{
		string s;
		cin >> s;
		char l, r, x;
		l = r = x = 0;
		int lc, rc, xc;
		lc = rc = xc = 0;
		
		l = s[0];
		int m = 1;
		for(int i = 0; i < s.length(); ++i)
		{
			if(s[i] != l && r == 0)
			{
				r = s[i];
			}

			if(s[i] != l && s[i] != r && x == 0)
			{
				x = s[i];
				m = lc <= 0 ? 1 : -1;
			}

			lc += s[i] == l;
			lc -= s[i] == r;
			lc += (s[i] == x) * m;
		}
//		cout << lc << " == " << rc << endl;
		if(lc == 0)
			cout << "YES\n";
		else
			cout << "NO\n";

	}

}
