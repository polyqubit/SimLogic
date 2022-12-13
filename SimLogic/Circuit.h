#pragma once
#include <iostream>
#include <string>

class Circuit
{
public:
	Circuit(std::string n)
	{
		name = n;
	}
	void add_component();
private:
	std::string name;
};

