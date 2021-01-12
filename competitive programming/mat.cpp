#include <iostream>
#include <vector>

using namespace std;




vector<vector<int>> getRes(const int A)
{
	int sz = A * 2 - 1;
	vector<vector<int>> m(sz);
	for(int i = 0; i < sz; ++i)
	{
		m[i].resize(sz);
	}
	
	for(int i = 0; i < sz; ++i)
	{
		int lim = A - i;
		int num = A;
		int step = 1;
		for(int j = 0; j < sz; ++j)
		{
			if(i <= sz/2)
			{
				if(num == lim)
				{
					step = -1;
					while(j < sz - i)
					{
						m[i][j] = lim;
						j++;
					}
					j--;;
				}
				else
				{
					m[i][j] = num;
				}
				num -= step;
			}
			else
			{
				m[i][j] = m[sz - i - 1][j];
			}
		}
	}

	return m;
}


int main(int argc, char** argv)
{
	vector<vector<int>> res = getRes(3);
	
	for(auto v : res)
	{
		for(auto num : v)
		{
			cout << num << ' ';
		}
		cout << '\n';
	}
}
