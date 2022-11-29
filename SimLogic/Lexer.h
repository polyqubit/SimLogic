#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

class Lexer
{
public:
	void produce_tokens(std::string);
private:
	bool m_inCircuit;
	//std::vector<> m_cvec;
};

