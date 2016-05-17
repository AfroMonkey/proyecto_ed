#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

template <class T>
class node
{
    template <class U>
    friend class LinkedList;

public:
    node<T>(const T&);

private:
    node<T>* next_;
    node<T>* prev_;
    T        data_;
};

template <class T>
node<T>::node(const T& data) : next_(nullptr), prev_(nullptr), data_(data) {}

#endif