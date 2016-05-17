#ifndef CAREER_HPP
#define CAREER_HPP

#include "config.hpp"
#include "subject.hpp"

class Career
{
private:
    unsigned int id_;
    char name_[CAREER_NAME_LENGTH + 1];
    unsigned int credits_;
    char division_[CAREER_DIVISION_LENGTH + 1];
    //list<Subject*> basic_subjects_; TODO
    //list<Subject*> language_subjects_; TODO
    //list<Subject*> specialized_subjects_; TODO
public:
    Career();

    bool set_id(unsigned int id);
    unsigned int get_id();
    bool set_name(char *name);
    char* get_name();
    bool set_credits(unsigned int credits);
    unsigned int get_credits();
    bool set_division(char *division);
    char* get_division();

    bool check_credits(); //TODO
};

Career::Career()
{
    id_ = -1;
    name_[0] = '\x0';
    credits_ = -1;
    division_[0] = '\x0';
}

bool Career::set_id(unsigned int id)
{
    if (id >= 0)
    {
        id_ = id;
        return true;
    }
    return false;
}

unsigned int Career::get_id()
{
    return id_;
}

bool Career::set_name(char *name)
{
    if (name[0] != '\x0')
    {
        for (int i = 0; name[i]; i++)
        {
            name_[i] = name[i];
        }
        return true;
    }
    return false;
}

char* Career::get_name()
{
    return name_;
}

bool Career::set_credits(unsigned int credits)
{
    if (credits >= 0)
    {
        credits_ = credits;
        return true;
    }
    return false;
}

unsigned int Career::get_credits()
{
    return credits_;
}

bool Career::set_division(char *division)
{
    if (division[0] != '\x0')
    {
        for (int i = 0; division[i]; i++)
        {
            division_[i] = division[i];
        }
        return true;
    }
    return false;
}

char* Career::get_division()
{
    return division_;
}

#endif
