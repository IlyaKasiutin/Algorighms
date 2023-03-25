#include "dynamic_array..h"
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
struct DefaultComparator
{
    bool operator()(const T& l, const T& r) const
    {
        return l < r;
    }
};


template <typename T, typename Comparator = DefaultComparator<T>>
class Heap
{
public:
    Heap(Comparator comp = Comparator()): comp(comp)
    {}
    Heap(const T& arr, size_t arr_size, Comparator comp = Comparator()): comp(comp)
    {}
    ~Heap();

    const T& top();
    void pop();
    void push(const T&);

    bool is_empty() const { return heap_size == 0; }
    size_t size() const { return heap_size; }

private:
    void heapify();
    void sift_up(T elem);
    T sift_down(T elem);

    Comparator comp;

    DynamicArray<T> buf;
    size_t buf_size;
    size_t heap_size;
};

template <typename T, typename Comparator>
void Heap<T, Comparator>::pop()
{}