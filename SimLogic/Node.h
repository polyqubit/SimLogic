#pragma once

template <class T>
class Node
{
public:
	Node(T);
	void set_next(Node&);
private:
	T val;
	Node* next;
};