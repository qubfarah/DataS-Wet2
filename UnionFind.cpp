//
// Created by Farah Qub on 17/01/2025.
//

#include "UnionFind.h"

// UnionFind::UnionFind(const int& n)
// {
//     for (int i = 0; i < n; ++i)
//     {
//         parent.push_back(i);
//         rank.push_back(0);
//     }
// }
//
// }
//
// int UnionFind::find(const int& x) const
// {
//     if (parent[x] != x)
//     {
//         return find(parent[x]); // Path compression
//     }
//     return parent[x];
// }
//
// void UnionFind::unite(const int& x, const int& y)
// {
//     int rootX = find(x);
//     int rootY = find(y);
//     if (rootX != rootY)
//     {
//         if (rank[rootX] > rank[rootY])
//         {
//             parent[rootY] = rootX;
//         }
//         else if (rank[rootX] < rank[rootY])
//         {
//             parent[rootX] = rootY;
//         }
//         else
//         {
//             parent[rootY] = rootX;
//             rank[rootX]++;
//         }
//     }
};

UnionFind::UnionFind(const int& n)
{
}

int UnionFind::find(const int& x) const
{
}

void UnionFind::unite(const int& x, const int& y)
{
}
