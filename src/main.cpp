
#include <iostream>

#include "cli.hpp"
#include "config.hpp"
#include "degree.hpp"
#include "subject.hpp"
#include "linked_list.hpp"

void manage_degrees();
void manage_subjects();

int main()
{
    bool exit_program = false;
    while (!exit_program)
    {
        display_main_menu();
        switch(get_positive_int()) // Quiza una funcion derivada de get_int que sea especifica para opciones (?)
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
                std::cout << OPTION_NOT_FOUND << std::endl;
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
        display_sec_menu(DEGREE);
        switch(get_positive_int())
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

void manage_subjects()
{
    bool go_back = false;
    while (!go_back)
    {
        display_sec_menu(SUBJECT);
        switch(get_positive_int())
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
