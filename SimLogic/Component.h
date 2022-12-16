#pragma once
#include <iostream>

class Component
{
public:
	Component(std::string s)
	{
		m_name = s;
	}
	void propagate(bool);
private:
	std::string m_name;
};

class Input : public Component
{
public:
	void propagate(bool pass)
	{
		for (auto& i : m_compvec)
		{
			i->propagate(pass);
		}
	}
	void add_child(Component* c)
	{
		m_compvec.push_back(c);
	}
private:
	std::vector<Component*> m_compvec;
};

class And : public Component
{
public:
	void propagate(bool pass)
	{
		if (m_boolvec.size() == m_compvec.size())
		{
			real_propagate();
		}
		else
		{
			m_boolvec.push_back(pass);
		}
	}
	void real_propagate()
	{
		bool store = true;
		for (bool i : m_boolvec)
		{
			if (!i)
			{
				store = false;
				break;
			}
		}
		for (auto& i : m_compvec)
		{
			i->propagate(store);
		}
	}
	void add_child(Component* c)
	{
		m_compvec.push_back(c);
	}
private:
	std::vector<Component*> m_compvec;
	std::vector<bool> m_boolvec;
};

class Or : public Component
{
public:
	void propagate(bool pass)
	{
		if (m_boolvec.size() == m_compvec.size())
		{
			real_propagate();
		}
		else
		{
			m_boolvec.push_back(pass);
		}
	}
	void real_propagate()
	{
		bool store = false;
		for (bool i : m_boolvec)
		{
			if (i)
				break;
		}
		for (auto& i : m_compvec)
		{
			i->propagate(store);
		}
	}
	void add_child(Component* c)
	{
		m_compvec.push_back(c);
	}
private:
	std::vector<Component*> m_compvec;
	std::vector<bool> m_boolvec;
};

class Not : public Component
{
public:
	void propagate(bool pass)
	{
		for (auto& i : m_compvec)
		{
			i->propagate(!pass);
		}
	}
	void add_child(Component* c)
	{
		m_compvec.push_back(c);
	}
private:
	std::vector<Component*> m_compvec;
};

class Output : public Component
{
public:
	void propagate(bool pass)
	{
		if (pass)
			state = 1;
		else
			state = 0;
	}
	int get_state()
	{
		return state;
	}
private:
	std::vector<Component*> m_compvec;
	int state = -1;
};