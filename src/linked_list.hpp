#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "linked_list_iterator.hpp"

template <class T>
class linked_list
{
    typedef node<T> node;
    typedef linked_list_iterator<T> iterator;
public:
    linked_list();
    ~linked_list() {}
    // accessors
    size_t   size() const;
    bool     empty() const;
    iterator at(long);
    iterator begin();
    iterator end();
    iterator find(const T&);
    // modifiers
    void push_front(const T&);
    void push_back(const T&);
    void insert(const node*, const T&);
    void erase(const node*);
    void remove(const T&);

private:
    node*  head_;
    node*  tail_;
    size_t size_;
};

template <class T>
linked_list<T>::linked_list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <class T>
size_t linked_list<T>::size() const
{
    return size_;
}

template <class T>
bool linked_list<T>::empty() const
{
    return size_ == 0;
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::begin()
{
    return iterator(head_);
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::end()
{
    return iterator();
}

#endif
