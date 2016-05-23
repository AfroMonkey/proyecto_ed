#include <fstream>
#include <iostream>
#include <algorithm>
#include "linked_list.hpp"

int main(int argc, char const *argv[])
{
    linked_list<int> list;
    std::ifstream in("test.txt");
    list.read(in);
    in.close();
    //list.push_back(1);
    //list.push_back(12);
    //list.push_back(5);
    //list.push_back(9);
    //list.push_front(0);
    //std::ofstream out("test.txt", std::ios::trunc);
    //list.write(out);
    //out.close();
    for (auto it = list.begin(); it != list.end(); it++)
    {
        std::cout << *it << "\n";
    }

    return 0;
}
