



//========================================================================
// Здравствуйте!
// 
// Мой выбор пал на сортировку Кучей. Почему? В мире существует быстрая сортировка Хоара, которая на практике в среднем случае является намного 
// более быстрой, нежели сортировка Кучей, однако же, сортировка Хоара - нестабильный алгоритм, и при уже отсортированном массиве (или же когда
// элементы равны) сложность сортировки Хоара становится равной 0(N^2),а у нас по условию возможность уже отсортированного массива
// необходимо учитывать.
// 
// Кроме того, сортировка Слиянием также быстрее, нежели сортировка Кучей, но сортировка Слиянием занимает дополнительную память 0(N), так как
// использует временный массив.
// 
// Сложность сортировки Кучей в худших и лучших случаях - всегда nlogn, а также не использует дополнительную память,
// в отличие от сортировки Слиянием.
//
//========================================================================


#include <iostream>
using namespace std;

int* CreateArray(int n) // Создание массива.
{
	int* array = new int[n];
	for (int i = 0; i < n; i++) 
	{
		cout << "Введите " << i + 1 << " элемент: ";
		cin >> array[i];
	}
	return array;
}

void Print(int* array,int length) // Вывод элементов массива.
{
	cout << endl;
	cout << "Список элементов массива:" << endl;
	for (int i = 0; i < length; i++) 
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

void Heap(int* array, int element, int length) // Создание самой кучи, в которой на верхних уровнях расположены наибольшие элементы.
{
	int max = element;
	while (1) 
	{
		int child = 2 * element + 1; // Первый дочерний элемент.
		if (child < length && array[child] > array[max]) 
		{
			max = child;
		}
		child++; // Второй дочерний элемент.
		if (child < length && array[child] > array[max]) 
		{
			max = child;
		}
		if (max == element) break;
		else // Меняем местами элементы. Наибольший идет наверх.
		{
			int temp = array[element];
			array[element] = array[max];
			array[max] = temp;
			element = max; // Спускаемся ниже по дереву к дочерним элементам.
		}
	}
}

void SortHeap(int* array, int length) // Сортировка сформированной кучи.
{
	for (int element = length / 2; element >= 0; element--) // Формирование кучи.
	{
		Heap(array, element, length);
	}
	for (int element = length - 1; element >= 1; element--) // Сортировка сформированных частей кучи.
	{
		int temp = array[0]; // Меняем местами самый первый наибольший элемент с нижним меньшим.
		array[0] = array[element];
		array[element] = temp;

		Heap(array, 0, element); // После перемены элементов снова пробегаемся по куче и снова формируем её, поднимая наибольшие элементы вверх.
	}
}

int main() 
{
	setlocale(LC_ALL, "RUSSIAN");
	int length;
	cout << "Введите размер массива: ";
	cin >> length;
	int* array = CreateArray(length);
	cout << endl << "Исходный массив: ";
	Print(array,length);
	cout << endl;
	SortHeap(array, length);
	cout << "Отсортированный массив: ";
	Print(array,length);
}