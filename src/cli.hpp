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

const int kRows = 24;
const int kCols = 80;

const std::string OPTION_NOT_FOUND = " Opcion no valida.";
const std::string PAUSE_MESSAGE = " Presiona enter...";
const std::string PROMPT_POSITIVE_INTEGER = " Ingresa un entero positivo: ";

enum menu_option
{
    DEGREE  = 1,
    SUBJECT = 2,
    EXIT    = 3,
    ADD     = 1,
    LIST    = 2,
    SEARCH  = 3,
    EDIT    = 4,
    DELETE  = 5,
    GO_BACK = 6
};

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

void clear_screen()
{
    system(CLEAR.c_str());
}

void pause_program(std::string msg = PAUSE_MESSAGE)
{
    std::cout << msg;
    std::cin.ignore();
}

void print_centered(std::string msg, char fill = ' ')
{
    int padding = (kCols - msg.length()) / 2;
    for (int i = 0; i < padding; i++) std::cout << fill;
    std::cout << msg;
    for (int i = 0; i < padding; i++) std::cout << fill;
    if (msg.length() % 2) std::cout << fill;
}

void display_main_menu()
{
    clear_screen();
    print_centered("Malla Curricular");
    std::cout << " 1.- Programas educativos" << std::endl;
    std::cout << " 2.- Asignaturas         " << std::endl;
    std::cout << " 3.- Salir               " << std::endl << std::endl;
    std::cout << " Opcion: ";
}

void display_sec_menu(int type = DEGREE)
{
    clear_screen();
    type == DEGREE ? print_centered("Programas educativos") 
                   : print_centered("Asignaturas");
    std::cout << " 1.- Agregar  " << std::endl;
    std::cout << " 2.- Mostrar  " << std::endl;
    std::cout << " 3.- Buscar   " << std::endl;
    std::cout << " 4.- Modificar" << std::endl;
    std::cout << " 5.- Eliminar " << std::endl;
    std::cout << " 6.- Regresar " << std::endl << std::endl;
    std::cout << " Opcion: ";
}

void option_not_found()
{
    std::cout << OPTION_NOT_FOUND << std::endl;
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
