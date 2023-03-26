#include "heap.h"
#include <string>
using namespace std;

void test_heap()
{
    {
        Heap<int> heap;
        assert(heap.IsEmpty());
    }
    cout << "Test 1 completed" << endl;

    {
        Heap<int> heap;
        heap.Push(1);
        assert(heap.Size() == 1);
        auto top = heap.Top();
        assert(top == 1);
        heap.Pop();
        assert(heap.Size() == 0);
        assert(heap.IsEmpty());
    }
    cout << "Test 2 completed" << endl;

    {
        Heap<int> heap;
        for (int i = 0; i < 100; i++)
        {
            heap.Push(i);
        }
        heap.PrintHeap();
        for (int i = 0; i < 100; i++)
        {
            assert(heap.Top() == i);
            heap.Pop();
            assert(heap.Size() == 99 - i);
        }
    }
    cout << "Test 3 completed" << endl;

    {
        Heap<string> heap;

        //assert(heap.Size() == 0);
        //assert(heap.IsEmpty());
        string str1, str2, str3;
        str1 = "First";
        str2 = "Second";
        str3 = "A";
        heap.Push(str1);
        heap.PrintHeap();
        assert(heap.Top() == "First");
        assert(heap.Size() == 1);
        assert(!heap.IsEmpty());
        heap.Push(str2);
        heap.PrintHeap();
        heap.Push(str3);
        heap.PrintHeap();
        heap.Pop();
        heap.PrintHeap();
        assert(heap.Size() == 2);
    }
    cout << "Test 4 completed" << endl;
    cout << "All tests completed" << endl;

}

void run_tests()
{
    test_heap();
}

int main()
{
    run_tests();
    return 0;
}