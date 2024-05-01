// Простейший циклический буфер на основе массива ограниченного размера.

#include <iostream>
#include <cstring>

const int size = 6;
int flag = 0; // Этот флаг для того, чтобы при ошибке извлечения числа из буфера в строку не записывалось изначальное проинициализированное число массива.

class CycleBuffer 
{
private:
    int head;
    int tail;
    bool isFull; // Проверка на заполненность массива.
    int array[size];

public:
    CycleBuffer() 
    {
        head = 0; // Указатель на первый элемент очереди.
        tail = 0; // Указатель на последний элемент очереди.
        isFull = false;
    }

    void addValue(int val) // Добавить элемент в буфер.
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

    int getValue() // Изьять элемент из буфера.
    {
        int temp;
        try
        {
            if (head == tail && !isFull)
            {
                temp = (int)nan;
                flag = 1;
                throw "Нет элемента!";
            }

            else if (head == size && isFull)
            {
                isFull = false;
                head = 0;
                temp = array[head];
            }

            else
            {
                temp = array[head];
                head += 1;
            }
        }
        catch (const char* exception)
        {
            std::cout << exception << std::endl;
        }
        return temp;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    CycleBuffer buffer;
    std::string answer = "";
    std::cout << "Добро пожаловать в циклический буфер!" << std::endl;
    while (1) 
    {
        std::cout << "Введите слово:" << std::endl << "1. exit - Выйти из программы." << std::endl << "2. add - Добавить элемент."
            << std::endl << "3. get - Вернуть элемент и вывести на экран." << std::endl << "4. clear - Очистить буфер." << std::endl << std::endl;
        std::cin >> answer;

        if (answer == "exit") break;

        else if (answer == "add")
        {
            int value;
            std::cout << "Введите значение: ";
            std::cin >> value;
            buffer.addValue(value);
            std::cout << std::endl;
        }
        else if (answer == "get")
        {
            int temp = buffer.getValue();
            if (flag == 1)
            {
                flag = 0;
                continue;
            }
            else std::cout << temp << std::endl;
        }
        else if (answer == "clear")
        {
            CycleBuffer newBuffer;
            buffer = newBuffer;
            std::cout << "Буфер очищен." << std::endl << std::endl;
        }
        else std::cout << "Введите корректную команду!" << std::endl << std::endl;
    }
}

