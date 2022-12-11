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
private:
	std::string name;
};

