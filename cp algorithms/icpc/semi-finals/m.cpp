#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#define umap unordered_map
#define uset unordered_set
using namespace std;

int main() {
	int n, count = 1;
	cin >> n;

	umap<int, int> studs;

	int i = 0;

	
	uset<int> shown;

	while(i < n)
	{
		int k;
		cin >> k;
		int ids[k];

		int to_show = n;

//		cout << "day " << (i+1) << endl;
		for(int j = 0; j < k; j++)
		{
			int id;
			cin >> id;
			ids[j] = id;

			// does not exist
			if(studs.find(id) == studs.end())
			{	
//				cout << id << " not exist\n";
//				cout << "to_show = " << n << endl;
				studs[id] = n;
				shown.insert(n);
				continue;
			}
			
			int last_saw = studs[id];
			
//			cout << id << " last saw = " << last_saw << endl;
		       		
			if(to_show >= last_saw)
			{
//				cout <<  to_show << " >= " << last_saw << endl; 
				to_show = last_saw - 1;
				//count++;
			}
			shown.insert(to_show);
//			cout << "to_show = " << to_show << endl;
			//cout << "count = " << count << endl;
		}

		for(int j = 0; j < k; j++)
		{
			studs[ids[j]] = to_show;
		}
//		cout << endl;
		i++;
	}
//	cout << count << '\n';
	cout << shown.size() << '\n';
}
