#include <assert.h>
#include <iostream>
#define DEFAULT_INITIAL_SIZE 5


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
    buffer = new T[length];
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
    Heap(Comparator comp = Comparator()): comp(comp) {}

    Heap(const T& arr, size_t arr_size, Comparator comp = Comparator()): comp(comp)
    {
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

class Process
{
public:
    Process(): P(0), T(0), t(0) {}
    Process(int P, int T): P(P), T(T), t(0) {}

    void Update() { t += P; }
    int get_P() const { return P; }
    int get_T() const{ return T; }
    int get_t() const { return t; }

    bool operator<(Process other_process) const
    {
        return P * (t + 1) < other_process.get_P() * (other_process.get_t() + 1);
    }

private:
    int P;
    int t;
    int T;

};


int execute(Heap<Process> heap)
{
    int n = 0;
    Process proc;
    while (!heap.IsEmpty())
    {
        proc = heap.Top();
        heap.Pop();
        proc.Update();
        if (proc.get_t() < proc.get_T())
            heap.Push(proc);
        n++;
    }
    return n;
}

int main()
{
    Heap<Process> heap;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int P = 0, T = 0;
        std::cin >> P >> T;
        Process proc(P, T);
        heap.Push(proc);
    }

    std::cout << execute(heap) << std::endl;

    return 0;
}

