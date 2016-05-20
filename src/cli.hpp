#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>

#include "subject.hpp"

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

char* get_string(std::string m = ">")
{
    //TODO [FIX] Free memory
    char* cs;
    std::string s;

    std::cout << m;

    getline(std::cin, s);
    cs = new char[s.length()];
    for(int i = 0; s[i]; i++)
    {
        cs[i] = s[i];
    }

    return cs;
}

void fill_subject(Subject &subject)
{
    char* name;

    subject.set_id(get_int("ID>"));

    do
    {
        name = get_string("Nombre>");
    } while (!subject.set_name(name));
    delete name;

    subject.set_credits(get_int("Creditos>"));
}

void print_subject_row(Subject &subject)
{
    //TODO [FIX] Alligment
    std::cout << subject.get_id() << "\t";
    std::cout << subject.get_name() << "\t";
    std::cout << subject.get_credits() << "\n";
}

#endif
