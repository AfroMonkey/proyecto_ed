#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "linked_list_iterator.hpp"

template <class T>
class linked_list
{
public:
    typedef linked_list_iterator<T> iterator;

    linked_list();
    ~linked_list();
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
    void insert(iterator, const T&);
    void erase(iterator);
    void remove(const T&);
    void clear();

private:
    typedef node<T> node;
    node* construct_node(const T&);
    void  destroy_node(node*);

    node*  head_;
    node*  tail_;
    size_t size_;
};

template <class T>
linked_list<T>::linked_list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <class T>
linked_list<T>::~linked_list()
{
    clear();
}

template <class T>
size_t linked_list<T>::size() const
{
    return size_;
}

template <class T>
bool linked_list<T>::empty() const
{
    return head_ == nullptr;
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::at(long index)
{
    // if (index >= size_) // throw IndexOutOfBounds
    long l = 0;
    for (iterator it = begin(); it != end(); ++it, ++l)
    {
        if (l == index)
        {
            return it;
        }
    }
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

template <class T>
typename linked_list<T>::iterator linked_list<T>::find(const T& value)
{
    iterator it;
    for (it = begin(); it != end(); ++it)
    {
        if (*it == value) break;
    }
    return it;
}

template <class T>
void linked_list<T>::push_front(const T& value)
{
    node* new_node = construct_node(value);
    if (empty())
    {
        head_ = tail_ = new_node;
        new_node->next_ = nullptr;
        new_node->prev_ = nullptr;
    }
    else
    {
        new_node->next_ = head_;
        new_node->prev_ = nullptr;
        head_ = new_node;
    }
}

template <class T>
void linked_list<T>::push_back(const T& value)
{
    node* new_node = construct_node(value);
    if (empty())
    {
        head_ = tail_ = new_node;
        new_node->next_ = nullptr;
        new_node->prev_ = nullptr;
    }
    else
    {
        new_node->next_ = nullptr;
        new_node->prev_ = tail_;
        tail_ = new_node;
    }
}

template <class T>
void linked_list<T>::insert(iterator index, const T& value)
{
    // if (index >= size_) // throw IndexOutOfBounds
    for (iterator it = begin(); it != end(); ++it)
    {
        if (it == index)
        {
            if (it.it_ == head_) push_front(value);
            else
            {
                node* new_node = construct_node(value);
                new_node->next_ = it.it_;
                new_node->prev_ = it.it_->prev_;
                it.it_->prev_->next_ = new_node;
                it.it_->prev_ = new_node;
            }
            break;
        }
    }
}

template <class T>
void linked_list<T>::erase(iterator index)
{
    if (index.it_ == nullptr) return;
    if (index.it_ == head_)
    {
        head_ = index.it_->next_;
        index.it_->next_->prev_ = nullptr;
        destroy_node(index.it_);
    }

    else if (index.it_ == tail_)
    {
        tail_ = index.it_->prev_;
        index.it_->prev_->next_ = nullptr;
        destroy_node(index.it_);
    }

    else
    {
        for (iterator it = begin(); it != end(); ++it)
        {
            if (it == index)
            {
                it.it_->prev_->next_ = it.it_->next_;
                it.it_->next_->prev_ = it.it_->prev_;
                destroy_node(it.it_);
                break;
            }
        }
    }
}

template <class T>
void linked_list<T>::remove(const T& value)
{
    for (iterator it = begin(); it != end(); ++it)
    {
        if (*it == value)
        {
            erase(it);
        }
    }
}

template <class T>
void linked_list<T>::clear()
{
    for (iterator it = begin(); it != end(); ++it)
    {
        erase(it);
    }
}

template <class T>
typename linked_list<T>::node* linked_list<T>::construct_node(const T& value)
{
    node* new_node = new node(value);
    // check for correct allocation or throw
    ++size_;
    return new_node;
}

template <class T>
void linked_list<T>::destroy_node(node* old_node)
{
    delete old_node;
    --size_;
}

#endif
