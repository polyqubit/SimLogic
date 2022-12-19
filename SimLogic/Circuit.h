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
	std::shared_ptr<std::vector<std::shared_ptr<Component>>> get_inputs() const
	{
		std::vector<std::shared_ptr<Component>> invec;
		auto shared_invec = std::make_shared<std::vector<std::shared_ptr<Component>>>(invec);
		for (auto& c : m_compvec)
		{
			if (c->get_type() == "Input")
			{
				shared_invec->push_back(c);
			}
		}
		return shared_invec;
	}
	std::shared_ptr<std::vector<std::shared_ptr<Component>>> get_outputs() const
	{
		std::vector<std::shared_ptr<Component>> outvec;
		auto shared_outvec = std::make_shared<std::vector<std::shared_ptr<Component>>>(outvec);
		for (auto& c : m_compvec)
		{
			if (c->get_type() == "Output")
			{
				shared_outvec->push_back(c);
			}
		}
		return shared_outvec;
	}
	std::string get_name() const
	{
		return m_name;
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

