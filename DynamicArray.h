//
// Created by Farah Qub on 17/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_DYNAMICARRAY_H
#define DS_WET2_WINTER_2024_2025_DYNAMICARRAY_H

#endif //DS_WET2_WINTER_2024_2025_DYNAMICARRAY_H


template <typename T>
class DynamicArray
{
private:
    T* data;
    int capacity;
    int size;

    void resize();

public:
    DynamicArray();

    ~DynamicArray();

    void push_back(const T& value);

    T& operator[](int index);

    const T& operator[](int index) const;

    int get_size() const;
};

template <typename T>
void DynamicArray<T>::resize()
{
    capacity *= 2;
    T* newData = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template <typename T>
DynamicArray<T>::DynamicArray() : capacity(10), size(0)
{
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value)
{
    if (size == capacity)
    {
        resize();
    }
    data[size++] = value;
}

template <typename T>
T& DynamicArray<T>::operator[](int index)
{
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](int index) const
{
    return data[index];
}

template <typename T>
int DynamicArray<T>::get_size() const
{
    return size;
}

