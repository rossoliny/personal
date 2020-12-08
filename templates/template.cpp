#include <iostream>



class new_type
{

public:
	int value;

	new_type(int value) : value(value)
	{

	}

	bool operator>(new_type& other)
	{
		return value > other.value;
	}
};


template<class T>
T get_max(T a, T b)
{
	return (a > b ? a : b);
}


template<class T>
class some_container
{
	T element;
public:
	some_container(T t) : element(t) {};
	T  inc() { return ++element; }
};

template<>
class some_container<long>
{
	long element;
public:
	some_container(long e) : element(e) {};
	long dec() { return -- element; }
};

int main(int argc, char** argv)
{
	//new_type a(1), b(2);
	//std::cout << get_max(a, b).value << std::endl;

	some_container<int> sc(1);
	some_container<long> sc2(3);

	std::cout << sc.inc() << std::endl << sc2.dec() << std::endl;

	using namespace std;
	cout << "sizeof with int = " << sizeof(some_container<int>) << std::endl;
	cout << "sizeof with double = " << sizeof(some_container<double>) << std::endl;
	
}
