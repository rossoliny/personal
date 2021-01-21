#include <stdio.h>

//#define TEST


typedef struct 
{
	int s;
	int e;
} pair;

void read_pair(pair* p) 
{
	scanf("%d - %d", &(p->s), &(p->e));
}

int less(pair a, pair b) 
{
	if(a.s < b.s)
	{
		return 1;
	}
	else if(a.s > b.s) 
	{
		return 0;
	}

	if(a.e < b.e)
	{
		return 1;
	}
	else if(a.e > b.e)
	{
		return 0;
	}

	return 0;
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

void print_pair(pair p) 
{
	printf("[%d - %d]", p.s, p.e);
}

void print_arr(pair* p, int sz)
{
	int i = 0;
	while(i < sz)
	{
		print_pair(p[i]);
		printf(", ");
		i++;
	}
	puts("");
}

void testsort() 
{
	puts("SORT");
	int n;
	scanf("%d", &n);
	pair p[n];

	int i = 0;
	while(i < n)
	{
		read_pair(p + i);
		i++;
	}
	puts("Before sort: ");
	print_arr(p, n);

	msort(p, 0, n - 1);

	puts("After sort: ");
	print_arr(p, n);
}

void testless()
{
	puts("LESS");
	fflush(stdout);
	pair p, p2;
	read_pair(&p);
	read_pair(&p2);

	if(less(p, p2)) {
		print_pair(p);
		printf(" is less than \n");
		print_pair(p2);
	}
	else 
	{
		print_pair(p2);
		printf(" is less than \n");
		print_pair(p);
	}

}

int main(int argc, char** argv)
{
#ifdef TEST
	testless();
	testsort();
#else
	int n, intr = 0;
	scanf("%d", &n);

	pair ar[n];
	
	int i = 0;
	while(i < n) 
	{
		read_pair(ar + i);
		i++;
	}
	msort(ar, 0, n - 1);

	i = 0;
	while(i < n) 
	{
		if(i != 0 && ar[i - 1].e == ar[i].s)
		{
			intr++;
		}
		i++;
	}

	printf("%d\n", n - intr);
	i = 0;
	while(i < n)
	{
		if(i && less(ar[i - 1], ar[i])) {
			if(ar[i - 1].e != ar[i].s) 
			{
				printf("%d ", ar[i - 1].e);
			}
			printf("%d ", ar[i].s);
		}
		else if(!i) {
			printf("%d ", ar[i].s);
		}
		i++;
	}
	printf("%d\n", ar[n-1].e);

	
#endif
	return 0;
}
