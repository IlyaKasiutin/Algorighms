#include <iostream>

int partition(unsigned long long* arr, int l, int r, unsigned long long pivot)
{
    std::cout << "partition for: ";
    for (int i = l; i < r; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    int i = l;
    int j = l;
    while (j < r)
    {
        std::cout << "arr[j] = " << arr[j] << std::endl;
        std::cout << (arr[j] & pivot) << std::endl;
        std::cout << (j < r) << " " << ((arr[j] & pivot) == 0) << std::endl;
        while (arr[j] & pivot)
        {
            std::cout << "j increasing" << std::endl;
            j++;
        }

        if ((j < r) && ((arr[j] & pivot) == 0))
        {
            std::cout << "i and j increasing" << std::endl;
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    return i;
}

void msd_sort(unsigned long long* arr, int l, int r, unsigned long long pivot)
{
    std::cout << "msd_sort for: ";
    for (int i = l; i < r; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    if (r - l <= 1)
        return;

    int separator = partition(arr, l, r, pivot);
    msd_sort(arr, l, separator - 1, pivot >> 1);
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

    std::cout << "result: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}