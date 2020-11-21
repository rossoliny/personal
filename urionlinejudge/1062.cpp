#include <deque>
#include <stack>
#include <iostream>

using namespace std;

bool rearrange(stack<int> line_a, int N)
{
	stack<int> station;
	// stack<int> line_b;

	int vagon;
	while(!line_a.empty())
	{
		vagon = line_a.top();
		line_a.pop();

		if(vagon == N)
		{
			// line_b.push(vagon;)
			N--;
			while(!station.empty() && station.top() == N)
			{
				// line_b.push(station.top());
				station.pop();
				N--;
			}
		}
		else 
		{
			station.push(vagon);
		}
	}

	while(!station.empty())
	{
		vagon = station.top();
		station.pop();

		if(vagon == N)
		{
			// line_b.push(vagon);
			N--;
		}
		else
		{
			return false;
		}
	}

	return true;
}


int main()
{
	int N;

	while(1)
	{
		scanf("%d", &N);
		if(!N) 
		{	
			break;
		}
		

		while(1)
		{
			int n;
			scanf("%d", &n);
			if(!n)
			{
				puts("");
				break;
			}

			stack<int> line_a;
			line_a.push(n);

			int i = 1;
			while(i < N)
			{
				scanf("%d", &n);
				line_a.push(n);
				i++;
			}

			if(rearrange(line_a, N))
			{
				puts("Yes");
			}
			else 
			{
				puts("No");
			}
		}
	}
}
