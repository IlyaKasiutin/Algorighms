#pragma once

#define DEFAULT_INITIAL_SIZE 5

template <typename T>
class DynamicArray
{
public:
    DynamicArray(): buffer_size(DEFAULT_INITIAL_SIZE), length(0) { buffer = new int[buffer_size]; }
    DynamicArray(DynamicArray const& another_array);
    ~DynamicArray() { delete[] buffer; }

    int Size() const { return length; }
    int MaxSize() const{ return buffer_size; }
    bool IsEmpty() const { return length == 0; }
    T GetElement(int index) const;
    void Push(T element);
    T Pop();

    T operator[](int index) const {return GetElement(index);}
    DynamicArray& operator=(DynamicArray const& another_array);

protected:
    T* buffer;
    int buffer_size;
    int length;
    void Extend();
};
