//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_DYNAMICARRAY_H
#define DS_WET2_WINTER_2024_2025_DYNAMICARRAY_H

#endif //DS_WET2_WINTER_2024_2025_DYNAMICARRAY_H


template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize() {}

public:
    DynamicArray() : capacity(10), size(0) {}

    void push_back(const T& value) {}

    T& operator[](int index) {}

    int get_size() const {}
};
