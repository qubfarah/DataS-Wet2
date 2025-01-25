//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_UNIONFIND_H
#define DS_WET2_WINTER_2024_2025_UNIONFIND_H

#include <memory>
#include <HashTable.h>
#include "DynamicArray.h"

template <typename T>
 class UnionFind
 {
 public:
     explicit UnionFind();

     T* find(T* object);

     void unite(T* object1, T* object2);
 };


#endif //DS_WET2_WINTER_2024_2025_UNIONFIND_H
