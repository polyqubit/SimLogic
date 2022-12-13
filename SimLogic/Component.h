#pragma once
#include <iostream>

class Component
{
public:
	Component(std::string s)
	{
		name = s;
	}
	void set_child(Component* c)
	{
		child = c;
	}
private:
	std::string name;
	Component* child;
};