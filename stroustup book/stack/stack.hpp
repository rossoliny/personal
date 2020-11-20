#ifndef _STACK_HPP
#define _STACK_HPP

#include "stack.h"

// template<class T>
Stack::Stack(int s) {
	top = 0;
	if(s > 10000) {
		throw Bad_size();
	}
	max_size = s;
	v = new T[s];
}

// template<class T>
Stack::~Stack() {
	delete[] v;
}

template<class T>
void Stack<T>::push(T t) {
	if(top == max_size) {
		throw Overflow();
	}
	v[top] = t;
	top++;
}
template<class T>
T Stack<T>::pop() {
	if(top == 0) {
		throw Underflow();
	}
	top--;
	return v[top];
}
#endif // _STACK_HPP