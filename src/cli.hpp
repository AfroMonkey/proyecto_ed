#ifndef CLI_HPP
#define CLI_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"

#ifdef _WIN32
const std::string CLEAR = "cls";
#else
const std::string CLEAR = "clear";
#endif

const int kCols = 80;
const std::string ver_s = "|";
const std::string hor_s = "-";

const std::string OPTION_NOT_FOUND = " Opcion no valida.";
const std::string RECORD_NOT_FOUND = " No se encontro ningun registro con esa informacion.";
const std::string PAUSE_MESSAGE = " Presiona enter...";
const std::string PROMPT_POSITIVE_INTEGER = " Ingresa un entero positivo: ";
const std::string HEADER_DEGREE = "Programas educativos";
const std::string HEADER_SUBJECT = "Asignaturas";

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

void display_sec_menu(const std::string header)
{
    clear_screen();
    print_centered(header);
    std::cout << " " << ADD      << ".- Agregar  " << std::endl;
    std::cout << " " << LIST     << ".- Mostrar  " << std::endl;
    std::cout << " " << SEARCH   << ".- Buscar   " << std::endl;
    std::cout << " " << EDIT     << ".- Modificar" << std::endl;
    std::cout << " " << DELETE   << ".- Eliminar " << std::endl;
    std::cout << " " << GO_BACK  << ".- Regresar " << std::endl << std::endl;
    std::cout << " Opcion: ";
}

int prompt_id()
{
    std::cout << " Ingresa el ID: ";
    return get_positive_int();
} 

void record_not_found()
{
    std::cout << RECORD_NOT_FOUND << std::endl;
}

void option_not_found()
{
    std::cout << OPTION_NOT_FOUND << std::endl;
}

// 'Degree' specific functions -------------------------------------------------

void set_degree(Degree& degree, bool edit = false)
{
    std::string str;
    if (edit)
    {
        std::cout << " Ingresa los nuevos datos: " << std::endl;
    }
    std::cout << "       ID: ";
    degree.set_id(get_positive_int());
    do
    {
        std::cout << "   Nombre: ";
        str = get_string();
    } while (!degree.set_name(str.c_str()));
    std::cout << " Creditos: ";
    degree.set_credits(get_positive_int());
    do
    {
        std::cout << " Division: ";
        str = get_string();
    } while (!degree.set_division(str.c_str()));
}

void print_degree_header(bool title = false)
{
    if (title)
    {
        std::cout << " ";
        for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
        std::cout << std::endl;
        print_centered(HEADER_DEGREE);
    }
    std::cout << " ";
    for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
    std::cout << std::endl;
    std::cout << std::setw(5)  << std::left << (" " + ver_s + " ID");
    std::cout << std::setw(32) << std::left << (ver_s + " Nombre");
    std::cout << std::setw(8)  << std::left << (ver_s + " Cred");
    std::cout << std::setw(33) << std::left << (ver_s + " Division");
    std::cout << ver_s << std::endl;
    std::cout << " ";
    for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
    std::cout << std::endl;
}

void print_degree(const Degree& degree)
{
    std::string s = ver_s + " ";
    std::cout << std::setw(5)  << std::left << (" " + s + std::to_string(degree.get_id()));
    std::cout << std::setw(32) << std::left << (s + degree.get_name());
    std::cout << std::setw(8)  << std::left << (s + std::to_string(degree.get_credits()));
    std::cout << std::setw(33) << std::left << (s + degree.get_division());
    std::cout << ver_s << std::endl;
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
