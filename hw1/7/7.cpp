/*Дан массив неотрицательных целых 64-разрядных чисел. 
Количество чисел не больше 1000000. 
Отсортировать массив методом MSD по битам (бинарный QuickSort).*/

#include <iostream>

int partition(unsigned long long* arr, int l, int r, unsigned long long pivot)
{
    int i = l;
    int j = l;
    while (j < r)
    {
        while (arr[j] & pivot)
        {
            j++;
        }

        if ((j < r) && ((arr[j] & pivot) == 0))
        {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    return i;
}

void msd_sort(unsigned long long* arr, int l, int r, unsigned long long pivot)
{
    if (r - l <= 1 )
        return;

    int separator = partition(arr, l, r, pivot);
    msd_sort(arr, l, separator, pivot >> 1);
    msd_sort(arr, separator, r, pivot >> 1);
}

int main()
{
    unsigned int n = 0;
    std::cin >> n;
    unsigned long long* array = new unsigned long long[n];
    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    msd_sort(array, 0, n, 1ULL << 63);

    for (int i = 0; i < n; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}