#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LIST_ITERATOR_H

#include "linked_list_node.hpp"

template <class T>
class linked_list_iterator
{
    template <class U>
    friend class linked_list;

    typedef node<T> node;

public:
    linked_list_iterator(node* it = nullptr);
    T& operator*();
    T* operator->();
    linked_list_iterator &operator++();
    linked_list_iterator operator++(int);
    linked_list_iterator &operator--();
    linked_list_iterator operator--(int);
    bool operator==(const linked_list_iterator<T> &other) const;
    bool operator!=(const linked_list_iterator<T> &other) const;
private:
    node* it_;
};

template <class T>
linked_list_iterator<T>::linked_list_iterator(node* it) : it_(it) {}

template <class T>
T& linked_list_iterator<T>::operator*()
{
    return it_->data_;
}

template <class T>
T* linked_list_iterator<T>::operator->()
{
    return &(operator*());
}

template <class T>
linked_list_iterator<T>& linked_list_iterator<T>::operator++()
{
    if (it_) it_ = it_->next_;
    return *this;
}

template <class T>
linked_list_iterator<T> linked_list_iterator<T>::operator++(int)
{
    linked_list_iterator tmp(*this);
    if (it_) it_ = it_->next_;
    return tmp;
}

template <class T>
linked_list_iterator<T>& linked_list_iterator<T>::operator--()
{
    if (it_ != nullptr)
    {
        it_ = it_->prev_;
    }
    return *this;
}

template <class T>
linked_list_iterator<T> linked_list_iterator<T>::operator--(int)
{
    if (it_ != nullptr)
    {
        linked_list_iterator tmp(*this);
        it_ = it_->prev_;
        return tmp;
    }
    return *this;
}

template <class T>
bool linked_list_iterator<T>::operator==(const linked_list_iterator<T>& other) const
{
    return it_ == other.it_;
}

template <class T>
bool linked_list_iterator<T>::operator!=(const linked_list_iterator<T>& other) const
{
    return it_ != other.it_;
}

#endif
