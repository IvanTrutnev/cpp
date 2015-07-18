//Перепишите класс stack одного из предыдущих домашних заданий таким образом
//, чтобы генерировать исключения для такого количества условий, какое Вы считаете приемлемым.
//(Например, невозможность выделить нужное количество памяти, переполнение стека и т.д.)
// Демонстрация двух исключений
#include<iostream>
using namespace std;
const int MAX = 3;
class Stack
{
private:
	int st[MAX];
	int top;
public:
	class Full {};   //класс исключения
	class Empty {};  //класс исключения
	Stack()          //конструктор
	{
		top = -1;
	}
	void push(int var)   //занести числ в стек
	{
		if (top >= MAX - 1)  //если стек полон,генерировать исключение Full
			throw Full();
		st[++top] = var;
	}
	int pop()   // взять число из стека
	{
		if (top < 0)    //если стек пуст,генерировать исключение Empty
			throw Empty();
		return st[top--];
	}

};
int main()
{
	setlocale(LC_ALL, "Russian");
	Stack s1;
	try
	{
		s1.push(11);
		s1.push(22);
		s1.push(33);
		//s1.push(44);     // стек переволнен
		cout << "1: " << s1.pop() << endl;
		cout << "2: " << s1.pop() << endl;
		cout << "3: " << s1.pop() << endl;
		cout << "4: " << s1.pop() << endl;   //стек пуст
	}
	catch (Stack::Full)
	{
		cout << "Ошибка:переполнение стека" << endl;
	}
	catch (Stack::Empty)
	{
		cout << "Ошибка:стек пуст" << endl;
	}
	return 0;
}

