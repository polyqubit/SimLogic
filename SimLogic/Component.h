#pragma once
#include <iostream>

class Component
{
public:
	Component(std::string s)
	{
		m_name = s;
	}
private:
	std::string m_name;
};

class Input : public Component
{
public:
	void propagate()
	{
		for (auto& i : m_compvec)
		{
		}
	}
	void set_child(Component* c)
	{
		m_compvec.push_back(c);
	}
private:
	std::vector<Component*> m_compvec;
};