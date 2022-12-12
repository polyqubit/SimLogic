#include "Node.h"

template <class T>
void Node<T>::set_next(Node<T>& t)
{
	next = t;
}

template <class T>
T Node<T>::get_val() const
{
	return val;
}