#ifndef CLI_HPP
#define CLI_HPP

#include <cstdlib>
#include <iostream>
#include "degree.hpp"
#include "subject.hpp"

#ifdef _WIN32
const std::string CLEAR = "cls";
#else
const std::string CLEAR = "clear";
#endif

const std::string PAUSE_MESSAGE = " Presiona enter...";
const std::string PROMPT_POSITIVE_INTEGER = "Ingresa un entero positivo: ";

// Input functions ---------------------------------------------------------

int get_int(int d = -1)
{
    // Prompts user for an int, if user doesn't enter an int, returns 'd'
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
    // Uses 'get_int' until the user enters a positive int, then returns it
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
    // Prompts user for a string and returns it
    std::string str;
    getline(std::cin, str);
    return str;
}

// Menus, messages and interface functions -------------------------------------

void print_menu()
{
    // TODO
}

void clear_screen()
{
    system(CLEAR.c_str());
}

void pause_program(std::string msg = PAUSE_MESSAGE)
{
    std::cout << msg;
    std::cin.ignore();
}

// 'Degree' specific functions -------------------------------------------------

void set_degree(Degree& degree)
{
    std::string str;
    degree.set_id(get_positive_int());
    do
    {
        str = get_string();
    } while (!degree.set_name(str.c_str()));
    degree.set_credits(get_positive_int());
    do
    {
        str = get_string();
    } while (!degree.set_division(str.c_str()));
}

// 'Subject' specific functions ------------------------------------------------

void set_subject(Subject& subject)
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
