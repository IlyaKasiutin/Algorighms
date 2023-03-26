#include "dynamic_array.h"
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;

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
    {
        //buf = DynamicArray<T>();
    }

    Heap(const T& arr, size_t arr_size, Comparator comp = Comparator()): comp(comp)
    {
        //buf = DynamicArray<T>();

        for (auto i = 0; i < arr_size; i++)
        {
            Push(arr[i]);
        }
    }
    ~Heap(){}

    const T& Top();
    void Pop();
    void Push(const T& element);

    bool IsEmpty() const { return buf.Size() == 0; }
    size_t Size() const { return buf.Size(); }
    void PrintHeap() const;

private:
    void heapify();
    void sift_up(int index);
    void sift_down(int index);

    Comparator comp;

    DynamicArray<T> buf;
};

template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify()
{
    for (int i = buf.Size() / 2 - 1; i >= 0; i--)
        sift_down(i);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_down(int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int min_elem = index;
    if (left < buf.Size() && comp(buf[left], buf[index]))
        min_elem = left;
    if (right < buf.Size() && comp(buf[right], buf[min_elem]))
        min_elem = right;

    if (min_elem != index)
    {
        std::swap(buf[index], buf[min_elem]);
        sift_down(min_elem);
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_up(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (!comp(buf[index], buf[parent]))
            return;
        std::swap(buf[index], buf[parent]);
        index = parent;
    }
}

template <typename T, typename Comparator>
const T& Heap<T, Comparator>::Top()
{
    assert(!buf.IsEmpty());
    return buf[0];
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::Push(const T& element)
{
    buf.Push(element);
    sift_up(buf.Size() - 1);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::Pop()
{
    assert(!buf.IsEmpty());
    buf[0] = buf[buf.Size() - 1];
    buf.Pop();
    if (!buf.IsEmpty())
        sift_down(0);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::PrintHeap() const
{
    buf.PrintArray();
}
