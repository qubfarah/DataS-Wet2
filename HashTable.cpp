//
// Created by Farah Qub on 17/01/2025.
//

template <typename Key, typename Value>
class HashTable {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;
        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;
    int capacity;
    int size;

    int hash(const Key& key) const {
        return key % capacity;
    }

public:
    explicit HashTable(const int& cap = 10) : capacity(cap), size(0) {
        table = new Node*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    bool insert(const Key& key, const Value& value) {
        int idx = hash(key);
        Node* current = table[idx];
        while (current) {
            if (current->key == key) return false; // Key already exists
            current = current->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = table[idx];
        table[idx] = newNode;
        size++;
        return true;
    }

    bool find(const Key& key, Value& value) const {
        int idx = hash(key);
        Node* current = table[idx];
        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(const Key& key) {
        int idx = hash(key);
        Node* current = table[idx];
        Node* prev = nullptr;
        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
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
};
