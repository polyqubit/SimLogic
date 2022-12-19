#pragma once
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <exception>
#include "Circuit.h"

struct Message {
	std::string message = "";
	int linenum = -1;
	bool incorrect = false;
};

class Lexer
{
public:
	Message produce_tokens(std::string);
	Message read_file(std::string);
	Message evaluate_circ();
	void output_linevec();
	void output_circ();
private:
	std::vector<std::string> m_linevec;
	std::vector<std::shared_ptr<Circuit>> m_cvec;
	std::stack<std::shared_ptr<Circuit>> m_cstack;
};