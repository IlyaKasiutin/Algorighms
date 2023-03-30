/*Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>

template <typename T>
struct DefaultComparator
{
    bool operator()(const T& l, const T& r) const
    {
        return l < r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
int find_median(T* arr, int l, int r, Comparator comp)
{
    if (r - l >= 3)
    {
        int left = arr[l];
        int middle = arr[l + (r - l) / 2];
        int right = arr[r - 1];

        if (comp(middle, left) && comp(left, right) || comp(right, left) && comp(left, middle))
            return l;

        else if (comp(left, right) && comp(right, middle) || comp(middle, right) && comp(right, left))
            return r - 1;

        else
            return l + (r - l) / 2;
    }
    return l;
}

template <typename T, typename Comparator = DefaultComparator<T>>
int partition(T* arr, int l, int r, Comparator comp)
{
    int pivot_idx = find_median(arr, l, r, comp);
    T pivot = arr[pivot_idx];

    std::swap(arr[pivot_idx], arr[l]);

    int i = r - 1;
    int j = r - 1;
    while (j > l)
    {
        while (arr[j] < pivot)
            j--;

        if (j > l && arr[j] >= pivot)
        {
            std::swap(arr[i], arr[j]);
            i--;
            j--;
        }
    }

    std::swap(arr[i], arr[l]);
    return i;
}

template <typename T, typename Comparator = DefaultComparator<T>>
void kth_element(T* arr, int size, int k, Comparator comp = Comparator())
{
    int l = 0;
    int r = size;
    while (l < r)
    {
        int m = partition(arr, l, r, comp);
        if (m == k)
        {
            return;
        }
        else if (m < k)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    int* array = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    int percent_10 = int(0.1 * n);
    int median = int(0.5 * n);
    int percent_90 = int(0.9 * n);

    kth_element(array, n, percent_10);

    kth_element(array, n, median);

    kth_element(array, n, percent_90);

    std::cout << array[percent_10] << std::endl;
    std::cout << array[median] << std::endl;
    std::cout << array[percent_90] << std::endl;

    return 0;
}