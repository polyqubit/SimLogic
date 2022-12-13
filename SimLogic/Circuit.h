#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Component.h"

class Circuit
{
public:
	Circuit(std::string n)
	{
		m_name = n;
	}
	void add_component(Component* c)
	{
		m_compvec.push_back(c);
	}
private:
	std::string m_name;
	std::vector<Component*> m_compvec;
};

