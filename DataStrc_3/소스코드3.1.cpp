	//�ҽ��ڵ�3.1: Bag �ڷᱸ��
#pragma once
#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100
template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();
	bool IsFull();
	int Size() const;
	bool IsEmpty() const;
	virtual T& Pop();
	virtual void Push(const T&);
private:
	T* array;
	int capacity;
	int top;
};
//Visual Studio2019���� bag.h, bag.cpp�� �и����� �ʾƾ� ��
template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity)
{
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag() { delete[] array; }

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, sizeof(int)*(number));
	delete[] a;
	a = temp;
}

template <class T>
int Bag<T>::Size() const {
	return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const {
	return top < 0;
}

template <class T>
void Bag<T>::Push(const T& x)
{
	if (top == capacity - 1)
		// ���� ������ ordering ���¿��� push�Ѵ�. non-ordering�ǰ� push�� �����ϰ� ����
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

template <class T>
T& Bag<T>::Pop()
{
	T retValue;
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top / 2;
	retValue = array[deletePos];
	// �ǽ� ����: no ordering���·� pop�ǰ� ����
	//copy(array + deletePos + 1, array + top + 1, array + deletePos);
	memcpy(array+deletePos, array + deletePos+1, sizeof(int) * (top - deletePos));
	top--;
	return retValue;
}

template <class T>
inline bool Bag<T>::IsFull()
{
	if (top == MaxSize - 1) return TRUE;
	else return FALSE;
}
int main() {
	Bag<int> b(4);
	//Bag<float> fo(10);�� ���Ͽ��� ������ ��
	//ȭ�鿡�� ���� ���ڸ� �Է¹޾� Push() ȣ���ϵ��� ����
	b.Push(3);	b.Push(5); b.Push(1); b.Push(6); b.Push(7); b.Push(9);
	//cin >> b; //�����ϰ� ����
	if (b.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}

	while (!b.IsEmpty()) {
		cout << b.Pop() << endl;
	}
	//cout << b; //�����ϰ� ����
	system("pause");
	return 0;
}