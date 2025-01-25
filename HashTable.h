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

template <typename TKey, typename TValue>
class HashTable : public enable_shared_from_this<HashTable<TKey, TValue>>
{
    const float MAX_LOAD_FACTOR = 0.75;
    const int PRIME = 997; // a large prime number for hashing

    class Pair
    {
    public:
        TKey key;
        shared_ptr<TValue> value;

        Pair(TKey key, shared_ptr<TValue> value): key(key), value(value)
        {
        }
    };

    using TableItem = DoubleLinkedList<shared_ptr<Pair>>;
    using Table = TableItem;

    Table* table;

    int tableSize;
    int size;

    int hash_a;
    int hash_b;

    int hash(const TKey& key) const
    {
        //Universal hash function
        return ((hash_a * key + hash_b) % PRIME) % tableSize;
    }

    void resize()
    {
        int oldSize = tableSize;
        tableSize *= 2;

         // Generate a new random hash function
        generateHashFunction();
        
        auto newTable = new Table[tableSize];

        size = 0;
        for (int i = 0; i < oldSize; i++)
        {
            for (const shared_ptr<Pair>& pair : table[i])
            {
                m_insert(newTable, pair);
            }
        }

        // free previous data;
        delete[] table;

        table = newTable;
    }


    void m_insert(Table* table, const shared_ptr<Pair>& pair)
    {
        int hashKey = hash(pair->key);

        table[hashKey].insert(pair);

        size++;
    }

    void generateHashFunction()
    {
        hash_a = std::rand() % PRIME + 1; // a should be non-zero
        hash_b = std::rand() % PRIME;
    }

public:
    HashTable() : tableSize(10), size(0)
    {
        table = new Table[tableSize];

        // Seed for random number generation
        std::srand(std::time(nullptr));
    // Generate random coefficients for the hash function
        generateHashFunction();
    }

    ~HashTable()
    {
        delete[] table;
    }


    void insert(const TKey& key, const TValue& value)
    {
        // resize hash table
        if (size >= tableSize * MAX_LOAD_FACTOR)
        {
            resize();
        }

        shared_ptr<TValue> value_ptr = make_shared<TValue>(value);

        shared_ptr<Pair> pair = make_shared<Pair>(key, value_ptr);

        m_insert(table, pair);
    }

    bool exists(const TKey& key)
    {
        return search(key) != nullptr;
    }

    shared_ptr<TValue> search(const TKey& key) const
    {
        int hashKey = hash(key);

        TableItem list = table[hashKey];

        for (const auto& pair : list)
        {
            if (pair->key == key) return pair->value;
        }

        return nullptr;
    }

    const TValue& operator [](const TKey& key) const
    {
        return *search(key);
    }


    // class TValueProxy : public TValue
    // {
    // public:
    //     shared_ptr<HashTable> table;
    //     TKey key;
    //
    //
    //     TValueProxy(shared_ptr<HashTable> table, const TKey& key) : table(table), key(key)
    //     {
    //     }
    //
    //     // acts like lazy-insert
    //     TValueProxy& operator=(const TValue& val)
    //     {
    //         table->insert(key, val);
    //         return *this;
    //     };
    // };


    TValue& operator [](const TKey& key)
    {
        auto result = search(key);
        if (result != nullptr)
        {
            return *result;
        }
        
        TValue default_value{};
        insert(key, default_value);
        return *search(key);
        // TValue val;
        //
        // insert(key, val);
        //
        // return this->operator[](key);
        // return TValueProxy(this->shared_from_this(), key);
    }

    float loadFactor() const
    {
        return (float)size / (float)tableSize;
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
