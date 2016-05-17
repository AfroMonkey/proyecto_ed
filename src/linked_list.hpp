#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "linked_list_iterator.hpp"

template <typename T>
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

template <typename T>
linked_list<T>::linked_list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
linked_list<T>::~linked_list()
{
    clear();
}

template <typename T>
size_t linked_list<T>::size() const
{
    return size_;
}

template <typename T>
bool linked_list<T>::empty() const
{
    return head_ == nullptr;
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::at(long index)
{
    // TODO: add exception
    // if (index >= size_) // throw IndexOutOfBounds
    long l = 0;
    for (iterator it = begin(); it != end(); ++it, ++l)
    {
        if (l == index)
        {
            return it;
        }
    }
    return iterator(); // remove this
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::begin()
{
    return iterator(head_);
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::end()
{
    return iterator();
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::find(const T& value)
{
    iterator it;
    for (it = begin(); it != end(); ++it)
    {
        if (*it == value) break;
    }
    return it;
}

template <typename T>
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
        head_->prev_ = new_node;
        head_ = new_node;
    }
    ++size_;
}

template <typename T>
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
        tail_->next_ = new_node;
        tail_ = new_node;
    }
    ++size_;
}

template <typename T>
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
            ++size_;
            break;
        }
    }
}

template <typename T>
void linked_list<T>::erase(iterator index)
{
    if (index.it_ == nullptr) return;
    if (index.it_ == head_)
    {
        head_ = index.it_->next_;
        if (index.it_->next_) index.it_->next_->prev_ = nullptr;
        destroy_node(index.it_);
    }

    else if (index.it_ == tail_)
    {
        tail_ = index.it_->prev_;
        if (index.it_->prev_) index.it_->prev_->next_ = nullptr;
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
    --size_;
}

template <typename T>
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

template <typename T>
void linked_list<T>::clear()
{
    while(!empty())
    {
        erase(begin());
    }
}

template <typename T>
typename linked_list<T>::node* linked_list<T>::construct_node(const T& value)
{
    node* new_node = new node(value);
    // check for correct allocation or throw
    return new_node;
}

template <typename T>
void linked_list<T>::destroy_node(node* old_node)
{
    delete old_node;
}

#endif
