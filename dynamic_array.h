#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#define DEFAULT_INITIAL_SIZE 5
#include <assert.h>
#include <iostream>

template <typename T>
class DynamicArray
{
public:
    DynamicArray(): buffer_size(DEFAULT_INITIAL_SIZE), length(0) { buffer = new T[buffer_size]; }
    DynamicArray(DynamicArray const& another_array);
    ~DynamicArray() { delete[] buffer; }

    int Size() const { return length; }
    int MaxSize() const{ return buffer_size; }
    bool IsEmpty() const { return length == 0; }
    T GetElement(int index) const;
    void Push(const T& element);
    T& Pop();
    void PrintArray() const;

    T operator[](int index) const {return GetElement(index);}
    T& operator[](int index);
    DynamicArray& operator=(DynamicArray const& another_array);

protected:
    T* buffer;
    int buffer_size;
    int length;

    void Extend();
};

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &another_array):
        buffer_size(another_array.buffer_size), length(another_array.length)
{
    buffer = new int[length];
    std::copy(another_array.buffer, another_array.buffer + another_array.length, buffer);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> const& another_array)
{
    buffer_size = another_array.buffer_size;
    length = another_array.length;
    buffer = new T[length];
    std::copy(another_array.buffer, another_array.buffer + another_array.length, buffer);
    return *this;
}

template <typename T>
T DynamicArray<T>::GetElement(int index) const
{
    assert(index >= 0 && index < length && buffer != nullptr);
    return buffer[index];
}

template <typename T>
void DynamicArray<T>::Extend()
{
    int new_size = std::max(buffer_size * 2, DEFAULT_INITIAL_SIZE);
    T* new_buffer = new T[new_size];
    std::copy(buffer, buffer + length, new_buffer);
    delete[] buffer;
    buffer = new_buffer;
    buffer_size = new_size;
}

template <typename T>
void DynamicArray<T>::Push(const T& element)
{
    if (length == buffer_size)
        Extend();

    assert(length < buffer_size && buffer != nullptr);
    buffer[length++] = element;
}

template <typename T>
T& DynamicArray<T>::Pop()
{
    T& ans = buffer[length - 1];
    length--;
    return ans;
}

template <typename T>
T& DynamicArray<T>::operator[](int index)
{
    return buffer[index];
}

template <typename T>
void DynamicArray<T>::PrintArray() const
{
    for (auto i = 0; i < Size(); i++)
        std::cout << buffer[i] << " ";
    std::cout << std::endl;
}


#endif