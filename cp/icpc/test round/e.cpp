#include <stdio.h>
#include <stdlib.h>

struct point 
{
	int x;
	int y;
};

int dx(point a, point b) 
{
	return (a.x - b.x);
}

int dy(point a, point b) 
{
	return (a.y - b.y);
}

int main(int argc, char** argv)
{
	int n;
	scanf("%d", &n);
	
	point p[n];

	int i = 0;
	while(i < n) 
	{
		scanf("%d %d", &p[i].x, &p[i].y);
		i++;
	}

	i = 0;
	int res;
	while(i < n - 3) 
	{
		point p1 = p[i];
		
		int j = i + 1;
		while(j < n - 2)
		{	
			point p2 = p[j];
			
			int k = j + 1;
			while(k < n - 1)
			{
				point p3 = p[k];

				int l = k + 1;
				while(l < n)
				{
					point p4 = p[l];

					if( 
						(dx(p1, p2) == dx(p3, p4) || dx(p1, p2) == -dx(p3, p4) ) &&  (dy(p1, p2) == dy(p3, p4) || dy(p1, p2) == -dy(p3, p4) ) ||
						(dx(p1, p3) == dx(p2, p4) || dx(p1, p3) == -dx(p2, p4) ) &&  (dy(p1, p3) == dy(p2, p4) || dy(p1, p3) == -dy(p2, p4) ) ||
 						(dx(p1, p4) == dx(p3, p2) || dx(p1, p4) == -dx(p3, p2) ) &&  (dy(p1, p4) == dy(p3, p2) || dy(p1, p4) == -dy(p3, p2) ) 
					)
					{
						res++;
					}

					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}

	printf("%d\n", res);

	return 0;
}
