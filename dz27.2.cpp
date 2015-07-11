
Владислав Гончарук
Задание №2.Реализовать шаблонный класс "Очередь" на основе двусвязного списка.

#include <iostream>
using namespace std;

//реализовать очередь на основе шаблонного двухсвязного списка.

template <typename T>
struct Element{
	T mData;
	Element *mPrev, *mNext;
};

template <typename T>
class ListQueue {
	Element<T> *mHead, *mTail;
	T mData;
	int mCount;

	void DelAll();
	void AddTail(T data);
	void AddHead(T data);
	void AddSomeWhere(int pos, T data);
	void DelTail();

public:
	ListQueue();
	void Add(T data);
	Element<T> Extract();
	bool Empty();
	void Print();
	~ListQueue();
};

template<typename T>
ListQueue<T>::ListQueue()
{
	mHead = mTail = NULL;
	mCount = 0;
}

template<typename T>
ListQueue<T>::~ListQueue()
{
	DelAll();
}

template<typename T>
void ListQueue<T>::DelAll(){
	Element<T> * ptr;
	while (mCount != 0)
	{
		ptr = mHead;
		mHead = mHead->mNext;
		delete ptr;
		mCount--;
	}
}

template<typename T>
void ListQueue<T>::AddTail(T data){
	Element<T> * ptr = new Element < T > ;

	mTail->mNext = ptr;
	ptr->mPrev = mTail;
	ptr->mNext = NULL;
	Tail = ptr;

	Count++;
}

template<typename T>
void ListQueue<T>::AddHead(T data){
	Element<T> * ptr = new Element < T > ;

	if (mCount == 0)
	{
		mHead = ptr;
		mTail = ptr;
		ptr->mData = data;
		ptr->mNext = NULL;
		ptr->mPrev = NULL;
		mCount++;
	}
	else
	{
		mHead->mPrev = ptr;
		ptr->mNext = mHead;
		ptr->mData = data;
		ptr->mPrev = NULL;
		mHead = ptr;
		mCount++;
	}
}

template<typename T>
void ListQueue<T>::AddSomeWhere(int pos, T data){

	if (position<0 || position>Count)
	{
		cout << "\n\nError!\n\n";
		exit(1);
	}

	if (position == 0){
		AddHead(data);
	}

	else if (position == Count - 1){
		AddTail(data);
	}

	else
	{
		Element<T> * ptr = Head;
		int i = 0;
		while (i < position){
			ptr = ptr->Next;
			i++;
		}

		Element<T> * prev = ptr;
		Element<T> * next = ptr->Next;
		Element<T> * cur = new Element;
		prev->Next = cur;
		cur->data = data;
		cur->mPrev = prev;
		cur->Next = next;
		next->mPrev = cur;
	}
	Count++;
}

template<typename T>
bool ListQueue<T>::Empty()
{
	if (mCount == 0)return true;
	else return false;
}

template<typename T>
void ListQueue<T>::Add(T data)
{
	AddHead(data);
}

template<typename T>
Element<T> ListQueue<T>::Extract()
{
	Element<T>tmp;

	if (!Empty())
	{
		tmp.mData = mTail->mData;
		tmp.mNext = mTail->mNext;
		tmp.mPrev = mTail->mPrev;

		DelTail();
		return tmp;
	}
	else
	{
		return tmp;
	}
}

template<typename T>
void ListQueue<T>::DelTail(){

	if (mCount == 1)
	{
		delete mTail;
		mTail = NULL;
		mHead = NULL;
	}
	else
	{
		Element<T> * ptr = mTail->mPrev;
		ptr->mNext = NULL;
		delete mTail;
		mTail = ptr;
	}

	mCount--;
}

template<typename T>
void ListQueue<T>::Print()
{
	Element<T> * ptr = mHead;

	while (ptr != 0)
	{
		cout << ptr->mData;
		ptr = ptr->mNext;
	}

	cout << "\n\n";
}