//
// Created by Farah Qub on 17/01/2025.
//
#include "UnionFind.h"

UnionFind::UnionFind() {
}

int UnionFind::makeset(const int &key) {
    if (!nodes.exists(key)) {
        nodes.insert(key, {key, 0});
        return key;
    }
    return key;
}

int UnionFind::find(const int &key) {
    if (nodes[key].parent != key) {
        nodes[key].parent = find(nodes[key].parent); // Path compression
    }
    return nodes[key].parent;
}

void UnionFind::unite(const int &x, const int &y) {
    int root1 = find(x);
    int root2 = find(y);

    if (root1 != root2) {
        if (nodes[root1].rank > nodes[root2].rank) {
            nodes[root2].parent = root1;
        } else if (nodes[root1].rank < nodes[root2].rank) {
            nodes[root1].parent = root2;
        } else {
            nodes[root2].parent = root1;
            nodes[root1].rank++;
        }
    }
}
