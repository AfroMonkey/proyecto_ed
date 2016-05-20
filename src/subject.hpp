#ifndef SUBJETC_HPP
#define SUBJETC_HPP

#include <cstring>
#include "config.hpp"

class Subject
{
public:
    Subject();
    bool set_name(char* name);
    
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

#endif
