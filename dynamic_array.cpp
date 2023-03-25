#include "dynamic_array..h"
#include <assert.h>
#include <iostream>

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
    buffer = new int[length];
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
    int* new_buffer = new int[new_size];
    std::copy(buffer, buffer + length, new_buffer);
    delete[] buffer;
    buffer = new_buffer;
    buffer_size = new_size;
}

template <typename T>
void DynamicArray<T>::Push(T element)
{
    if (length == buffer_size)
        Extend();
        
    assert(length < buffer_size && buffer != nullptr);
    buffer[length++] = element;
}

template <typename T>
T DynamicArray<T>::Pop()
{
    T ans = buffer[length - 1];
    length--;
    return ans;
}
