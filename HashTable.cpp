#include <iostream>
#include  "HashTable.h"



// Node in the linked list for the hash table
template <typename T>
struct LinkedListNode {
    int key;               // Key (e.g., ID)
    T* object;             // Pointer to the object (generic type)
    LinkedListNode* next;  // Pointer to the next node in the list

    LinkedListNode(int key, T* object)
            : key(key), object(object), next(nullptr) {}
};

// Template class for HashTable
template <typename T>
class HashTable {
private:
    LinkedListNode<T>** table; // Array of pointers to linked lists
    int capacity;              // Number of buckets in the hash table

    // Hash function to map keys to buckets
    int hashFunction(int key) const {
        return key % capacity;
    }

public:
    // Constructor
    HashTable(int capacity) : capacity(capacity) {
        table = new LinkedListNode<T>*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    // Destructor
    ~HashTable() {
        for (int i = 0; i < capacity; ++i) {
            LinkedListNode<T>* node = table[i];
            while (node) {
                LinkedListNode<T>* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Insert a key with a pointer to the object
    void insert(int key, T* object) {
        int index = hashFunction(key);
        LinkedListNode<T>* newNode = new LinkedListNode<T>(key, object);

        // Insert at the head of the linked list
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Find a key and return its object pointer
    T* find(int key) const {
        int index = hashFunction(key);
        LinkedListNode<T>* node = table[index];

        while (node) {
            if (node->key == key) {
                return node->object;
            }
            node = node->next;
        }
        return nullptr; // Key not found
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = hashFunction(key);
        LinkedListNode<T>* node = table[index];
        LinkedListNode<T>* prev = nullptr;

        while (node) {
            if (node->key == key) {
                if (prev) {
                    prev->next = node->next;
                } else {
                    table[index] = node->next;
                }
                delete node;
                return;
            }
            prev = node;
            node = node->next;
        }
    }
};