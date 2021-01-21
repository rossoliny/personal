#include <stdio.h>

struct pair 
{
	int a;
	int b;
};

int less(pair a, pair b)
{
	return (a.a * a.b) < (b.a * b.b);
}

void merge(pair* p, int l, int le, int r, int re)
{
        int lsz = le - l + 1;
        int rsz = re - r + 1;

        pair left[lsz];
        pair right[rsz];

        int il = 0, ir = 0;
        while(il < lsz)
        {
                left[il] = p[l + il];
                il++;
        }
        while(ir < rsz)
        {
                right[ir] = p[r + ir];
                ir++;
        }

        ir = 0;
        il = 0;
        while(il < lsz && ir < rsz)
        {
                if(less(left[il], right[ir]))
                {
                        p[l] = left[il];
                        il++;
                }
                else
                {
                        p[l] = right[ir];
                        ir++;
                }
                l++;
        }

        while(il < lsz)
        {
                p[l] = left[il];
                il++;
                l++;
        }
        while(ir < rsz)
        {
                p[l] = right[ir];
                ir++;
                l++;
        }

}

void msort(pair* p, int l, int r)
{
        if(l < r)
        {
                int m = l + (r - l) / 2;

                msort(p, l, m);
                msort(p, m+1, r);

                merge(p, l, m, m+1, r);
	}
}

pair max(pair first, pair second, bool a)
{
	if(a) 
	{
		if(first.a == second.a) 
		{
			if(first.b >= second.b)
			{
				return first;
			}
			else {
				return second;
			}
		}
		else if(first.a > second.a)
		{
			return first;
		}
		else 
		{
			return second;
		}
	}
	else 
	{
		if(first.b == second.b) 
		{
			if(first.a >= second.a)
			{
				return first;
			}
			else {
				return second;
			}
		}
		else if(first.b > second.b)
		{
			return first;
		}
		else 
		{
			return second;
		}
	}
}

int main(int argc, char** argv) 
{
	int n;
	scanf("%d", &n);

	pair a[n];
	pair maxA = { -1, -1 };
	pair maxB = { -1, -1 };
	int countA = 0;
	int countB = 0;
	
	int i = 0;
	while(i < n)
	{
		scanf("%d %d", &a[i].a, &a[i].b);
		if(a[i].a > a[i].b) 
		{
			int t = a[i].a;
			a[i].a = a[i].b;
			a[i].b = t;
		}
		maxA = max(maxA, a[i], true);
		maxB = max(maxB, a[i], false);

		i++;
	}

	i = 0;
	while(i < n)
	{
		if(a[i].a == maxA.a && a[i].b == maxA.b) {
			countA++;	
		}
		if(a[i].a == maxB.a && a[i].b == maxB.b) {
			countB++;	
		}
		i++;
	}


	i = 0;
	int count  = 0;
	pair prev = a[i];
	bool sequence = false;

	while(i < n)
	{
		if(i != 0 && a[i] == prev) 
		{
			sequense = true;
			l++;
		}
		else 
		{
			sequense = false;
			count += l != 0 ? l + 1 : 0;
			l = 0;
			prev = a[i];
		}
		// A
		if(! sequense) {
			if(a[i].a == maxA.a && a[i].b == maxA.b)
			{
				if(countA > 1)
				{
					count++;
				}
			}
			else if(a[i].a <= maxA.a && a[i].b <= maxA.b)
			{
				count++;
			}

			//B
			else if(a[i].a == maxB.a && a[i].b == maxB.b)
			{
				if(countB > 1)
				{
					count++;
				}
			}
			else if(a[i].a <= maxB.a && a[i].b <= maxB.b)
			{
				count++;
			}
		}

		i++;
	}

	printf("%d", count);

	return 0;
}
