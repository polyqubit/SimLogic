#pragma once
#include "Node.h"

template <class T>
class Stack
{
public:
	Stack(Node<T>&);
	void push_val(Node<T>&);
	T pop_val();
	T peek_val();
private:
	Node<T>* top;
	int size;
};