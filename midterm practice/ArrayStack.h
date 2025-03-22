/*
* 
Write the implementation for an ArrayStack class in which that items are of type int and
the maximum stack size is 100. 
Data members are an array values of type int, size 100 along with an int topIndex which should be - 1 for an empty stack 
and otherwise equal to the current size - 1.

Provide push, pop, top, isEmpty, isFull methods and a default Constructor.Upload ArrayStack.h and ArrayStack.cpp

*/
#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H


class ArrayStack {
	int stack[100];
	int topIndex;

public:
	ArrayStack();

	void push(int value);
	void pop();
	int top();
	bool isEmpty();
	bool isFull();

};

#endif // !ARRAYSTACK_H