//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_UNIONFIND_H
#define DS_WET2_WINTER_2024_2025_UNIONFIND_H

template<typename T>
class UnionFind {
private:
    explicit UnionFind(const int &n);

    // key is key
    int makeset(const int& key); 

    // returns the set of the index
    int find(const int &key) const;

    //which sets to unite. (x <- y)
    void unite(const int &x, const int &y);
};


#endif //DS_WET2_WINTER_2024_2025_UNIONFIND_H
