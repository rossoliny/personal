#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string s;
	
	cin >> s;
	int z[s.size()];
	z[0] = 0;

	int i = 1;
	while(i < s.size())
	{
		z[i] = 0;
		while(z[i] + i < s.size() && s[z[i] + i] == s[z[i]])
		{
			z[i]++;
		}
		i++;
	}

	for(int i = 0; i < s.size(); i++)
	{
		cout << z[i] << ' ';
	}
	cout << endl;
	return 0;
}
