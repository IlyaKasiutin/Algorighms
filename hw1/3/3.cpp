/*
Реализовать очередь с динамическим зацикленным буфером.
Обрабатывать команды push back и pop front.
2 - pop front
3 - push back
*/

#include <iostream>
#include <assert.h>
#include <iterator>

#define DEFAULT_INITIAL_SIZE 5

class DynamicArray
{
public:
    DynamicArray(): buffer_size(DEFAULT_INITIAL_SIZE), length(0) { buffer = new int[buffer_size]; }
    DynamicArray(DynamicArray const& another_array);
    ~DynamicArray() { delete[] buffer; }

    int Size() const { return length; }
    int MaxSize() const{ return buffer_size; }
    bool IsEmpty() const { return length == 0; }
    int GetElement(int index) const;
    void Push(int element);

    int operator[](int index) const {return GetElement(index);}
    DynamicArray& operator=(DynamicArray const& another_array);

protected:
    int* buffer;
    int buffer_size;
    int length;

    void Extend();
};


DynamicArray::DynamicArray(const DynamicArray &another_array):
    buffer_size(another_array.buffer_size), length(another_array.length)
{
    buffer = new int[length];
    std::copy(another_array.buffer, another_array.buffer + another_array.length, buffer);
}

DynamicArray& DynamicArray::operator=(DynamicArray const& another_array)
{
    buffer_size = another_array.buffer_size;
    length = another_array.length;
    buffer = new int[length];
    std::copy(another_array.buffer, another_array.buffer + another_array.length, buffer);
    return *this;
}

int DynamicArray::GetElement(int index) const
{
    assert(index >= 0 && index < length && buffer != nullptr);
    return buffer[index];
}

void DynamicArray::Extend()
{
    int new_size = std::max(buffer_size * 2, DEFAULT_INITIAL_SIZE);
    int* new_buffer = new int[new_size];
    std::copy(buffer, buffer + length, new_buffer);
    delete[] buffer;
    buffer = new_buffer;
    buffer_size = new_size;
}

void DynamicArray::Push(int element)
{
    if (length == buffer_size)
        Extend();
        
    assert(length < buffer_size && buffer != nullptr);
    buffer[length++] = element;
}


class Queue: public DynamicArray
{
public:
    Queue():head(0), tail(0) {};

    void PushBack(int value);
    int PopFront();
    void Print();

private:
    int head;
    int tail;

    void Extend();
};

int Queue::PopFront()
{
    int prev_head = head;

    if (Size() >= 1)
    {
        if (Size() > 1)
            head = (head + 1) % MaxSize();

        length--;
        return buffer[prev_head];
    }

    else
        return -1;
}

void Queue::PushBack(int value)
{
    if ((tail + 1) % MaxSize() == head)
        Extend();

    if (length != 0)
        tail = (tail + 1) % MaxSize();
    
    length++;
    buffer[tail] = value;
}

void Queue::Extend()
{
    int new_size = std::max(buffer_size * 2, DEFAULT_INITIAL_SIZE);
    int* new_buffer = new int[new_size];

    int cur_elem = head;
    int i = 0;
    while (cur_elem != tail)
    {
        new_buffer[i++] = buffer[cur_elem];
        cur_elem = (cur_elem + 1) % MaxSize();
    }
    new_buffer[i] = buffer[cur_elem];

    delete[] buffer;
    buffer = new_buffer;
    head = 0;
    tail = length - 1;

    buffer_size = new_size;
}

void Queue::Print()
{
    std::cout << std::endl << "Diagnostics" << std::endl;
    std::cout << "head: " << head << " tail: " << tail << " length: " << Size() << std::endl;
    int cur_elem = head;
    while (cur_elem != tail)
    {
        std::cout << buffer[cur_elem] << " ";
        cur_elem = (cur_elem + 1) % MaxSize();
    }
    std::cout << buffer[cur_elem] << std::endl << std::endl;
}


bool check_pop(Queue& queue, int value)
{   
    int val = queue.PopFront();
    if (val == value)
        return true;

    return false;
}

std::string handle_queries(Queue& queue, int number_of_operations)
{
    int operation = 0;
    int value = 0;
    bool result = false;
    std::string answer = "";

    for (int i = 0; i < number_of_operations; i++)
    {
        std::cin >> operation >> value;
        if (operation == 3)
            queue.PushBack(value);

        else if (operation == 2)
        {
            result = check_pop(queue, value);
            if (result == false)
                answer = "NO";
        }
    }
    
    if (answer == "")
        answer = "YES";
    
    return answer;
}

int main()
{
    int n = 0;
    std::cin >> n;
    Queue Q;

    std::cout << handle_queries(Q, n) << std::endl;

    return 0;
}