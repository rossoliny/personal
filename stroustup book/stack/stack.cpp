#include "stack.h"

template<class T>
Stack<T>::Stack(int s) {
	top = 0;
	if(s > 10000) {
		throw Bad_size();
	}
	max_size = s;
	v = new char[s];
}

template<class T>
Stack<T>::~Stack() {
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