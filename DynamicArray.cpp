//
// Created by Farah Qub on 17/01/2025.
//

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray() : capacity(10), size(0) {
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    T& operator[](int index) {
        return data[index];
    }

    int get_size() const {
        return size;
    }
};
