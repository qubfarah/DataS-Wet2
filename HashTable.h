//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_HASHTABLE_H
#define DS_WET2_WINTER_2024_2025_HASHTABLE_H

#include <functional>
#include <memory>

using namespace std;

template<typename TKey, typename TValue>
class HashTable {
    class Node : enable_shared_from_this<Node> {
    public:
        bool isEmpty;

        shared_ptr<Node> next;

        weak_ptr<Node> previous;

        TKey key;

        shared_ptr<TValue> value;
    };

    Node *table;

    int tableSize;


    int hash_a;
    int hash_b;


    int hash(TKey key) {
        return (hash_a * key + hash_b) % tableSize;
    }

    void resize() {
        auto newTable = new Node[2 * tableSize];


        for (const Node &node: *this) {
            m_insert(newTable, &hash, node.key, node.value);
        }

        // free previous data;
        delete[] table;

        tableSize *= 2;

        table = newTable;
    }

    using HashFn = function<int(TKey key)>;

    void m_insert(Node *table, const HashFn &hashFn, TKey &key, TValue &value) {
        int hashKey = hashFn(key);


        // this could be turned into one execution.
        if (table[hashKey].isEmpty) {
            Node node(key, value);

            table[hashKey] = std::move(node);

            return;
        }

        auto current = table[hashKey];

        while (current.next != nullptr) {
            current = current.next;
        }

        Node node(current, key, value);

        current.next = std::move(node);
    }

public:
    HashTable() {
        // Seed for random number generation
        std::srand(std::time(nullptr));
        // Generate random coefficients a and b
        hash_a = std::rand() % tableSize + 1; // a should be non-zero
        hash_b = std::rand() % tableSize;
    }

    ~HashTable() {
        delete[] table;
    }


    void insert(const TKey &key, const TValue &value) {
        m_insert(table, &hash, key, value);
    }

    bool exists(const TKey &key) {
        return search(key) != nullptr;
    }

    shared_ptr<TValue> search(TKey &key) const {
        int hashKey = hash(key);

        if (table[hashKey].isEmpty) {
            return nullptr;
        }

        auto current = table[hashKey];

        while (current != nullptr) {
            if (current.key == key) return current.value;
            current = current.next;
        }

        return nullptr;
    }


    TValue & operator [](const TKey &key) {
        return *search(key);
    }
};


#endif //DS_WET2_WINTER_2024_2025_HASHTABLE_H
