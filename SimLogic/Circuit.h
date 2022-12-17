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
	Component* find_component(std::string s)
	{
		for (Component* c : m_compvec)
		{
			if (c->get_name() == s)
			{
				return c;
			}
		}
		return NULL;
	}
private:
	std::string m_name;
	std::vector<Component*> m_compvec;
};

