#include <iostream>
#include "vector.h"
#include <vector>
#include <string>

using namespace std;

class object
{
	void* ptr = nullptr;
	size_t bytes = 0;

public:
	object() : ptr(nullptr), bytes(0)
	{
		cout << "default constructor(0, nullptr)\n";
	}

	object(size_t bytes) : bytes(bytes), ptr(::operator new(bytes))
	{ 
		cout << "constructor(" << "bytes = " << bytes << ")\n";
	}

	~object()
	{
		cout << "destructor(" << "bytes = " << bytes << ", ptr = " << ((intptr_t) ptr) << ")\n";
		if(ptr)
		{
			::operator delete(ptr, bytes);
		}
	}
	
	object(const object& other)
	{
		cout << "copy constructor(" << "other.bytes = " << other.bytes << ", other.ptr = " << ((intptr_t)other.ptr) << ")\n";
		if(bytes < other.bytes)
		{
			if(ptr)
			{
				::operator delete (ptr, bytes);
			}
			ptr = ::operator new(other.bytes);
		}

		int i;
		for(i = 0; i < other.bytes; ++i)
		{
			static_cast<char*> (ptr)[i] = static_cast<char*> (other.ptr)[i];
		}

		for(;i < bytes; ++i)
		{
			static_cast<char*> (ptr)[i] =  0;
		}

		bytes = other.bytes;
	}

	object(object&& other) : ptr(other.ptr), bytes(other.bytes)
	{
		cout << "move constructor(" << "other.bytes = " << other.bytes << ", other.ptr = " << ((intptr_t)other.ptr) << ")\n";
		other.ptr = nullptr;
		other.bytes = 0;
	}

	object& operator=(const object& other)
	{
		cout << "copy assignment(" << "other.bytes = " << other.bytes << ", other.ptr = " << ((intptr_t)other.ptr) << ")\n";
		//swap(*this, other);
		if(bytes < other.bytes)
		{
			if(ptr)
			{
				::operator delete(ptr, bytes);
			}
			ptr = ::operator new(other.bytes);
		}

		int i;
		for(i = 0; i < other.bytes; ++i)
		{
			static_cast<char*> (ptr)[i] = static_cast<char*> (other.ptr)[i];
		}

		for(;i < bytes; ++i)
		{
			static_cast<char*> (ptr)[i] = 0;
		}

		bytes = other.bytes;

		return *this;
	}

	object& operator=(object&& other)
	{
		cout << "move assignment(" << "other.bytes = " << other.bytes << ", other.ptr = " << ((intptr_t)other.ptr) << ")\n";
		if(ptr)
		{
			::operator delete(ptr, bytes);
		}

		ptr = other.ptr;
		bytes = other.bytes;

		other.ptr = nullptr;
		other.bytes = 0;

		return *this;
	}


	friend ostream& operator<<(ostream&, const object&);
};

ostream& operator<<(ostream& out, const object& o)
{
	out << "(" << o.bytes << ", " << reinterpret_cast<intptr_t> (o.ptr) << ")";
	return out;
}

template<typename T>
void print_vec(const vec<T>& v)
{
	cout << "vec:\n";
	for(int i = 0; i < v.size(); ++i)
	{
		cout << "\t" << v[i] << "\n";
	}
	cout << '\n';
	
}

int main(int argc, char** argv)
{
	vec<string> v;
	string isa = "isa";
	string* loh = new string("loh");

	v.push_back(isa);
	v.push_back("loh");
	v.pop_back();
	v.push_back(*loh);
	v.emplace_back("pidr");

	print_vec(v);
	
	return 0;
}
