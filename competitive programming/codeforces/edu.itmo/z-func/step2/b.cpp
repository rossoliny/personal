#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define pow(a, b) ((int) pow(a, b))
#define K 26
#define MAX_LEN 67108863

static char G[MAX_LEN];

static constexpr string_view c = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char** argv)
{
	G[0] = 'a';

	unsigned long long int i = 1;
	unsigned long long int len;

	while(i < K)
	{
		len = pow(2, i) - 1;
		G[len] = c[i % 26];
		memmove(G + len + 1, G, len);
		i++;
	};
		
	unsigned long long int t, k, j, z;
	cin >> t;

	while(t--)
	{
		cin >> k >> j;
		
		if(!j)
		{ 
			cout << "0\n";
			continue;
		};
		z = 0;
		
		len = pow(2, k) - 1;

		while(z + j < len && G[z + j] == G[z])
		{
			z++;
		};
		
		cout << z << '\n';
	};
	return 0;
};
