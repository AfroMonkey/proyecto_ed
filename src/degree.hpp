#ifndef DEGREE_HPP
#define DEGREE_HPP

#include <cstring>
#include "config.hpp"
#include "subject.hpp"

class Degree
{
public:
    Degree();
    bool set_name(char *name);
    bool set_division(char *division);
    bool check_credits(); //TODO

private:
    unsigned int id_;
    char name_[DEGREE_NAME_LENGTH + 1];
    unsigned int credits_;
    char division_[DEGREE_DIVISION_LENGTH + 1];
    //list<Subject*> basic_subjects_; TODO
    //list<Subject*> language_subjects_; TODO
    //list<Subject*> specialized_subjects_; TODO
};

Degree::Degree()
{
    id_ = -1;
    name_[0] = '\x0';
    credits_ = -1;
    division_[0] = '\x0';
}

bool Degree::set_name(char *name)
{
    if (strlen(name) <= DEGREE_NAME_LENGTH)
    {
        strcpy(name_, name);
        return false;
    }
    return false;
}

bool Degree::set_division(char *division)
{
    if (strlen(division) <= DEGREE_DIVISION_LENGTH)
    {
        strcpy(division_, division);
        return false;
    }
    return false;
}

#endif
