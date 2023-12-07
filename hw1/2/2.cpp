/*
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого
элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или
превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
*/

#include <iostream>

int exp_search(int* array, int array_length, int value)
{
    int index = 1;
    for (; index < array_length; index *= 2)
    {
        if (array[index] >= value)
            break;
    }
    if (index < array_length)
        return index;
    else
        return array_length - 1;
}

int bin_search(int* array, int value, int left, int right)
{
    int mid = (left + right) / 2;
    while (left < right)
    {
        if (array[mid] < value)
            left = mid + 1;
        else
            right = mid;

        mid = (left + right) / 2;

    }
    return left;
}

int solve(int* arr1, int array_length, int value)
{
    int right = 0;
    int left = 0;
    right = exp_search(arr1, array_length, value);

    if (right > 2)
        left = right / 2;
    else
        left = 0;

    int ans = bin_search(arr1, value, left, right);

    if (arr1[ans] >= value)
        return ans;
    else
        return array_length;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    int array1[n];


    for (int i = 0; i < n; i++)
        std::cin >> array1[i];

    int val = 0;
    for (int i = 0; i < m; i++)
    {
        std::cin >> val;
        std::cout << solve(array1, n, val) << " ";
    }

    return 0;
}