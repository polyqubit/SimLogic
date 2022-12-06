#pragma once
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <exception>

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
	void output_linevec();
private:
	std::vector<std::string> m_linevec;
};

