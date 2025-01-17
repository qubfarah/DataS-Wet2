//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_UNIONFIND_H
#define DS_WET2_WINTER_2024_2025_UNIONFIND_H

#include <memory>

#include "DynamicArray.h"

// class _UnionFind
// {
// private:
//     DynamicArray<int> parent;
//     DynamicArray<int> rank;
//
// public:
//     explicit UnionFind(const int& n);
//
//     int find(const int& x) const;
//
//     void unite(const int& x, const int& y);
// };

class UnionFind
{
private:
    struct Node
    {
        int value;
        Node* head;
        Node* next;
    };

    DynamicArray<Node> A;
public:
    class Set
    {

    };
public:
    explicit UnionFind(const int& n);

    // returns the set of the index
    std::shared_ptr<Set> find(const int& x) const;

    void unite(const int& x, const int& y);
};


#endif //DS_WET2_WINTER_2024_2025_UNIONFIND_H
