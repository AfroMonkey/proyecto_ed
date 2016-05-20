#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include "subject.hpp"

const std::string PROMPT_POSITIVE_INTEGER = "Ingresa un entero positivo: ";

int get_int(int d = -1)
{
    int n;
    if (!(std::cin >> n))
    {
        n = d;
        std::cin.clear();
        std::cin.ignore();
    }
    std::cin.ignore();
    return n;
}

int get_positive_int()
{
    int n = get_int();
    while (n < 0)
    {
        std::cout << PROMPT_POSITIVE_INTEGER;
        n = get_int();
    }
    return n;
}

std::string get_string()
{
    std::string str;
    getline(std::cin, str);
    return str;
}

// 'Subject' specific functions

void set_subject(Subject &subject)
{
    // Prompts user to enter the data needed for a subject
    std::string str;
    subject.set_id(get_positive_int());
    do
    {
        str = get_string();
    } while (!subject.set_name(str.c_str()));
    subject.set_credits(get_positive_int());
}

void print_subject(const Subject& subject)
{
    //TODO [FIX] Alligment
    // Prints data contained by subject
    std::cout << subject.get_id() << "\t";
    std::cout << subject.get_name() << "\t";
    std::cout << subject.get_credits() << "\n";
}

#endif
