//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_UNIONFIND_H
#define DS_WET2_WINTER_2024_2025_UNIONFIND_H

#include "HashTable.h"

class UnionFind
{
private:
    struct Node
    {
        int parent;
        int rank;
    };

    HashTable<Node> nodes;

public:
    explicit UnionFind();

    // key is key, identifier is like a meta-data for the set (teamId for example)
    int makeset(const int& key);


    // returns the set of the index
    int find(const int& key);

    //which sets to unite. (x <- y)
    void unite(const int& x, const int& y);
};

#endif //DS_WET2_WINTER_2024_2025_UNIONFIND_H
