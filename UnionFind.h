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

template<typename T>
class UnionFind {
private:
    struct Node {
        int value;
        Node *head;
        Node *next;
    };

    DynamicArray<Node> A;

public:
    class Set {
    public:
        int identifier;


        class Iterator {
        public:
            // Iterator(const PersonList *list, int index);

            Iterator &operator++();

            bool operator!=(const Iterator &);

            T &operator*();
        };

        Iterator begin();

        Iterator end();

        bool operator ==(const Set &other) const {
            return identifier == other.identifier;
        }
    };

public:
    explicit UnionFind(const int &n);

    // key is key, identifier is like a meta-data for the set (teamId for example)
    Set& makeset(const int& key, const int& identifier); 


    // returns the set of the index
    Set &find(const int &key) const;

    //which sets to unite. (x <- y)
    void unite(const Set &x, const Set &y);
};


#endif //DS_WET2_WINTER_2024_2025_UNIONFIND_H
