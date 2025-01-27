//
// Created by jamal on 21/01/2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <functional>
#include <memory>
#include <ctime>

#include "DoubleLinkedList.h"

using namespace std;

// TODO: split header def from impl
template <typename TValue>
class HashTable : public enable_shared_from_this<HashTable<TValue>>
{
    // although at first created with TKey param, the hashtable thoughout the application
    // only used TKey = int. therefore removing unnessary param.
    using TKey = int;

    const float MAX_LOAD_FACTOR = 0.75;

    class Pair
    {
    public:
        TKey key;
        shared_ptr<TValue> value;

        Pair(TKey key, shared_ptr<TValue> value) : key(key), value(value)
        {
        }
    };

    using TableItem = DoubleLinkedList<shared_ptr<Pair>>;

    using Table = TableItem;

    Table *table;

    int tableSize;
    int size;

    class HashFunction
    {
    private:
        int hash_a;
        int hash_b;
        int m;

    public:
        HashFunction(const int &m) : m(m)
        {
            // Seed for random number generation
            std::srand(std::time(nullptr));
            // Generate random coefficients a and b

            hash_a = std::rand() % m + 1; // a should be non-zero
            hash_b = std::rand() % m;
        }

        int operator()(const int &key) const
        {
            return (hash_a * key + hash_b) % m;
        }

        void recalibrate(const int &newSize)
        {
            m = newSize;
        }
    };

    HashFunction hash;

    void resize()
    {
        auto newSize = tableSize * 2;

        auto newTable = new Table[newSize];

        hash.recalibrate(newSize);

        size = 0;
        for (int i = 0; i < tableSize; i++)
        {
            for (const auto &token : table[i])
            {
                const shared_ptr<Pair> &pair = *token;

                m_insert(newTable, pair);
            }
        }

        tableSize = newSize;

        // free previous data;
        delete[] table;

        table = newTable;
    }

    void m_insert(Table *table, const shared_ptr<Pair> &pair)
    {
        int hashKey = hash(pair->key);

        table[hashKey].insert(pair);

        size++;
    }

    typename TableItem::NodeToken m_search(const TKey &key) const
    {
        int hashKey = hash(key);

        TableItem list = table[hashKey];

        for (typename TableItem::NodeToken token : list)
        {
            auto pair = *token;
            if (pair->key == key)
                // make sure it returns a copy not a ref
                return token;
        }

        // this converts to token with empty node
        return nullptr;
    }

    shared_ptr<Pair> m_find(const TKey &key) const
    {
        auto token = m_search(key);
        if (token == nullptr)
            return nullptr;

        return *token;
    }

    void m_remove(typename TableItem::NodeToken &token)
    {
        token.remove();
    }

public:
    HashTable() : tableSize(10), size(0), hash(tableSize)
    {
        table = new Table[tableSize];
    }

    ~HashTable()
    {
        delete[] table;
    }

    void insert(const TKey &key, const TValue &value)
    {
        shared_ptr<TValue> value_ptr = make_shared<TValue>(value);

        insert(key, value_ptr);
    }

    void insert(const TKey &key, shared_ptr<TValue> value_ptr)
    {
        // resize hash table
        if (size >= tableSize * MAX_LOAD_FACTOR)
        {
            resize();
        }

        shared_ptr<Pair> pair = make_shared<Pair>(key, value_ptr);

        m_insert(table, pair);
    }

    bool exists(const TKey &key)
    {
        return search(key) != nullptr;
    }

    shared_ptr<TValue> search(const TKey &key) const
    {
        auto pair = m_find(key);

        if (pair == nullptr)
            return nullptr;

        // value of pair
        return pair->value;
    }

    void upsert(const TKey &key, const TValue &value)
    {
        auto ptr = search(key);
        if (ptr == nullptr)
        {
            return insert(key, value);
        }
        // update
        *ptr = value;
    }

    void upsert(const TKey &key, shared_ptr<TValue> value_ptr)
    {
        auto token = m_search(key);
        if (token == nullptr)
        {
            return insert(key, value_ptr);
        }

        if (value_ptr == nullptr)
        {
            // remove item
            m_remove(token);
        }
        else
        {
            auto pair = *token;
            // update
            pair->value = value_ptr;
        }
    }

    const TValue &operator[](const TKey &key) const
    {
        return *search(key);
    }

    TValue &operator[](const TKey &key)
    {
        return *search(key);
    }

    float loadFactor() const
    {
        return (float)size / (float)tableSize;
    }

    // TODO: for debugging remove later.
    //  class Iterator
    //  {
    //  private:
    //      Table* table;
    //      int tableIndex;
    //      typename TableItem::Iterator listIterator;

    // public:
    //     Iterator(Table* table, int table_index,
    //              typename DoubleLinkedList<shared_ptr<Pair>>::Iterator list_iterator)
    //         : table(table),
    //           tableIndex(table_index),
    //           listIterator(list_iterator)
    //     {
    //     }

    //     Iterator& operator++()
    //     {
    //         try
    //         {
    //             if (listIterator.current == nullptr)
    //             {
    //                 tableIndex++;
    //                 listIterator = table[tableIndex].begin();
    //             }
    //             else
    //             {
    //                 listIterator = listIterator.operator++();
    //             }
    //         }
    //         catch (...)
    //         {
    //             return *(this);
    //         }

    //         return *(this);
    //     }

    //     bool operator!=(const Iterator& other)
    //     {
    //         return listIterator != other.listIterator || tableIndex != other.tableIndex;
    //     }

    //     shared_ptr<TValue> operator*()
    //     {
    //         if (listIterator.current == nullptr) return nullptr;
    //         return (*listIterator)->value;
    //     }
    // };

    // Iterator begin()
    // {
    //     return Iterator(table, 0, table[0].begin());
    // }

    // Iterator end()
    // {
    //     return Iterator(table, tableSize-1, table[tableSize - 1].end());
    // }
};

#endif // HASHTABLE_H
