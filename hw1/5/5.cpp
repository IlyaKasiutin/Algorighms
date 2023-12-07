/*На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
Найти длину окрашенной части числовой прямой.*/

#include <iostream>
#include <vector>
#include <assert.h>

struct Point
{
    int position;
    bool value;

    bool operator<(const Point& other_point) const
    {
        return position < other_point.position;
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

int count_colored_area(Point* arr, int size)
{
    int opened = 0;
    int colored_area = 0;
    int prev_pos = 0;

    for (int i = 0; i < size; i++)
    {
        if (opened > 0)
            colored_area += arr[i].position - prev_pos;

        if (arr[i].value == 1)
            opened++;
        else
            opened--;

        prev_pos = arr[i].position;
    }

    return colored_area;
}

int main()
{
    int n = 0;
    std::cin >> n;
    Point* array = new Point[2 * n];
    Point point;
    for (int i = 0; i < n; i++)
    {
        std::cin >> point.position;
        point.value = true;
        array[2 * i] = point;

        std::cin >> point.position;
        point.value = false;
        array[2 * i + 1] = point;
    }

    merge_sort(array, 2 * n);

    std::cout << count_colored_area(array, 2 * n) << std::endl;

    return 0;
}