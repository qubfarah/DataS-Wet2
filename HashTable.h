//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_HASHTABLE_H
#define DS_WET2_WINTER_2024_2025_HASHTABLE_H

template <typename Key, typename Value>
class HashTable
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr)
        {
        }
    };

    Node** table;
    int capacity;
    int size;

    int hash(const Key& key) const;

public:
    explicit HashTable(const int& cap = 10);

    ~HashTable();

    bool insert(const Key& key, const Value& value);

    bool find(const Key& key, Value& value) const;

    bool remove(const Key& key);
};


template <typename Key, typename Value>
int HashTable<Key, Value>::hash(const Key& key) const
{
    return key % capacity;
}

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const int& cap): capacity(cap), size(0)
{
    table = new Node*[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }
}

template <typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
    for (int i = 0; i < capacity; ++i)
    {
        Node* current = table[i];
        while (current)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value)
{
    int idx = hash(key);
    Node* current = table[idx];
    while (current)
    {
        if (current->key == key) return false; // Key already exists
        current = current->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = table[idx];
    table[idx] = newNode;
    size++;
    return true;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::find(const Key& key, Value& value) const
{
    int idx = hash(key);
    Node* current = table[idx];
    while (current)
    {
        if (current->key == key)
        {
            value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::remove(const Key& key)
{
    int idx = hash(key);
    Node* current = table[idx];
    Node* prev = nullptr;
    while (current)
    {
        if (current->key == key)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                table[idx] = current->next;
            }
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}


#endif //DS_WET2_WINTER_2024_2025_HASHTABLE_H
