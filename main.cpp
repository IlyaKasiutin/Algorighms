#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;


//DynamicArray
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
//DynamicArray


struct Point
{
    int position;
    bool value;

    bool operator<(Point& other_point) const
    {
        return position < other_point.position;
    }

    friend ostream& operator<<(ostream& out, Point& point)
    {
        out << "(" << point.position << "; " << point.value << ")";
        return out;
    }

};


template <typename T>
struct DefaultComparator
{
    bool operator()(const T& l, const T& r) const
    {
        return l < r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
void merge(T* arr1, int len1, T* arr2, int len2, T* result, Comparator comp)
{
    int pos1 = 0;
    int pos2 = 0;
    int pos_result = 0;
    while (pos1 < len1 && pos2 < len2)
    {
        if (comp(arr1[pos1], arr2[pos2]))
        {
            result[pos_result] = arr1[pos1];
            pos1++;
        }

        else
        {
            result[pos_result] = arr2[pos2];
            pos2++;
        }

        pos_result++;
    }

    while (pos1 < len1)
    {
        result[pos_result++] = arr1[pos1++];
    }

    while (pos2 < len2)
    {
        result[pos_result++] = arr2[pos2++];
    }
    
    delete[] arr1;
    delete[] arr2;
}

template <typename T, typename Comparator = DefaultComparator<T>>
void merge_sort(T* arr, size_t length, Comparator comp = Comparator())
{
    if (length <= 1)
        return;
    
    int first_len = length / 2;
    int second_len = length - first_len;
    merge_sort(arr, first_len, comp);
    merge_sort(arr + first_len, second_len, comp);

    T* temp_array = new T[length];

    merge<T>(arr, first_len, arr + first_len, second_len, temp_array, comp);
    
    std::copy(temp_array, temp_array + length, arr);
    delete[] temp_array;
}

int main()
{
    DynamicArray<Point> array;
    Point point;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> point.position;
        point.value = true;
        array.Push(point);

        std::cin >> point.position;
        point.value = false;
        array.Push(point);
    }

    array.PrintArray();

    merge_sort(&array, array.Size());

    array.PrintArray();

    return 0;
}