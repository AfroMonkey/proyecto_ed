#include <iostream>
#include "linked_list.hpp"

int main(int argc, char const *argv[])
{
    linked_list<int> list;
    std::cout << list.size() << std::endl;
    std::cout << list.empty() << std::endl;
    list.push_back(1);
    list.push_back(12);
    list.push_back(5);
    list.push_back(9);
    std::cout << list.size() << std::endl;
    linked_list<int>::iterator x = list.begin();
    ++x;
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    //list.clear();
    return 0;
}