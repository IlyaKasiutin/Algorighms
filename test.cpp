#include "dynamic_array.h"
#include <string>
using namespace std;

void test_array()
{
    {
        DynamicArray<int> array;
        assert(array.IsEmpty());
    }
    cout << "Test 1 completed" << endl;

    {
        DynamicArray<int> array;
        array.Push(1);
        assert(array.Size() == 1);
        array.Pop();
        assert(array.IsEmpty());
    }
    cout << "Test 2 completed" << endl;

    {
        DynamicArray<string> array;
        assert(array.Size() == 0);
        assert(array.IsEmpty());
        array.Push("First");
        assert(array[0] == "First");
        assert(array.Size() == 1);
        assert(!array.IsEmpty());
        array.Pop();
        assert(array.Size() == 0);
    }
    cout << "Test 3 completed" << endl;

    {
        DynamicArray<int> array;
        for (int i = 0; i < 100; i++)
            array.Push(i);
        array.print_array();
        for (int i = 99; i > - 1; i--)
        {
            assert(array.Pop() == i);
        }
        assert(array.IsEmpty());
    }
    cout << "Test 4 completed" << endl;

    {
        DynamicArray<int> array;
        for (int i = 0; i < 100; i++)
        {
            array.Push(i);
            array[i] -=10;
        }
            
        for (int i = 99; i > - 1; i--)
        {
            assert(array.Pop() == i - 10);
        }
        assert(array.IsEmpty());
    }
    cout << "Test 5 completed" << endl;


    cout << "All tests completed" << endl;
}

void run_tests()
{
    test_array();
}

int main()
{
    run_tests();
    return 0;
}