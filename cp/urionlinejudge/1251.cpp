#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;
 
#define C 300

bool cmp(pair<char,int> const& a, pair<char, int> const& b)
{
	if(a.second == b.second)
	{
		return a.first > b.first;
	}
	return a.second < b.second;
}

int main() {
 
	string text;
	text.resize(1001);

	pair<char, int> count[C];

	int t = 0;
	while(!cin.eof())
	{
		for(int i = 0; i < C; i++)
		{
			count[i].first = i;
			count[i].second = 0;
		}

		int len = 0;
		char ch;
		for(int i = 0; cin.get(ch); i++)
		{
			if(ch == '\n' || ch == '\r')
			{
				break;
			}
			text[i] = ch;
			len++;
			count[text[i]].second++;
		}

		if(!len)
		{
			continue;
		}

		sort(count, count + C, cmp);

		if(t)
		{
			cout << '\n';
		}

		for(int i = 0; i < C; i++)
		{
			if(count[i].second)
			{
				cout << int(count[i].first) << ' ' << count[i].second << '\n';
			}
		}

		t++;
	}
 
    return 0;
}
