#ifndef SUBJETC_HPP
#define SUBJETC_HPP

#include "config.hpp"

class Subject
{
private:
    unsigned int id_;
    char name_[SUBJECT_NAME_LENGTH + 1];
    unsigned int credits_;
public:
    Subject();

    bool set_id(unsigned int id);
    unsigned int get_id();
    bool set_name(char* name);
    char* get_name();
    bool set_credits(unsigned int credits);
    unsigned int get_credits();
};

Subject::Subject()
{
    id_ = -1;
    name_[0] = '\x0';
    credits_ = -1;
}

bool Subject::set_id(unsigned int id)
{
    if (id >= 0)
    {
        id_ = id;
        return true;
    }
    return false;
}

unsigned int Subject::get_id()
{
    return id_;
}

bool Subject::set_name(char* name)
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

char* Subject::get_name()
{
    return name_;
}

bool Subject::set_credits(unsigned int credits)
{
    if (credits >= 0)
    {
        credits_ = credits;
        return true;
    }
    return false;
}

unsigned int Subject::get_credits()
{
    return credits_;
}

#endif
