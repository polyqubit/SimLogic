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
	void add_component(std::unique_ptr<Component> c)
	{
		m_compvec.push_back(c);
	}
	std::unique_ptr<Component> find_component(std::string s)
	{
		for (auto& c : m_compvec)
		{
			if (c->get_name() == s)
			{
				return std::move(c);
			}
		}
		return NULL;
	}
	void print()
	{
		for (auto& c : m_compvec)
		{
			std::cout << c->get_name() << " ";
		}
	}
private:
	std::string m_name;
	std::vector<std::unique_ptr<Component>> m_compvec;
};

