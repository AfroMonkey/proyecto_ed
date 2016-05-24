
#include <cstdio>
#include <fstream>
#include <iostream>

#include "cli.hpp"
#include "config.hpp"
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"
#include "relation.hpp"

linked_list<Degree> degrees;
linked_list<Subject> subjects;
linked_list<Relation> relations;

void manage_degrees();
void manage_subjects();
void manage_reports();

void add_degree();
void list_degrees();
Degree search_degree();
void edit_degree();
void delete_degree();
void add_subject_to_degree();

void add_subject();
void list_subjects();
Subject search_subject();
void edit_subject();
void delete_subject();

void add_subject_to_degree();
void list_all_subjects();
void list_by_category();
void list_by_degree();

int main()
{
    std::ifstream input_degrees(DEGREES_FILE);
    std::ifstream input_subjects(SUBJECTS_FILE);
    std::ifstream input_relations(RELATIONS_FILE);
    degrees.read(input_degrees);
    subjects.read(input_subjects);
    relations.read(input_relations);
    input_degrees.close();
    input_subjects.close();
    input_relations.close();
    bool exit_program = false;
    while (!exit_program)
    {
        display_main_menu();
        switch(get_int())
        {
            case DEGREE:
                manage_degrees();
                break;
            case SUBJECT:
                manage_subjects();
                break;
            case ADD_SUBJECT:
                add_subject_to_degree();
                pause_program();
                break;
            case REPORTS:
                manage_reports();
                break;
            case EXIT:
                clear_screen();
                exit_program = true;
                break;
            default:
                option_not_found();
                pause_program();
        }
    }
    std::ofstream output_degrees(DEGREES_FILE, std::ios::trunc);
    std::ofstream output_subjects(SUBJECTS_FILE, std::ios::trunc);
    std::ofstream output_relations(RELATIONS_FILE, std::ios::trunc);
    degrees.write(output_degrees);
    subjects.write(output_subjects);
    relations.write(output_relations);
    output_degrees.close();
    output_subjects.close();
    output_relations.close();
    return 0;
}

void manage_degrees()
{
    bool go_back = false;
    while (!go_back)
    {
        display_sec_menu(HEADER_DEGREE);
        switch(get_int())
        {
            case ADD:
                add_degree();
                break;
            case LIST:
                list_degrees();
                break;
            case SEARCH:
                search_degree();
                break;
            case EDIT:
                edit_degree();
                break;
            case DELETE:
                delete_degree();
                break;
            case GO_BACK:
                go_back = true;
                break;
            default:
                std::cout << OPTION_NOT_FOUND << std::endl;
        }
        if (!go_back) pause_program();
    }
}

void manage_subjects()
{
    bool go_back = false;
    while (!go_back)
    {
        display_sec_menu(HEADER_SUBJECT);
        switch(get_int())
        {
            case ADD:
                add_subject();
                break;
            case LIST:
                list_subjects();
                break;
            case SEARCH:
                search_subject();
                break;
            case EDIT:
                edit_subject();
                break;
            case DELETE:
                delete_subject();
                break;
            case GO_BACK:
                go_back = true;
                break;
            default:
                std::cout << OPTION_NOT_FOUND << std::endl;
        }
        if (!go_back) pause_program();
    }
}

void add_degree()
{
    Degree degree;
    set_degree(degree);
    if (degrees.find(degree) != degrees.end())
    {
        std::cout << "Ese programa ya existe" << "\n"; //TODO change to cli
        return;
    }
    degrees.push_back(degree);
}

void list_degrees()
{
    Degree degree;
    clear_screen();
    print_degree_header(true);
    for (auto it = degrees.begin(); it != degrees.end(); it++)
    {
        print_degree((Degree)*it);
    }
    std::cout << std::endl;
}

Degree search_degree()
{
    Degree degree;
    degree.set_id(prompt_id());
    if (degrees.find(degree) == degrees.end())
    {
        std::cout << "Ese programa no existe" << "\n"; //TODO change to cli
        Degree empty;
        return empty;
    }
    degree = *degrees.find(degree);
    clear_screen();
    print_degree_header(false);
    print_degree(degree);
    return degree;
}

void edit_degree()
{
    Degree degree = search_degree();
    if (degree.get_id() == (unsigned)-1) return;
    unsigned int old_id = degree.get_id();
    set_degree(degree, true);
    degrees.remove(degree);
    degrees.push_front(degree);

    for (auto it = relations.begin(); it != relations.end(); it++)
    {
        if (it->get_degree_id() == old_id)
        {
            it->set_degree_id(degree.get_id());
        }
    }
}

void delete_degree()
{
    Degree degree;
    degree = search_degree();
    if (degree.get_id() == (unsigned)-1) return;
    for (auto it = relations.begin(); it != relations.end(); it++)
    {
        if (it->get_degree_id() == degree.get_id())
        {
            relations.remove(*it);
        }
    }
    degrees.remove(degree);
}


void add_subject()
{
    Subject subject;
    set_subject(subject);
    if (subjects.find(subject) != subjects.end())
    {
        std::cout << "Esa materia ya existe" << "\n"; //TODO change to cli
        return;
    }
    subjects.push_back(subject);
}

void manage_reports()
{
    bool go_back = false;
    while (!go_back)
    {
        display_reports_menu();
        switch(get_int())
        {
            case BY_CATEGORY:
                list_by_category();
                break;
            case BY_DEGREE:
                list_by_degree();
                break;
            case GO_BACK:
                go_back = true;
                break;
            default:
                std::cout << OPTION_NOT_FOUND << std::endl;
        }
        if (!go_back) pause_program();
    }
}

void list_subjects()
{
    Subject subject;
    clear_screen();
    print_subject_header(true);
    for (auto it = subjects.begin(); it != subjects.end(); it++)
    {
        print_subject((Subject)*it);
    }
    std::cout << std::endl;
}

void list_by_category()
{
    std::cout << "Ingrese la categoria (b/e/l):";
    char type = get_char();

    if (type != 'b' && type != 'e' && type != 'l')
    {
        std::cout << "Categoria invalida" << "\n";
        return;
    }

    print_subject_header(true, true);
    Subject subject;
    for (auto it = relations.begin(); it != relations.end(); it++)
    {
        if (it->get_type() == type)
        {
            subject.set_id(it->get_subject_id());
            print_subject((Subject)*subjects.find(subject), type);
        }
    }
}

void list_by_degree()
{
    //TODO sort list
    Degree degree;
    Subject subject;
    degree.set_id(prompt_id());
    print_subject_header(true, true);
    for (auto it = relations.begin(); it != relations.end(); it++)
    {
        if (it->get_degree_id() == degree.get_id())
        {
            subject.set_id(it->get_subject_id());
            print_subject((Subject)*subjects.find(subject), it->get_type());
        }
    }
    std::cout << std::endl;
}


Subject search_subject()
{
    Subject subject;
    subject.set_id(prompt_id());
    if (subjects.find(subject) == subjects.end())
    {
        std::cout << "Esa materia no existe" << "\n"; //TODO change to cli
        Subject empty;
        return empty;
    }
    subject = *subjects.find(subject);
    clear_screen();
    print_subject_header(false);
    print_subject(subject);
    return subject;
}

void edit_subject()
{
    Subject subject = search_subject();
    if (subject.get_id() == (unsigned)-1) return;
    unsigned int old_id = subject.get_id();
    set_subject(subject, true);
    subjects.remove(subject);
    subjects.push_front(subject);

    for (auto it = relations.begin(); it != relations.end(); it++)
    {
        if (it->get_subject_id() == old_id)
        {
            it->set_subject_id(subject.get_id());
        }
    }
}

void delete_subject()
{
    Subject subject;
    subject = search_subject();
    if (subject.get_id() == (unsigned)-1) return;
    for (auto it = relations.begin(); it != relations.end(); it++)
    {
        if (it->get_subject_id() == subject.get_id())
        {
            relations.remove(*it);
        }
    }
    subjects.remove(subject);
}

void add_subject_to_degree()
{
    Relation relation;
    Degree degree;
    Subject subject;

    std::cout << "ID del programa educativo: "; //TODO change to cli
    relation.set_degree_id(get_positive_int());
    degree.set_id(relation.get_degree_id());
    if (degrees.find(degree) == degrees.end())
    {
        std::cout << "No existe ese programa" << "\n";
        return;
    }

    std::cout << "ID de la materia: "; //TODO change to cli
    relation.set_subject_id(get_positive_int());
    subject.set_id(relation.get_subject_id());
    if (subjects.find(subject) == subjects.end())
    {
        std::cout << "No existe esa materia" << "\n";
        return;
    }

    if (relations.find(relation) != relations.end())
    {
        std::cout << "Esa relacion ya existe" << "\n";
        return;
    }

    std::cout << "Tipo de materia (b/e/l): "; //TODO change to cli
    while (!relation.set_type(get_char()));
    relations.push_back(relation);
}
