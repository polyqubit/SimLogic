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
	Input(std::string s) : Component(s)
	{
	}
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
	And(std::string s, int n) : Component(s)
	{
		limit = n;
	}
	void propagate(bool pass)
	{
		if (c == limit)
		{
			real_propagate();
		}
		else
		{
			m_boolarray[c] = pass;
			c++;
		}
	}
	void real_propagate()
	{
		bool store = true;
		for (int i = 0; i < limit; ++i)
		{
			if (!m_boolarray[i])
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
	bool m_boolarray[8] = { false };
	int limit;
	int c;
};

class Or : public Component
{
public:
	Or(std::string s, int n) : Component(s)
	{
		limit = n;
	}
	void propagate(bool pass)
	{
		if (c == limit)
		{
			real_propagate();
		}
		else
		{
			m_boolarray[c] = pass;
			c++;
		}
	}
	void real_propagate()
	{
		bool store = false;
		for (int i = 0; i < limit; ++i)
		{
			if (m_boolarray[i])
			{
				store = true;
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
	bool m_boolarray[8] = { false };
	int limit;
	int c;
};

class Xor : public Component
{
public:
	Xor(std::string s) : Component(s)
	{
	}
	void propagate(bool pass)
	{
		if (c == 2)
		{
			real_propagate();
		}
		else
		{
			m_boolarray[c] = pass;
		}
	}
	void real_propagate()
	{
		bool store = (m_boolarray[0] || m_boolarray[1])
				   &&(!m_boolarray[0] || !m_boolarray[1]);
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
	bool* m_boolarray = new bool[2];
	int c = 0;
};

class Not : public Component
{
public:
	Not(std::string s) : Component(s)
	{
	}
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
	Output(std::string s) : Component(s)
	{
	}
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