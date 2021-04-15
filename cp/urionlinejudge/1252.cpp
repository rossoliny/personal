#include <iostream>
#include <algorithm>

using namespace std;
 
int N = -1;
int M = -1;

bool cmp(int const& a, int const& b)
{
	int aM = a % M;
	int bM = b % M;

	if(aM == bM)
	{
		if(a & 1)
		{
			// a is odd
			if(b & 1)
			{
				// both odd
				return a > b;
			}
			else
			{
				// a odd b even
				return true;
			}
		}
		else
		{
			if(b & 1)
			{
				// a even b odd
				return false;
			}
			else
			{
				// both even
				return a < b;
			}

		}
	}

	return aM < bM;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	while(1)
	{
		cin >> N >> M;
		if(!N && !M)
		{
			cout << 0 << ' ' << 0 << '\n';
			break;
		}

		static int buffer[10000];

		for(int i = 0; i < N; i++)
		{
			cin >> buffer[i];
		}
		std::sort(buffer, buffer + N, cmp);

		cout << N << ' ' << M << '\n';
		int i = 0;
		while(i < N)
		{
			cout << buffer[i++] << '\n';
		}
	}
 
    return 0;
}
