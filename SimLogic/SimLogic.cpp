#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>

//interesting discovery: for visual studio, local dir is not the .exe's but the .sln file

std::string read(std::string);

int main()
{
    for (const auto& file : std::filesystem::directory_iterator("files"))
    {
        if (file.path().extension() == ".txt")
        {
            std::string s = file.path().filename().string();
            s.erase(std::remove(s.begin(), s.end(), '\"'), s.end());
            std::cout << s << "\n";
        }
    }
    //std::cout << read("files\\message.txt");
}

std::string read(std::string in)
{
    std::ifstream ifs;
    ifs.open(in);
    if (!ifs) {
        ifs.close();
        return "Read failed. Path: "+in+"\n";
    }

    std::string a;
    std::string bob;
    while (std::getline(ifs, a)) //when reading from file, space and newline are both used as separators
    {
        bob.append(a.append("\n"));
    }
    ifs.close();
    return bob;
}