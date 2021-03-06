#ifndef CLI_HPP
#define CLI_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"
#include "relation.hpp"

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
const std::string HEADER_RELATION = "Relacion de materias";
const std::string HEADER_REPORTS = "Reportes de materias";

enum menu_option
{
    DEGREE  = 1,
    SUBJECT = 2,
    ADD_SUBJECT = 3,
    REMOVE_SUBJECT = 4,
    REPORTS = 5,
    EXIT    = 6,
    ADD     = 1,
    LIST    = 2,
    SEARCH  = 3,
    EDIT    = 4,
    DELETE  = 5,
    GO_BACK = 6,
    BY_CATEGORY = 1,
    BY_DEGREE = 2
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

char get_char()
{
    char c;
    while (!(std::cin >> c))
    {
        std::cin.clear();
        std::cin.ignore();
    }
    std::cin.ignore();
    return c;
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
    std::cout << " " << DEGREE << ".- Programas educativos" << std::endl;
    std::cout << " " << SUBJECT << ".- Asignaturas         " << std::endl;
    std::cout << " " << ADD_SUBJECT << ".- Asignar materia a programa" << std::endl;
    std::cout << " " << REMOVE_SUBJECT << ".- Eliminar materia de un programa" << std::endl;
    std::cout << " " << REPORTS << ".- Reportes         " << std::endl;
    std::cout << " " << EXIT << ".- Salir               " << std::endl << std::endl;
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
    std::cout << " " << GO_BACK  << ".- Regresar " << std::endl;
    std::cout << std::endl;
    std::cout << " Opcion: ";
}

void display_reports_menu()
{
    clear_screen();
    print_centered(HEADER_REPORTS);
    std::cout << " " << BY_CATEGORY     << ".- Categoria  " << std::endl;
    std::cout << " " << BY_DEGREE   << ".- Programa educativo   " << std::endl;
    std::cout << " " << GO_BACK  << ".- Regresar " << std::endl;
    std::cout << std::endl;
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

// 'Relation' specific functions -----------------------------------------------
void set_relation(Relation& relation)
{
    std::cout << "  ID del programa: ";
    relation.set_degree_id(get_positive_int());
    std::cout << " ID de la materia: ";
    relation.set_subject_id(get_positive_int());
    std::cout << "  Tipo de materia: ";
    relation.set_type(get_char());
}

void print_relation_header(bool title = false)
{
    if (title)
    {
        std::cout << " ";
        for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
        std::cout << std::endl;
        print_centered(HEADER_RELATION);
    }
    std::cout << " ";
    for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
    std::cout << std::endl;
    std::cout << std::setw(20)  << std::left << (" " + ver_s + " ID del programa");
    std::cout << std::setw(20) << std::left << (ver_s + " ID de la materia");
    std::cout << std::setw(38)  << std::left << (ver_s + " Tipo");
    std::cout << ver_s << std::endl;
    std::cout << " ";
    for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
    std::cout << std::endl;
}

void print_relation(const Relation& relation)
{
    std::string s = ver_s + " ";
    std::cout << std::setw(20)  << std::left << (" " + s + std::to_string(relation.get_degree_id()));
    std::cout << std::setw(20) << std::left << (s + std::to_string(relation.get_subject_id()));
    std::cout << std::setw(38)  << std::left << (s + std::to_string(relation.get_type()));
    std::cout << ver_s << std::endl;
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

void set_subject(Subject& subject, bool edit = false)
{
    std::string str;
    if (edit)
    {
        std::cout << " Ingresa los nuevos datos: " << std::endl;
    }
    std::cout << "       ID: ";
    subject.set_id(get_positive_int());
    do
    {
        std::cout << "   Nombre: ";
        str = get_string();
    } while (!subject.set_name(str.c_str()));
    std::cout << " Creditos: ";
    subject.set_credits(get_positive_int());
}

void print_subject_header(bool title, int type = 0)
{
    if (title)
    {
        std::cout << " ";
        for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
        std::cout << std::endl;
        print_centered(HEADER_SUBJECT);
    }
    std::cout << " ";
    for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
    std::cout << std::endl;
    std::cout << std::setw(5)  << std::left << (" " + ver_s + " ID");
    if (type == 0)
    {
        std::cout << std::setw(65) << std::left << (ver_s + " Nombre");
    }
    else
    {
        std::cout << std::setw(45) << std::left << (ver_s + " Nombre");
        if (type == 1)
        {
            std::cout << std::setw(20) << std::left << (ver_s + " ID Programa");
        }
        else
        {
            std::cout << std::setw(20) << std::left << (ver_s + " Tipo");
        }
    }
    std::cout << std::setw(8)  << std::left << (ver_s + " Cred");
    std::cout << ver_s << std::endl;
    std::cout << " ";
    for (int i = 0; i < kCols - 2; ++i) std::cout << hor_s;
    std::cout << std::endl;
}

void print_subject(const Subject& subject, char type = '\x0', int id = 0)
{
    std::string s = ver_s + " ";
    std::cout << std::setw(5)  << std::left << (" " + s + std::to_string(subject.get_id()));
    if (type == '\x0' || type == 'x')
    {
        if (id == 0)
        {
            std::cout << std::setw(65) << std::left << (s + subject.get_name());
        }
        else
        {
            std::cout << std::setw(45) << std::left << (s + subject.get_name());
            std::cout << std::setw(20) << std::left << (s + std::to_string(id));
        }
    }
    else
    {
        std::cout << std::setw(45) << std::left << (s + subject.get_name());
        switch (type)
        {
            case 'b':
                std::cout << std::setw(20) << std::left << (s + "Basica");
                break;
            case 'e':
                std::cout << std::setw(20) << std::left << (s + "Especializante");
                break;
            case 'l':
                std::cout << std::setw(20) << std::left << (s + "Lengua extranjera");
        }
    }
    std::cout << std::setw(8)  << std::left << (s + std::to_string(subject.get_credits()));
    std::cout << ver_s << std::endl;
}

#endif
