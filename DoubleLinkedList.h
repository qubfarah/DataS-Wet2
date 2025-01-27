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

        Node(T data, shared_ptr<Node> next) : next(next),
                                              data(move(data))
        {
            resetPrevious();
        };

        void resetPrevious()
        {
            previous = shared_ptr<Node>(nullptr);
        }
    };

    shared_ptr<Node> head;

public:
    class NodeToken
    {
    private:
        shared_ptr<Node> node;

    public:
        NodeToken(shared_ptr<Node> node);
        NodeToken(std::nullptr_t p);

        bool operator==(const T &) const;

        void remove();

        T &operator*() const;
    };

public:
    class Iterator
    {
    public:
        shared_ptr<Node> current;

    public:
        explicit Iterator(shared_ptr<Node> current);

        Iterator &operator++();

        bool operator!=(const Iterator &);

        NodeToken operator*();
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
typename DoubleLinkedList<T>::Iterator &DoubleLinkedList<T>::Iterator::operator++()
{
    if (current == nullptr)
        throw std::out_of_range("Iterator::operator++()");

    current = current->next;

    return *this;
}

template <typename T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator &other)
{
    return current != other.current;
}

template <typename T>
typename DoubleLinkedList<T>::NodeToken DoubleLinkedList<T>::Iterator::operator*()
{
    return current;
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

template <typename T>
DoubleLinkedList<T>::NodeToken::NodeToken(shared_ptr<Node> node) : node(node)
{
}

template <typename T>
DoubleLinkedList<T>::NodeToken::NodeToken(std::nullptr_t p) : node(p)
{
}

template <typename T>
bool DoubleLinkedList<T>::NodeToken::operator==(const T &value) const
{
    return this->operator*() == value;
}

template <typename T>
void DoubleLinkedList<T>::NodeToken::remove()
{
    auto next = node->next;

    if (auto previous = node->previous.lock())
    {
        previous->next = next;
        if (next != nullptr)
        {
            next->previous = previous;
        }
    }
    else if (next != nullptr)
    {
        next->resetPrevious();
    }

    node->next = nullptr;
    node->resetPrevious();
}

template <typename T>
T &DoubleLinkedList<T>::NodeToken::operator*() const
{
    return node->data;
}

#endif // DOUBLELINKEDLIST_H
