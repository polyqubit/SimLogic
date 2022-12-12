#pragma once
#include <iostream>
#include "Node.h"

template <class T>
class Stack
{
public:
	Stack()
	{
		top = nullptr;
	}
	Stack(T& t)
	{
		Node<T> temp(t);
		top = temp;
		++size;
	}
	void push_val(T& t)
	{
		Node<T> temp(t);
		temp.set_next(top);
		top = temp;
		++size;
	}
	T pop_val()
	{
		T temp = top->get_val();
		top = top->get_next();
		--size;
		return temp;
	}
	T peek_val()
	{
		return top->get_val();
	}
	void print()
	{
		if (!top)
		{
			return;
		}
		while (top->get_next)
		{
			//std::cout << top.ge
		}
	}
private:
	Node<T>* top;
	int size = 0;
};