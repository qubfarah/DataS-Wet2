//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_HASHTABLE_H
#define DS_WET2_WINTER_2024_2025_HASHTABLE_H

#include <functional>
#include <memory>
#include <ctime>

#include "DoubleLinkedList.h"

using namespace std;

template<typename TKey, typename TValue>
class HashTable : public enable_shared_from_this<HashTable<TKey, TValue> > {
    const float MAX_LOAD_FACTOR = 0.75;

    class Pair {
    public:
        TKey key;
        shared_ptr<TValue> value;

        Pair(TKey key, shared_ptr<TValue> value): key(key), value(value) {
        }
    };

    using TableItem = DoubleLinkedList<shared_ptr<Pair> >;
    using Table = TableItem;

    Table *table;

    int tableSize;
    int size;

    int hash_a;
    int hash_b;

    int hash(const TKey &key) const {
        return (hash_a * key + hash_b) % tableSize;
    }

    void resize() {
        auto oldSize = tableSize;
        tableSize *= 2;
        auto newTable = new Table[tableSize];

        size = 0;
        for (int i = 0; i < oldSize; i++) {
            for (const shared_ptr<Pair> &pair: table[i]) {
                m_insert(newTable, pair);
            }
        }

        // free previous data;
        delete[] table;

        table = newTable;
    }


    void m_insert(Table *table, const shared_ptr<Pair> &pair) {
        int hashKey = hash(pair->key);

        table[hashKey].insert(pair);

        size++;
    }

public:
    HashTable() : tableSize(10), size(0) {
        table = new Table[tableSize];

        // Seed for random number generation
        std::srand(std::time(nullptr));
        // Generate random coefficients a and b
        hash_a = std::rand() % tableSize + 1; // a should be non-zero
        hash_b = std::rand() % tableSize;
        // hash_a = 5;
        // hash_b = 1;
    }

    ~HashTable() {
        delete[] table;
    }


    void insert(const TKey &key, const TValue &value) {
        shared_ptr<TValue> value_ptr = make_shared<TValue>(value);

        insert(key, value_ptr);
    }

    void insert(const TKey &key, shared_ptr<TValue> value_ptr) {
        // resize hash table
        if (size >= tableSize * MAX_LOAD_FACTOR) {
            resize();
        }

        shared_ptr<Pair> pair = make_shared<Pair>(key, value_ptr);

        m_insert(table, pair);
    }

    bool exists(const TKey &key) {
        return search(key) != nullptr;
    }

    shared_ptr<TValue> search(const TKey &key) const {
        int hashKey = hash(key);

        TableItem list = table[hashKey];

        for (const auto &pair: list) {
            if (pair->key == key) return pair->value;
        }

        return nullptr;
    }

    void upsert(const TKey &key, const TValue &value) {
        auto ptr = search(key);
        if (ptr == nullptr) {
            return insert(key, value);
        }
        //update
        *ptr = value;
    }

    const TValue &operator [](const TKey &key) const {
        return *search(key);
    }

    TValue &operator [](const TKey &key) {
        return *search(key);
    }

    float loadFactor() const {
        return (float) size / (float) tableSize;
    }
};


// class H2
// {
// public:
//     HashTable();
//
//     ~HashTable();
//
//     void insert(const TKey &key, const TValue &value);
//
//     bool exists(const TKey &key);
//
//     shared_ptr<TValue> search(const TKey &key) const;
//
//     TValue & operator [](const TKey &key);
//
//     float loadFactor() const;
// };

#endif //DS_WET2_WINTER_2024_2025_HASHTABLE_H
