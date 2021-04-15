#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>

using namespace std;
 
#define MAXN 1000001
static int sorted[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	int t = 1;
	while(1)
	{
		cin >> n;
		if(!n)
		{
			break;
		}

		if(t!=1)
			cout << '\n';

		int min = (unsigned int) -1 / 2;
		int max = ((unsigned int) -1 / 2) + 1;

		int totalC = 0;
		int totalP = 0;
		int people;
	   	int consumption;
		for(int i = 0; i < n; i++)
		{
			cin >> people >> consumption;
			int r = (consumption) / people;
			sorted[r] += people;

			totalC += consumption;
			totalP += people;

			if(min > r)
				min = r;
			if(max < r)
				max = r;
		}

		cout << "Cidade# " << t << ":\n";
		for(int i = min; i <= max; i++)
		{
			if(sorted[i])
			{
				cout << sorted[i] << '-' << i;
				sorted[i] = 0;
				if(i != max)
					cout << ' ';
			}
		}

		float avg = (int((float(totalC) / totalP) * 100)) / 100.0;
		cout << fixed;
    	cout << setprecision(2);
		cout << "\nConsumo medio: " << avg << " m3.\n";

		t++;
	}
 
    return 0;
}
