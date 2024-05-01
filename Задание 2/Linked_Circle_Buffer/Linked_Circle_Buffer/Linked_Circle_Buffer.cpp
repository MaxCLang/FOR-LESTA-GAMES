#include <iostream>
#include <cstring>
using namespace std;

class Node // Класс, описывающий Звено буфера.
{
public:
	int value; 
	Node* next;
	int flag = 0; // Проверяет, заполнена ли ячейка и возможность отдать элемент из нее
	Node(int v) : value(v), next(nullptr) {};
};

class CircleLinkedList // Класс, описывающий сам буфер.
{
private:
	int length = 0; // Текущая длина буфера. Его заполненность
	int maxLength = 0; // Максимальная длина
	bool isFull = false; // Заполнены ли все ячейки буфера
	int pos = 0; // Показывает, на каком по счету элементе находится сейчас указатель. Это нужно прежде всего для того,
	// чтобы при извлечении элемента не потерять свою позицию (при использовании метода Get).
	Node* head; // Голова
	Node* tail; // Хвост
	Node* pointer; // Указатель
public:
	CircleLinkedList(int l) 
	{
		maxLength = l;
	}
	bool flag = false; // Проверяет, не пустой ли буфер (не null)
	void Add(int value) // Добавить элемент в буфер
	{
		Node* node = new Node(value);
		node->flag = 1;
		length += 1;
		if (head == nullptr) // Когда буфер только что инициализирован
		{
			tail = head = node;
			pointer = head;
			flag = true;
			pos++;
		}
		else if (isFull && length != maxLength && maxLength != 1) // Когда добавление элементов идет по второму и более кругу.
		{
			if (length == 1) pos = 0;
			tail = tail->next;
			tail->value = node->value;
			tail->flag = 1;
			pos++;
		}
		else if (isFull && length == maxLength && maxLength != 1)  // Когда доходим до последнего элемента, при этом это не первая итерация.
		{
			tail = tail->next;
			length = 0;
			tail->value = node->value;
			tail->flag = 1;
			pos++;
		}
		else if (!isFull && maxLength != 1 && length == maxLength) // Когда дошли до последнего элемента на самой первой итерации.
		{
			tail->next = node;
			tail = node;
			tail->flag = 1;
			length = 0;
			isFull = true;
			tail->next = head;
			pos++;
		}
		else if (isFull && maxLength == 1) // Когда у нас размер буфера равен 1.
		{
			tail = head;
			tail->value = node->value;
			tail->flag = 1;
			pos = 1;
		}
		else // Добавление элементов на первой итерации.
		{
			tail->next = node;
			tail = node;
			pos++;
		}
	}
	
	int Get() // Изьять элемент из буфера
	{
		int val = -1010;
		if (pointer->flag == 1)
		{
			if (pointer->next != nullptr)
			{
				val = pointer->value;
				pointer->flag = 0;
				pointer = pointer->next;
			}
			else if (pointer->next == nullptr)
			{
				val = pointer->value;
				pointer->flag = 0;
			}
		}
		return val;
	}

	int Show() // Показать текущую позицию последнего добавленнного элемента.
	{
		return pos;
	}
};

int main() 
{
	setlocale(LC_ALL, "Russian");
	int length;
	string answer;
	cout << "Добро пожаловать в циклический буфер, основанный на ссылках!" << endl;
	cout << "Введите размер буфера: ";
	cin >> length;
	cout << "Чтобы выйти из программы введите \"exit\"" << endl;
	CircleLinkedList list(length);
	while (1)
	{
		cout << "Что вы хотите сделать? Введите соответствующее слово в консоль" << endl;
		cout << "add - Добавить элемент в буфер." << endl;
		cout << "get - Изьят элемент из буфера" << endl;
		cout << "show - Показать номере позиции, куда будет добавлени следующий элемент" << endl;
		cout << "exit - Выйти из программы" << endl;
		cin >> answer;
		if (answer == "exit") break;
		if (answer == "add") 
		{
			cout << endl;
			int add;
			cout << "Введите элемент: ";
			cin >> add;
			list.Add(add);
			cout << "Элемент добавлен!";
			cout << endl << endl;
		}
		if (answer == "get") 
		{
			if (!list.flag) 
			{
				cout << endl;
				cout << "Буфер пуст!" << endl << endl;
				continue;
			}
			cout << endl;
			cout << "В консоль будет выведено число -1010, если буфер пуст!" << endl;
			cout << list.Get() << endl << endl;
		}
		if (answer == "show") 
		{
			cout << endl;
			cout << "Текущая позиция элемента: " << list.Show() << endl;
		}
	}
}

