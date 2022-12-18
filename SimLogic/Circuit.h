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
	Circuit(Circuit&) = default;
	~Circuit() = default;
	void add_component(std::shared_ptr<Component> c)
	{
		m_compvec.push_back(std::move(c));
	}
	std::shared_ptr<Component> find_component(std::string s)
	{
		for (auto& c : m_compvec)
		{
			if (c->get_name() == s)
			{
				return c;
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
	std::string m_name = "";
	std::vector<std::shared_ptr<Component>> m_compvec;
};

