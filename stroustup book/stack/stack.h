#ifndef _STACK_H
#define _STACK_H

template<class T>
class Stack {
	T* v;
	int max_size;
	int top;
public:
	class Underflow{};
	class Overflow{};
	class Bad_size{};

	Stack(int s);
	~Stack();

	void push(T);
	T pop();
};

#include "stack.hpp"

#endif //_STACK_H