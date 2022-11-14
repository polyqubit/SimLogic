#include <iostream>
#include <fstream>

int main()
{
    std::ifstream ifs;
    ifs.open("../../hi.txt");
    if (ifs) {
        std::cout << "Hello World!\n";
    }
}