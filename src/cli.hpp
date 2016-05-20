#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>

int get_int(std::string m = ">")
{
    int i;
    std::cout << m;
    while (!(std::cin >> i))
    {
        std::cout << m;
        std::cin.clear();
        std::cin.ignore();
    }
    std::cin.ignore();
    return i;
}

#endif
