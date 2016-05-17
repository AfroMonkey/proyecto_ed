#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LIST_ITERATOR_H

#include "linked_list_node.hpp"

template <typename T>
class linked_list_iterator
{
    template <typename U>
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

template <typename T>
linked_list_iterator<T>::linked_list_iterator(node* it) : it_(it) {}

template <typename T>
T& linked_list_iterator<T>::operator*()
{
    // TODO: add exception
    return it_->data_;
}

template <typename T>
T* linked_list_iterator<T>::operator->()
{
    // TODO: add exception
    return &(operator*());
}

template <typename T>
linked_list_iterator<T>& linked_list_iterator<T>::operator++()
{
    // TODO: add exception
    it_ = it_->next_;
    return *this;
}

template <typename T>
linked_list_iterator<T> linked_list_iterator<T>::operator++(int)
{
    // TODO: add exception
    linked_list_iterator tmp(*this);
    it_ = it_->next_;
    return tmp;
}

template <typename T>
linked_list_iterator<T>& linked_list_iterator<T>::operator--()
{
    // TODO: add exception
    it_ = it_->prev_;
    return *this;
}

template <typename T>
linked_list_iterator<T> linked_list_iterator<T>::operator--(int)
{
    // TODO: add exception
   linked_list_iterator tmp(*this);
    it_ = it_->prev_;
    return tmp;
}

template <typename T>
bool linked_list_iterator<T>::operator==(const linked_list_iterator<T>& other) const
{
    return it_ == other.it_;
}

template <typename T>
bool linked_list_iterator<T>::operator!=(const linked_list_iterator<T>& other) const
{
    return it_ != other.it_;
}

#endif
