#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <exception>

#include "Lexer.h"
#include "Node.h"
#include "Stack.h"

//interesting discovery: for visual studio, local dir is not the .exe's but the .sln file

//int main()
//{
//    std::cout << "[System]\n";
//    for (const auto& file : std::filesystem::directory_iterator("files"))
//    {
//        if (file.path().extension() == ".txt")
//        {
//            std::string s = file.path().filename().string();
//            s.erase(std::remove(s.begin(), s.end(), '\"'), s.end());
//            std::cout << s << "\n";
//        }
//    }
//
//    std::cout << "\nEnter name of file(no .txt) ";
//    std::string inp;
//    std::cin >> inp;
//    
//    Lexer lex;
//    Message test = lex.read_file("files\\"+inp+".txt");
//    std::cout << test.message << "\n";
//    lex.output_linevec();
//}

int main()
{
	std::string s1 = "abcd";
	Stack<std::string> stakataka(s1);
	std::string s2 = "efgh";
	stakataka.push_val(s2);
	std::cout << "Stack: ";
}