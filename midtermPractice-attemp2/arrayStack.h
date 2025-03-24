#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H


class ArrayStack {
public:

	int topIndex;
	int stack[100];

	ArrayStack();

	void push(int v);
	void pop();
	int top();
	bool isEmpty();
	bool isFull();

};

#endif