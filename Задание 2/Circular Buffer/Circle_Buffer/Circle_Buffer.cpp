// Простейший циклический буфер на основе массива ограниченного размера.

#include <iostream>

const int size = 6;

class CycleBuffer 
{
private:
    int head;
    int tail;
    bool isFull;
    int array[size];

public:
    CycleBuffer() 
    {
        head = 0;
        tail = 0;
        isFull = false;
    }

    void addValue(int val) 
    {
        if (tail < size) 
        {
            array[tail] = val;
            tail += 1;
        }
        if (tail == size) 
        {
            isFull = true;
            tail = 0;
            array[tail] = val;
        }
    }

    int getValue() 
    {
        int temp;
        try 
        {
            if (head == tail && !isFull)
            {
                throw "Нет элемента!";
            }
        }
        catch (const char* exception) 
        {
            std::cout << exception << std::endl;
        }

        if (head == size)
        {
            isFull = false;
            head = 0;
        }
        
        else 
        {
            temp = array[head];
            head += 1;
        }

        return temp;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    CycleBuffer buffer;
    buffer.addValue(8);
    int number = buffer.getValue();
    std::cout << number << std::endl;
}

