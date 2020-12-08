#include <vector>
#include <functional>
#include <stdlib.h>
#include <stdio.h>


template<typename Iterator_T, typename Key_T>
Iterator_T _find(Iterator_T begin, Iterator_T end, const Key_T& key)
{
	using I = Iterator_T;
	std::less_equal<Iterator_T> le{};
	std::equal_to<Iterator_T> eq{};
	std::less<Iterator_T> l{};
	std::plus<Iterator_T> add{};
	std::minus<Iterator_T> sub{};
	std::divides<Iterator_T> div{};

	Iterator_T mid, old_end;
	old_end = end;

	while(le(begin, end))
	{
		mid = add(div(sub(end, begin), 2), begin);

		if(eq(*mid, key))
		{
			return mid;
		}
		if((*mid, key))
		{
			begin = add(mid, 1);
		}
		else
		{
			end = sub(mid, 1); 
		}
	}

	return old_end;
}

int main() {

	int N = 100;
	std::vector<int> n(N);


	while(N--)
	{
		n[N] = rand();
	}

	int k = n[0];
	int kk = *_find(n.begin(), n.end(), k);

	printf("Searched for %d, found %d\n", k, kk);
}
