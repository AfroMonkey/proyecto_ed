
#include <iostream>

#include "cli.hpp"
#include "config.hpp"
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"

void manage_degrees();
void manage_subjects();

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
    bool go_back = false;
    while (!go_back)
    {
        Degree degree;
        display_sec_menu(HEADER_DEGREE);
        switch(get_int())
        {
            case ADD:
                set_degree(degree);
                // Set a degree object and added to the list [DONE]
                break;
            case LIST:
                
                break;
            case SEARCH:
                // Prompt id or data needed, then search in the correspondent file
                // if there's any result, print it
                break;
            case EDIT:
                // Just like search, but giving the posibility of edit the data
                break;
            case DELETE:
                // Search, if found -> delete
                break;
            case GO_BACK:
                go_back = true;
                break;
            default:
                std::cout << OPTION_NOT_FOUND << std::endl;
                pause_program();
        }
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
    }
}
