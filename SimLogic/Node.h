#pragma once

template <class T>
class Node
{
public:
	Node(T& t)
	{
		val = t;
	}
	void set_next(Node&);
	T get_val() const;
private:
	T* val;
	Node* next;
};