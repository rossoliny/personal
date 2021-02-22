


// SQRT(N)
int euler(int n)
{
	// with subtraction we can use int
	int res = n;

	for(int p = 2; p*p <= n; ++p)
	{
		if(n % p == 0)
		{
			while(n % p == 0) 
			{
				n /= p;
			}		
			// res = res * (p - 1) / p;
			// = (res * p - res) / p
			// = res - res / p;
			res -= res / p;
		}
	}

	if(n > 1)
	{
		res -= res / n;
	}
}

// N * LOG(LOG(N))
std::vector<int> eulers_in_range(int n)
{
	std::vector<int> res(n + 1);

	for(int i = 0; i <= n; ++i)
	{
		res[i] = i;
	}

	for(int i = 2; i <= n; ++i)
	{
		if(res[i] == i)
		{
			for(int j = i; j <= n; j += i)
			{
				res[j] -= res[j] / j;
			}
		}
	}

	//

}


int main()
{
	int n;
}
