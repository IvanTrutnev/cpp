#include <iostream>
using namespace std;

struct Element
{
	// Данные
	char data;
	// Адрес следующего элемента списка
	Element * Next;
};

// Односвязный список
class List
{
	// Адрес головного элемента списка
	Element * Head;
	// Адрес головного элемента списка
	Element * Tail;
	// Количество элементов списка
	int Count;

public:
	// Конструктор
	List();
	// Деструктор
	~List();

	// Добавление элемента в список
	// (Новый элемент становится последним)
	void Add(char data);

	// Удаление элемента списка
	// (Удаляется головной элемент)
	void Del();
	// Удаление всего списка
	void DelAll();

	// Распечатка содержимого списка
	// (Распечатка начинается с головного элемента)
	void Print();

	// Получение количества элементов, находящихся в списке
	int GetCount();

	//вставка элемента в заданную позицию.
	bool insert(int position, char data);
	//Удаление элемента по заданной позиции.
	void erase(int position);
	//поиск i-го элемента.
	int search(char data);
};

List::List()
{
	// Изначально список пуст
	Head = Tail = NULL;
	Count = 0;
}

List::~List()
{
	// Вызов функции удаления
	DelAll();
}

int List::GetCount()
{
	// Возвращаем количество элементов
	return Count;
}

void List::Add(char data)
{
	// создание нового элемента
	Element * temp = new Element;

	// заполнение данными
	temp->data = data;
	// следующий элемент отсутствует
	temp->Next = NULL;
	// новый элемент становится последним элементом списка
	// если он не первый добавленный
	if (Head != NULL){
		Tail->Next = temp;
		Tail = temp;
	}
	// новый элемент становится единственным
	// если он первый добавленный
	else{
		Head = Tail = temp;
	}

	Count++;
}

void List::Del()
{
	// запоминаем адрес головного элемента
	Element * temp = Head;
	// перебрасываем голову на следующий элемент
	Head = Head->Next;
	// удаляем бывший головной элемент
	delete temp;
}

void List::DelAll()
{
	// Пока еще есть элементы
	while (Head != 0)
		// Удаляем элементы по одному
		Del();
}

void List::Print()
{
	// запоминаем адрес головного элемента
	Element * temp = Head;
	// Пока еще есть элементы
	while (temp != 0)
	{
		// Выводим данные
		cout << temp->data << " ";
		// Переходим на следующий элемент
		temp = temp->Next;
	}

	cout << "\n\n";
}

//вставка элемента в заданную позицию.
bool List::insert(int position, char data){

	if (position<1 || position>Count)
	{
		cout << "Error!";
		exit(1);
	}

	if (position == 1){
		Element * ptr = Head;
		Head = new Element;
		Head->data = data;
		Head->Next = ptr;
	}

	else if (position == Count){
		Element * ptr = Tail;
		Tail = new Element;
		Tail->data = data;
		Tail->Next = NULL;
		ptr->Next = Tail;
	}

	else
	{
		Element * ptr = Head;
		int i = 1;
		while (i < position - 1){
			ptr = ptr->Next;
			i++;
		}

		Element * prev = ptr;
		Element * next = ptr->Next;
		Element * cur = new Element;
		prev->Next = cur;
		cur->data = data;
		cur->Next = next;
	}
	Count++;
}