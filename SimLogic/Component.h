#pragma once
#include <iostream>
#include <memory>

class Component
{
public:
	Component(std::string s)
	{
		m_name = s;
	}
	Component(Component&) = default;
	void propagate(bool)
	{
	}
	void add_child(std::unique_ptr<Component>)
	{
	}
	std::string get_name()
	{
		return m_name;
	}
	virtual std::string get_type()
	{
		return "Component";
	}
private:
	std::string m_name = "";
};

class Input : public Component
{
public:
	Input(std::string s) : Component(s)
	{
	}
	Input(Input&) = default;
	void propagate(bool pass)
	{
		for (auto& i : m_compvec)
		{
			i->propagate(pass);
		}
	}
	void add_child(std::unique_ptr<Component> c)
	{
		m_compvec.push_back(std::move(c));
	}
	std::string get_type()
	{
		return "Input";
	}
private:
	std::vector<std::unique_ptr<Component>> m_compvec;
};

class And : public Component
{
public:
	And(std::string s, int n) : Component(s)
	{
		if (n < 8)
			limit = n;
	}
	And(And&) = default;
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
	void add_child(std::unique_ptr<Component> c)
	{
		m_compvec.push_back(std::move(c));
	}
	std::string get_type()
	{
		return "And";
	}
private:
	std::vector<std::unique_ptr<Component>> m_compvec;
	bool m_boolarray[8] = { false };
	int limit = 8;
	int c = 0;
};

class Or : public Component
{
public:
	Or(std::string s, int n) : Component(s)
	{
		if (n < 8)
			limit = n;
	}
	Or(Or&) = default;
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
	void add_child(std::unique_ptr<Component> c)
	{
		m_compvec.push_back(std::move(c));
	}
	std::string get_type()
	{
		return "Or";
	}
private:
	std::vector<std::unique_ptr<Component>> m_compvec;
	bool m_boolarray[8] = { false };
	int limit = 8;
	int c = 0;
};

class Xor : public Component
{
public:
	Xor(std::string s) : Component(s)
	{
	}
	Xor(Xor&) = default;
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
			&& (!m_boolarray[0] || !m_boolarray[1]);
		for (auto& i : m_compvec)
		{
			i->propagate(store);
		}
	}
	void add_child(std::unique_ptr<Component> c)
	{
		m_compvec.push_back(std::move(c));
	}
	std::string get_type()
	{
		return "Xor";
	}
private:
	std::vector<std::unique_ptr<Component>> m_compvec;
	bool* m_boolarray = new bool[2];
	int c = 0;
};

class Not : public Component
{
public:
	Not(std::string s) : Component(s)
	{
	}
	Not(Not&) = default;
	void propagate(bool pass)
	{
		for (auto& i : m_compvec)
		{
			i->propagate(!pass);
		}
	}
	void add_child(std::unique_ptr<Component> c)
	{
		m_compvec.push_back(std::move(c));
	}
	std::string get_type()
	{
		return "Not";
	}
private:
	std::vector<std::unique_ptr<Component>> m_compvec;
};

class Output : public Component
{
public:
	Output(std::string s) : Component(s)
	{
	}
	Output(Output&) = default;
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
	std::string get_type()
	{
		return "Output";
	}
private:
	int state = -1;
};