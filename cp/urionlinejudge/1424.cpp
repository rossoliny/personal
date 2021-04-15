#include <iostream>
#include <map>

using namespace std;



int main()
{
	int n, m;

	while(cin >> n >> m)
	{
		multimap<int, int> map;

		for(int i = 0; i < n; i++)
		{
			int num;
			cin >> num;
			map.insert(make_pair(num, i+1));
		}

		while(m--)
		{
			int k, v;
			cin >> k >> v;

			auto p = map.equal_range(v);
			auto start = p.first;
			auto end = p.second;

			int i = 1;
			while(i < k && start != end)
			{
				++start;
				++i;
			}
			if(start != end)
			{
				cout << start->second << '\n';
			}
			else
			{
				cout << 0 << '\n';
			}
		}
	}
}
