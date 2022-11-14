#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>

//interesting discovery: for vscode, local dir is not the .exe's but the .sln file

int main()
{
    std::ifstream ifs;
    ifs.open("message.txt");
    if (!ifs) {
        std::cout << "Bye World!\n";
        exit(-1);
    }
    std::cout << "Hello World!\n";

    std::string a;
    std::string bob;
    while (std::getline(ifs, a)) //when reading from file, space and newline are both used as separators
    {
        bob.append(a.append("\n"));
    }
    std::cout << bob;
}