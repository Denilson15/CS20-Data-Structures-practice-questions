#include "arrayStack.h"


ArrayStack::ArrayStack() {
	topIndex = -1;
}

void ArrayStack::push(int v) {
	if (isFull()) return;
	topIndex++;
	stack[topIndex] = v;
}

void ArrayStack::pop() {
	if (isEmpty()) return;
	topIndex--;
}

int ArrayStack::top() {
	if (isEmpty()) return -1;
	return stack[topIndex];
}

bool ArrayStack::isEmpty() {
	if (topIndex == -1) return true;
	return false;
}

bool ArrayStack::isFull() {
	if (topIndex == 99) return true;
	return false;
}
