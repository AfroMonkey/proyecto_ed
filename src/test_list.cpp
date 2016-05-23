#include <fstream>
#include <iostream>
#include <algorithm>
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
    list.push_front(0);
    std::cout << list.size() << std::endl;
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    list.remove(5);
    list.push_back(13);
    list.push_front(20);
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    *list.at(2) = 33;
    std::cout << *list.at(2) << std::endl;
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (linked_list<int>::iterator it = list.find(9); it != list.end(); --it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl << " List 2" << std::endl;
    linked_list<int> list2(list);
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl << " List 3" << std::endl;
    linked_list<int> list3;
    list3 = list;
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::ifstream in;
    std::ofstream out;

    out.open("test.txt", std::ios::trunc);
    list3.write(out);
    out.close();

    linked_list<int> list4;
    in.open("text.txt");
    list4.read(in);
    in.close();
    std::cout << " List 4" << std::endl;
    for (linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    return 0;
}
