
#include <cstdio>
#include <fstream>
#include <iostream>

#include "cli.hpp"
#include "config.hpp"
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"
#include "relation.hpp"

void manage_degrees();
void manage_subjects();

void add_degree();
void list_degrees();
Degree search_degree();
void edit_degree();
void delete_degree();
void add_subject_to_degree();
int find_degree(unsigned int id);
int get_degree_address(Degree degree);

void add_subject();
void list_subject();
Subject search_subject();
void edit_subject();
void delete_subject();
int find_subject(unsigned int id);

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
                add_subject_to_degree();
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
                list_subject();
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
    std::ofstream out;
    set_degree(degree);
    out.open(DEGREES_FILE, std::ios::app);
    degree.write(out);
    out.close();
}

void list_degrees()
{
    Degree degree;
    std::ifstream in;
    in.open(DEGREES_FILE);
    clear_screen();
    print_degree_header(true);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        degree.read(in);
        print_degree(degree);
    }
    in.close();
    std::cout << std::endl;
}

Degree search_degree()
{
    Degree degree, empty;
    std::ifstream in;
    int p = find_degree(prompt_id());
    if (p == -1)
    {
        record_not_found();
        return empty;
    }
    in.open(DEGREES_FILE);
    in.seekg(p, std::ios::beg);
    degree.read(in);
    in.close();
    std::cout << std::endl;
    print_degree_header();
    print_degree(degree);
    std::cout << std::endl;
    return degree;
}

void edit_degree()
{
    int p;
    Degree degree;
    std::ofstream out;
    degree = search_degree();
    if (degree.get_id() == (unsigned)-1) return;
    p = find_degree(degree.get_id());
    set_degree(degree, true);
    out.open(DEGREES_FILE, std::ios::out | std::ios::in);
    out.seekp(p, std::ios::beg);
    degree.write(out);
    out.close();
}

void delete_degree()
{
    Degree degree, holder;
    std::ifstream in;
    std::ofstream out;
    degree = search_degree();
    if (degree.get_id() == (unsigned)-1) return;
    in.open(DEGREES_FILE);
    out.open(TEMPORAL_FILE, std::ios::out);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        holder.read(in);
        if (holder == degree) continue;
        holder.write(out);
    }
    in.close();
    out.close();
    std::remove(DEGREES_FILE.c_str());
    std::rename(TEMPORAL_FILE.c_str(), DEGREES_FILE.c_str());
}

int find_relation(const Relation &relation)
{
    Relation aux;
    std::ifstream in;
    in.open(RELATIONS_FILE);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        aux.read(in);
        if (aux == relation)
        {
            int p = in.tellg();
            return p;
        }
    }
    in.close();
    return -1;
}

Relation search_relation()
{
    Relation relation, empty;
    std::ifstream in;
    set_relation(relation);
    int p = find_relation(relation);
    if (p == -1)
    {
        record_not_found();
        return empty;
    }
    in.open(DEGREES_FILE);
    in.seekg(p, std::ios::beg);
    relation.read(in);
    in.close();
    std::cout << std::endl;
    print_relation_header();
    print_relation(relation);
    std::cout << std::endl;
    return relation;
}

void add_subject_to_degree()
{
    Degree degree;
    std::ofstream out;
    Relation relation;
    relation = search_relation();
    //TODO Validate the degree and subject
    if (relation.get_degree_id() != (unsigned)-1)
    {
        std::cout << "Esa relacion ya existe, eliminela antes" << "\n"; //TODO move to cli
        return;
    }
    out.open(RELATIONS_FILE, std::ios::app);
    degree.write(out);
    out.close();
}

int find_degree(unsigned int id)
{
    Degree degree;
    std::ifstream in;
    in.open(DEGREES_FILE);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        degree.read(in);
        if (degree.get_id() == id)
        {
            int p = in.tellg();
            return p;
        }
    }
    in.close();
    return -1;
}

void add_subject()
{
    Subject subject;
    std::ofstream out;
    set_subject(subject);
    out.open(SUBJECTS_FILE, std::ios::app);
    subject.write(out);
    out.close();
}

void list_subject()
{
    Subject subject;
    std::ifstream in;
    in.open(SUBJECTS_FILE);
    clear_screen();
    print_subject_header(true);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        subject.read(in);
        print_subject(subject);
    }
    in.close();
    std::cout << std::endl;
}

Subject search_subject()
{
    Subject subject, empty;
    std::ifstream in;
    int p = find_subject(prompt_id());
    if (p == -1)
    {
        record_not_found();
        return empty;
    }
    in.open(SUBJECTS_FILE);
    in.seekg(p, std::ios::beg);
    subject.read(in);
    in.close();
    std::cout << std::endl;
    print_subject_header();
    print_subject(subject);
    std::cout << std::endl;
    return subject;
}

void edit_subject()
{
    int p;
    Subject subject;
    std::ofstream out;
    subject = search_subject();
    if (subject.get_id() == (unsigned)-1) return;
    p = find_subject(subject.get_id());
    set_subject(subject, true);
    out.open(SUBJECTS_FILE, std::ios::out | std::ios::in);
    out.seekp(p, std::ios::beg);
    subject.write(out);
    out.close();
}

void delete_subject()
{
    Subject subject, holder;
    std::ifstream in;
    std::ofstream out;
    subject = search_subject();
    if (subject.get_id() == (unsigned)-1) return;
    in.open(SUBJECTS_FILE);
    out.open(TEMPORAL_FILE, std::ios::out);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        holder.read(in);
        if (holder == subject) continue;
        holder.write(out);
    }
    in.close();
    out.close();
    std::remove(SUBJECTS_FILE.c_str());
    std::rename(TEMPORAL_FILE.c_str(), SUBJECTS_FILE.c_str());
}

int find_subject(unsigned int id)
{
    Subject degree;
    std::ifstream in;
    in.open(SUBJECTS_FILE);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        degree.read(in);
        if (degree.get_id() == id)
        {
            int p = in.tellg();
            return p;
        }
    }
    in.close();
    return -1;
}
