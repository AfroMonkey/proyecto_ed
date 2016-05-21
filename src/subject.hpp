#ifndef SUBJETC_HPP
#define SUBJETC_HPP

#include <cstring>
#include "config.hpp"

class Subject
{
public:
    Subject();

    void set_id(const unsigned int& id);
    unsigned int get_id() const;
    bool set_name(const char* name);
    const char* get_name() const;
    void set_credits(const unsigned int& credits);
    unsigned int get_credits() const;

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

void Subject::set_id(const unsigned int& id)
{
    id_ = id;
}

unsigned int Subject::get_id() const
{
    return id_;
}

bool Subject::set_name(const char* name)
{
    if (strcmp(name, "") && strlen(name) <= DEGREE_NAME_LENGTH)
    {
        strcpy(name_, name);
        return true;
    }
    return false;
}

const char* Subject::get_name() const
{
    return name_;
}

void Subject::set_credits(const unsigned int& credits)
{
    credits_ = credits;
}

unsigned int Subject::get_credits() const
{
    return credits_;
}

#endif
