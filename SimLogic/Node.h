#pragma once

template <class T>
class Node
{
public:
	Node(T& t)
	{
		val = t;
	}
	void set_next(Node& t)
	{
		next = t;
	}
	Node* get_next()
	{
		return next;
	}
	T get_val() const
	{
		return val;
	}
private:
	T* val;
	Node* next;
};