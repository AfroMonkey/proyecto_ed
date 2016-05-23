
#include <cstdio>
#include <fstream>
#include <iostream>

#include "cli.hpp"
#include "config.hpp"
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"

void manage_degrees();
void manage_subjects();

int search_degree(int id);

linked_list<Subject> ls_common_part;
linked_list<Subject> ls_degree_required;
linked_list<Subject> ls_foreign_language;

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
    int p;
    bool go_back = false;
    while (!go_back)
    {
        Degree degree;
        std::ifstream in;
        std::ofstream out;
        display_sec_menu(HEADER_DEGREE);
        switch(get_int())
        {
            case ADD:
                set_degree(degree);
                out.open(DEGREES_FILE, std::ios::app);
                degree.write(out);
                out.close();
                break;
            case LIST:
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
                break;
            case SEARCH:
                p = search_degree(prompt_id());
                if (p == -1)
                {
                    record_not_found();
                    break;
                }
                in.open(DEGREES_FILE);
                in.seekg(p, std::ios::beg);
                degree.read(in);
                in.close();
                print_degree_header();
                print_degree(degree);
                break;
            case EDIT:
                p = search_degree(prompt_id());
                if (p == -1)
                {
                    record_not_found();
                    break;
                }
                in.open(DEGREES_FILE);
                in.seekg(p, std::ios::beg);
                degree.read(in);
                in.close();
                print_degree_header();
                print_degree(degree);
                set_degree(degree, true);
                out.open(DEGREES_FILE, std::ios::out | std::ios::in);
                out.seekp(p, std::ios::beg);
                degree.write(out);
                out.close();
                break;
            case DELETE:
                p = search_degree(prompt_id());
                if (p == -1)
                {
                    record_not_found();
                    break;
                }
                in.open(DEGREES_FILE);
                out.open(TEMPORAL_FILE, std::ios::out);
                while(in.get() != EOF)
                {
                    in.seekg(-1, std::ios::cur);
                    if (in.tellg() == p) in.seekg(sizeof(Degree), std::ios::cur);
                    degree.read(in);
                    degree.write(out);
                }
                in.close();
                out.close();
                std::remove(DEGREES_FILE.c_str());
                std::rename(TEMPORAL_FILE.c_str(), DEGREES_FILE.c_str());
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

void manage_subjects()
{
    bool go_back = false;
    while (!go_back)
    {
        display_sec_menu(HEADER_SUBJECT);
        switch(get_int())
        {
            case ADD:
                break;
            case LIST:
                break;
            case SEARCH:
                break;
            case EDIT:
                break;
            case DELETE:
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

int search_degree(int id)
{
    Degree degree;
    std::ifstream in;
    in.open(DEGREES_FILE);
    while(in.get() != EOF)
    {
        in.seekg(-1, std::ios::cur);
        int p = in.tellg();
        degree.read(in);
        if (degree.get_id() == id)
        {
            return p;
        }
    }
    return -1;
}
