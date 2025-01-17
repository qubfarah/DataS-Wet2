//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_HASHTABLE_H
#define DS_WET2_WINTER_2024_2025_HASHTABLE_H

#endif //DS_WET2_WINTER_2024_2025_HASHTABLE_H

template <typename Key, typename Value>
class HashTable {
private:
    struct Node {};

    Node** table;
    int capacity;
    int size;

    int hash(const Key& key) const {}

public:
    HashTable(int cap = 10) : capacity(cap), size(0) {}

    ~HashTable() {}

    bool insert(const Key& key, const Value& value) {}

    bool find(const Key& key, Value& value) const {}

    bool remove(const Key& key) {}
};
