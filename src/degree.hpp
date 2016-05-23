#ifndef DEGREE_HPP
#define DEGREE_HPP

#include <fstream>
#include <cstring>
#include "config.hpp"
#include "subject.hpp"
#include "linked_list.hpp"

class Degree
{
public:
    Degree();
    void set_id(const unsigned int& id);
    unsigned int get_id() const;
    bool set_name(const char *name);
    const char* get_name() const;
    void set_credits(const unsigned int& credits);
    unsigned int get_credits() const;
    bool set_division(const char *division);
    const char* get_division() const;
    bool check_credits(); //TODO
    void read(std::ifstream& in);
    void write(std::ofstream& out);
    bool operator==(const Degree& other);
    //linked_list< std::pair<unsigned int, char> > subjects_;
private:
    unsigned int id_;
    char name_[DEGREE_NAME_LENGTH + 1];
    unsigned int credits_;
    char division_[DEGREE_DIVISION_LENGTH + 1];
};

Degree::Degree()
{
    id_ = -1;
    name_[0] = '\x0';
    credits_ = -1;
    division_[0] = '\x0';
}

void Degree::set_id(const unsigned int& id)
{
    id_ = id;
}

unsigned int Degree::get_id() const
{
    return id_;
}

bool Degree::set_name(const char *name)
{
    if (strcmp(name, "") && strlen(name) <= DEGREE_NAME_LENGTH)
    {
        strcpy(name_, name);
        return true;
    }
    return false;
}

const char* Degree::get_name() const
{
    return name_;
}

void Degree::set_credits(const unsigned int& credits)
{
    credits_ = credits;
}

unsigned int Degree::get_credits() const
{
    return credits_;
}

bool Degree::set_division(const char *division)
{
    if (strcmp(division, "") && strlen(division) <= DEGREE_DIVISION_LENGTH)
    {
        strcpy(division_, division);
        return true;
    }
    return false;
}

const char* Degree::get_division() const
{
    return division_;
}

void Degree::read(std::ifstream& in)
{
    in.read((char*) this, sizeof(Degree));
}

void Degree::write(std::ofstream& in)
{
    in.write((char*) this, sizeof(Degree));
}

bool Degree::operator==(const Degree& other)
{
    return id_ == other.id_;
}

#endif
