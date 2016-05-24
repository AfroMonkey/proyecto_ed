#ifndef RELATION_HPP
#define RELATION_HPP

#include <fstream>
#include "config.hpp"

class Relation
{
private:
    unsigned int degree_id_;
    unsigned int subject_id_;
    char type_;
public:

    Relation();
    Relation(unsigned int degree_id, unsigned int subject_id, char type);

    void set_degree_id(unsigned int degree_id);
    unsigned int get_degree_id() const;
    void set_subject_id(unsigned int subject_id);
    unsigned int get_subject_id() const;
    bool set_type(char type);
    char get_type() const;

    void write(std::ofstream& in);
    void read(std::ifstream& in);
    bool operator==(const Relation& other);
    bool operator<(const Relation& other) const;
};

Relation::Relation()
{
    degree_id_ = -1;
    subject_id_ = -1;
    type_ = '\x0';
}

Relation::Relation(unsigned int degree_id, unsigned int subject_id, char type)
{
    degree_id_ = degree_id;
    subject_id_ = subject_id;
    type_ = type;
}

void Relation::set_degree_id(unsigned int degree_id)
{
    degree_id_ = degree_id;
}

unsigned int Relation::get_degree_id() const
{
    return degree_id_;
}

void Relation::set_subject_id(unsigned int subject_id)
{
    subject_id_ = subject_id;
}

unsigned int Relation::get_subject_id() const
{
    return subject_id_;
}

bool Relation::set_type(char type)
{
    if (type != 'b' && type != 'e' && type != 'l') return false;
    type_ = type;
    return true;
}

char Relation::get_type() const
{
    return type_;
}


void Relation::read(std::ifstream& in)
{
    in.read((char*) this, sizeof(Relation));
}

void Relation::write(std::ofstream& in)
{
    in.write((char*) this, sizeof(Relation));
}

bool Relation::operator==(const Relation& other)
{
    return degree_id_ == other.degree_id_ && subject_id_ == other.subject_id_;
}

bool Relation::operator<(const Relation& b) const
{
    if (degree_id_ < b.get_degree_id()) return true;
    if (degree_id_ > b.get_degree_id()) return false;
    if (type_ < b.get_type()) return true;
    if (type_ > b.get_type()) return false;
    return subject_id_ < b.get_subject_id();
}

#endif
