#ifndef SUBJETC_HPP
#define SUBJETC_HPP

#include <cstring>
#include "config.hpp"

class Subject
{
public:
    Subject();

    void set_id(unsigned int id);
    const unsigned int get_id();
    bool set_name(char* name);
    const char* get_name();
    void set_credits(unsigned int credits);
    const unsigned int get_credits();

private:
    unsigned int id_;
    char name_[SUBJECT_NAME_LENGTH + 1];
    unsigned int credits_;
};

Subject::Subject()
{
    id_ = -1;
    name_[0] = '\x0';
    credits_ = -1;
}

bool Subject::set_name(char* name)
{
    if (strlen(name) <= DEGREE_NAME_LENGTH)
    {
        strcpy(name_, name);
        return true;
    }
    return false;
}

const char* Subject::get_name()
{
    return name_;
}

void Subject::set_id(unsigned int id)
{
    id_ = id;
}

const unsigned int Subject::get_id()
{
    return id_;
}

void Subject::set_credits(unsigned int credits)
{
    credits_ = credits;
}

const unsigned int Subject::get_credits()
{
    return credits_;
}

#endif
