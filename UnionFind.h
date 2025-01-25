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

    HashTable<int, Node> nodes;

public:
    explicit UnionFind();

    // key is key, identifier is like a meta-data for the set (teamId for example)
    void makeset(const int& key);


    // returns the set of the index
    int find(const int& key);

    //which sets to unite. (x <- y)
    void unite(const int& x, const int& y);
};


// #include <unordered_map>
//
// class DisjointSet
// {
// public:
//     struct Node
//     {
//         int parent;
//         int rank;
//     };
//
//     // Create a new set with a single element
//     void makeSet(int element)
//     {
//         if (nodes.find(element) == nodes.end())
//         {
//             nodes[element] = {element, 0}; // Each element is its own parent initially, rank is 0
//         }
//     }
//
//     // Find the root of the set containing the element, with path compression
//     int find(int element)
//     {
//         if (nodes[element].parent != element)
//         {
//             nodes[element].parent = find(nodes[element].parent); // Path compression
//         }
//         return nodes[element].parent;
//     }
//
//     // Union the sets containing two elements, by rank
//     void unionSets(int element1, int element2)
//     {
//         int root1 = find(element1);
//         int root2 = find(element2);
//
//         if (root1 != root2)
//         {
//             if (nodes[root1].rank > nodes[root2].rank)
//             {
//                 nodes[root2].parent = root1;
//             }
//             else if (nodes[root1].rank < nodes[root2].rank)
//             {
//                 nodes[root1].parent = root2;
//             }
//             else
//             {
//                 nodes[root2].parent = root1;
//                 nodes[root1].rank++;
//             }
//         }
//     }
//
// private:
//     std::unordered_map<int, Node> nodes; // Stores nodes indexed by their integer identifier
// };

#endif //DS_WET2_WINTER_2024_2025_UNIONFIND_H
