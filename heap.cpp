#include "heap.h"

template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify()
{
    for (int i = buf_size - 1; i > -1; i--)
    {
        int current_position = i;
        while current_position * 2 + 1 < buf_size - 1
        {
            int min_son_index = current_position * 2 + 1;
            if (buf[current_position * 2 + 2] < buf[current_position * 2 + 1])
                int min_son_index = current_position * 2 + 2;
            
            if (buf[current_position] > buf[min_son_index])
            {
                std::swap(buf[current_position], buf[min_son_index]);
                current_position = min_son_index;
            }

            else
                break;
        }
    }
}

template <typename T, typename Comparator>
T Heap<T, Comparator>::sift_down(T elem)
{
    T ans = buf[0];
    buf[0] = buf[buf.Size() - 1];
    int position = 0;
    while (position * 2 + 1 < buf_size - 1)
    {
        int min_son_index = position * 2 + 1;
        if (buf[pos * 2 + 2] < buf[pos * 2 + 1])
            min_son_index = position * 2 + 2;
        
        if (buf[position] > buf[min_son_index])
        {
            std::swap(buf[position], buf[min_son_index]);
            position = min_son_index;
        }
        else
            break;
    }
    buf.Pop();
    return ans;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_up(T elem)
{
    buf.Push(elem);
    int position = buf_size - 1;
    while (position > 0 && buf[position] < buf[(position - 1) / 2])
    {
        std::swap(buf[position], buf[(position - 1) / 2]);
        position = (position - 1) / 2;
    }
}

template <typename T, typename Comparator>
const T& Heap<T, Comparator>::top()
{
    if (is_empty())
        return nullptr;
    
    return buf[0];
}
