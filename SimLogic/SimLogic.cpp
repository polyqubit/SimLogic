#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <exception>

//interesting discovery: for visual studio, local dir is not the .exe's but the .sln file

std::string read(std::string, std::string);
int evaluate_expr(std::string);

int main()
{
    std::cout << "[System]\n";
    for (const auto& file : std::filesystem::directory_iterator("files"))
    {
        if (file.path().extension() == ".txt")
        {
            std::string s = file.path().filename().string();
            s.erase(std::remove(s.begin(), s.end(), '\"'), s.end());
            std::cout << s << "\n";
        }
    }

    std::cout << "\nEnter name of file(no .txt) ";
    std::string inp;
    std::cin >> inp;
    std::cout << read("files\\" + inp + ".txt", inp);
}

std::string read(std::string in, std::string name)
{
    std::ifstream ifs;
    ifs.open(in);
    if (!ifs) {
        ifs.close();
        return "Read failed. Path: "+in+"\n";
    }

    std::string a;
    std::string bob;
    std::cout << name << " contents:\n\n";
    while (std::getline(ifs, a)) //when reading from file, space and newline are both used as separators
    {
        bob.append(a.append(" = "));
        bob.append(std::to_string(evaluate_expr(a)));
        bob.append("\n");
    }
    ifs.close();
    return bob;
}

int evaluate_expr(std::string line)
{
    std::vector<std::string> tokens;
    int* nums = new int[8192];
    if (line.find("+") >= 0)
    {
        try
        {
            /*int num1 = std::stoi(line.substr(0, sym_position));
            int num2 = std::stoi(line.substr(sym_position + 1));
            return num1 + num2;*/
            while (line.length()>0)
            {
                int sym_position = line.find("+");
                int num1 = std::stoi(line.substr(0, sym_position));
                int num2 = std::stoi(line.substr(sym_position + 1));
            }
        }
        catch (std::exception& e)
        {
            std::cout << "Exception: " << e.what() << "\n";
            return 0;
        }
    }
    try
    {
        return std::stoi(line);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
        return 0;
    }
}