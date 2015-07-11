#include <iostream>
using namespace std;

struct Element
{
	// ������
	char data;
	// ����� ���������� �������� ������
	Element * Next;
};

// ����������� ������
class List
{
	// ����� ��������� �������� ������
	Element * Head;
	// ����� ��������� �������� ������
	Element * Tail;
	// ���������� ��������� ������
	int Count;

public:
	// �����������
	List();
	// ����������
	~List();

	// ���������� �������� � ������
	// (����� ������� ���������� ���������)
	void Add(char data);

	// �������� �������� ������
	// (��������� �������� �������)
	void Del();
	// �������� ����� ������
	void DelAll();

	// ���������� ����������� ������
	// (���������� ���������� � ��������� ��������)
	void Print();

	// ��������� ���������� ���������, ����������� � ������
	int GetCount();

	//������� �������� � �������� �������.
	bool insert(int position, char data);
	//�������� �������� �� �������� �������.
	void erase(int position);
	//����� i-�� ��������.
	int search(char data);
};

List::List()
{
	// ���������� ������ ����
	Head = Tail = NULL;
	Count = 0;
}

List::~List()
{
	// ����� ������� ��������
	DelAll();
}

int List::GetCount()
{
	// ���������� ���������� ���������
	return Count;
}

void List::Add(char data)
{
	// �������� ������ ��������
	Element * temp = new Element;

	// ���������� �������
	temp->data = data;
	// ��������� ������� �����������
	temp->Next = NULL;
	// ����� ������� ���������� ��������� ��������� ������
	// ���� �� �� ������ �����������
	if (Head != NULL){
		Tail->Next = temp;
		Tail = temp;
	}
	// ����� ������� ���������� ������������
	// ���� �� ������ �����������
	else{
		Head = Tail = temp;
	}

	Count++;
}

void List::Del()
{
	// ���������� ����� ��������� ��������
	Element * temp = Head;
	// ������������� ������ �� ��������� �������
	Head = Head->Next;
	// ������� ������ �������� �������
	delete temp;
}

void List::DelAll()
{
	// ���� ��� ���� ��������
	while (Head != 0)
		// ������� �������� �� ������
		Del();
}

void List::Print()
{
	// ���������� ����� ��������� ��������
	Element * temp = Head;
	// ���� ��� ���� ��������
	while (temp != 0)
	{
		// ������� ������
		cout << temp->data << " ";
		// ��������� �� ��������� �������
		temp = temp->Next;
	}

	cout << "\n\n";
}

//������� �������� � �������� �������.
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