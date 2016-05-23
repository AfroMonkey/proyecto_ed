
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


int main()
{
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
            case EXIT:
                clear_screen();
                exit_program = true;
                break;
            default:
                option_not_found();
                pause_program();
        }
    }
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
            case ADD_SUBJECT:
                //add_subject_to_degree(); TODO
                break;
            default:
                std::cout << OPTION_NOT_FOUND << std::endl;
                pause_program();
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
                pause_program();
        }
        if (!go_back) pause_program();
    }
}

void add_degree()
{
    Degree degree;
    set_degree(degree);
    if (degrees.find(degree) != nullptr)
    {
        std::cout << "Ese programa ya existe" << "\n"; //TODO change to cli
        return;
    }
    degrees.push_front(degree);
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
    if (degrees.find(degree) == nullptr)
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
    set_degree(degree, true);
}

void delete_degree()
{
    Degree degree;
    degree = search_degree();
    if (degree.get_id() == (unsigned)-1) return;
    degrees.remove(degree);
}


void add_subject()
{
    Subject subject;
    set_subject(subject);
    if (subjects.find(subject) != nullptr)
    {
        std::cout << "Esa materia ya existe" << "\n"; //TODO change to cli
        return;
    }
    subjects.push_front(subject);
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

Subject search_subject()
{
    Subject subject;
    subject.set_id(prompt_id());
    if (subjects.find(subject) == nullptr)
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
    set_subject(subject, true);
}

void delete_subject()
{
    Subject subject;
    subject = search_subject();
    if (subject.get_id() == (unsigned)-1) return;
    subjects.remove(subject);
}
