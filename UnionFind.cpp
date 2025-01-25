//#include <iostream>
//
//// Node in the "up-tree"
//struct UpTreeNode {
//    int id;             // Unique identifier (e.g., jockey ID)
//    UpTreeNode* parent; // Parent node in the up-tree
//    int rank;           // Rank for union-find
//
//    UpTreeNode(int id) : id(id), parent(this), rank(0) {}
//};
//
//// Union-Find class for managing up-tree operations
//class UnionFind {
//public:
//    // Find with path compression
//    UpTreeNode* find(UpTreeNode* node) {
//        if (node->parent != node) {
//            node->parent = find(node->parent); // Path compression
//        }
//        return node->parent;
//    }
//
//    // Union by rank
//    void unite(UpTreeNode* node1, UpTreeNode* node2) {
//        UpTreeNode* root1 = find(node1);
//        UpTreeNode* root2 = find(node2);
//
//        if (root1 != root2) {
//            if (root1->rank > root2->rank) {
//                root2->parent = root1;
//            } else if (root1->rank < root2->rank) {
//                root1->parent = root2;
//            } else {
//                root2->parent = root1;
//                root1->rank++;
//            }
//        }
//    }
//};
//
//// Node in the linked list
//struct LinkedListNode {
//    int key;                      // Key (e.g., jockey ID)
//    UpTreeNode* upTreeNode;       // Pointer to the "up-tree" node
//    LinkedListNode* next;         // Pointer to the next node in the list
//
//    LinkedListNode(int key, UpTreeNode* upTreeNode)
//            : key(key), upTreeNode(upTreeNode), next(nullptr) {}
//};
//
//// Hash table for managing jockeys
//class HashTable {
//private:
//    LinkedListNode** table; // Array of pointers to linked lists
//    int capacity;           // Number of buckets in the hash table
//
//    // Hash function to map keys to buckets
//    int hashFunction(int key) const {
//        return key % capacity;
//    }
//
//public:
//    // Constructor
//    HashTable(int capacity) : capacity(capacity) {
//        table = new LinkedListNode*[capacity];
//        for (int i = 0; i < capacity; ++i) {
//            table[i] = nullptr;
//        }
//    }
//
//    // Destructor
//    ~HashTable() {
//        for (int i = 0; i < capacity; ++i) {
//            LinkedListNode* node = table[i];
//            while (node) {
//                LinkedListNode* temp = node;
//                node = node->next;
//                delete temp;
//            }
//        }
//        delete[] table;
//    }
//
//    // Insert a key with a pointer to the up-tree node
//    void insert(int key, UpTreeNode* upTreeNode) {
//        int index = hashFunction(key);
//        LinkedListNode* newNode = new LinkedListNode(key, upTreeNode);
//
//        // Insert at the head of the linked list
//        newNode->next = table[index];
//        table[index] = newNode;
//    }
//
//    // Find a key and return its up-tree node pointer
//    UpTreeNode* find(int key) const {
//        int index = hashFunction(key);
//        LinkedListNode* node = table[index];
//
//        while (node) {
//            if (node->key == key) {
//                return node->upTreeNode;
//            }
//            node = node->next;
//        }
//        return nullptr; // Key not found
//    }
//
//    // Remove a key from the hash table
//    void remove(int key) {
//        int index = hashFunction(key);
//        LinkedListNode* node = table[index];
//        LinkedListNode* prev = nullptr;
//
//        while (node) {
//            if (node->key == key) {
//                if (prev) {
//                    prev->next = node->next;
//                } else {
//                    table[index] = node->next;
//                }
//                delete node;
//                return;
//            }
//            prev = node;
//            node = node->next;
//        }
//    }
//};


// Template class for Union-Find
template <typename T>
class UnionFind {
public:
    // Find with path compression
    T* find(T* object) {
        if (object->parent != object) {
            object->parent = find(object->parent); // Path compression
        }
        return object->parent;
    }

    // Union by rank
    void unite(T* object1, T* object2) {
        T* root1 = find(object1);
        T* root2 = find(object2);

        if (root1 != root2) {
            if (root1->rank > root2->rank) {
                root2->parent = root1;
            } else if (root1->rank < root2->rank) {
                root1->parent = root2;
            } else {
                root2->parent = root1;
                root1->rank++;
            }
        }
    }
};
