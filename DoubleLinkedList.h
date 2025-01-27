//
// Created by jamal on 24/01/2025.
//

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdexcept>
#include <memory>

using namespace std;

// the linked list owns the items.
// (copies the values)

template <typename T>
class DoubleLinkedList
{
private:
    struct Node : public enable_shared_from_this<Node>
    {
        shared_ptr<Node> next;
        weak_ptr<Node> previous;


        T data;

        Node(T data, shared_ptr<Node> next) : next(next), previous(shared_ptr<Node>(nullptr)), data(move(data))
        {
        };
    };

    shared_ptr<Node> head;

public:
    class Iterator
    {
    public:
        shared_ptr<Node> current;

    public:
        explicit Iterator(shared_ptr<Node> current);

        Iterator& operator++();

        bool operator!=(const Iterator&);

        T& operator*();
    };

    DoubleLinkedList();


    Iterator begin();

    Iterator end();


    void insert(T);
};

template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(shared_ptr<Node> current) : current(current)
{
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++()
{
    if (current == nullptr) throw std::out_of_range("Iterator::operator++()");

    current = current->next;

    return *this;
}

template <typename T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other)
{
    return current != other.current;
}

template <typename T>
T& DoubleLinkedList<T>::Iterator::operator*()
{
    return current->data;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() = default;

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin()
{
    return Iterator(head);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end()
{
    return Iterator(nullptr);
}

template <typename T>
void DoubleLinkedList<T>::insert(T data)
{
    shared_ptr<Node> newNode = make_shared<Node>(data, head);

    if (head != nullptr)
    {
        head->previous = newNode;
    }

    head = newNode;
}


#endif //DOUBLELINKEDLIST_H
