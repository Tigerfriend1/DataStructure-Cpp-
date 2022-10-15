//소스 코드4.2: Circular Linked List - template 버젼으로 전환하기 
//head node를 갖고 circular list로서   class List{ private: Node *last;}로 구현하기
//난수가 입력되면 정렬된 list를 만든다.
//두개의 list를 merge하여 정렬된 list를 만든다.
// 출력은 iterator를 사용한다.
// class Node, List, ListIterator
#include <iostream>
using namespace std;

template <class T> class List;
template <class T> class ListIterator;
template <class T> class CircularList;

template <class T>
class Node {
	friend class List<T>;
	friend class ListIterator<T>;
	friend class CircularList<T>;
public:
	Node(T elememt =0 , Node<T>* next = 0);
	~Node();
private:
	T num;
	Node<T>* link;
};

template <class T>
class List {
	friend class ListIterator<T>;
	friend class CircularList<T>;
public:
	List();
	~List();
	virtual void Add(T&);
	virtual void Delete(T&);//주어진 x 값을 갖는 노드를 삭제
	virtual void Show();
	//int Length( ); //count the number of nodes in a list
	//void Merge(List&, List&);//the merged nodes in a sequential order
private:
	Node<T>* first;
};

template <class T>
class ListIterator {
public:
	ListIterator(const List<T>& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	T* First();
	T* Next();
	T& operator*() const;
	T* operator->()const;
	ListIterator& operator++(); //Next( )
	ListIterator operator ++(T);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	T* GetCurrent();
private:
	Node<T>* current; //pointer to nodes
	const List<T>& list;//existing list
};

template <class T>
class CircularList : public List<T> {
public:
	CircularList();
	~CircularList();
	void Add(T&);
	void Delete(T&);
	void Show();
	void DeleteNum(T& x);
};

//#include "listiterator.h"
template <class T>
Node<T>::Node(T element, Node* next) {
	num = element;
	link = next;
}
template <class T>
Node<T>::~Node() {
}

template <class T>
List<T>::List() {
	first = 0;
}

template <class T>
List<T>::~List() {
}

template <class T>
void List<T>::Add(T& x) {
	if (!first) {
		first = new Node<T>(x);
		first->link = 0;
	}
	else {
		Node<T>* n = new Node<T>(x);
		n->link = first;
		first = n;
	}
}

template <class T>
void List<T>::Delete(T& x) {
	if (first == NULL) cout << " List is empty" << endl;
	// body of delete
	return;
}

template <class T>
void List<T>::Show() {
	Node<T>* current;
	current = first;
	if (first)
		while (current)
		{
			cout << current->num << " ";
			current = current->link;
		}
	else cout << "List is empty" << endl;
}

/*
ListIterator::ListIterator(Node *ll){
}
*/

template <class T>
ListIterator<T>::ListIterator(const List<T>& lst) :
	list(lst), current(lst.first) {
	cout << "List Iterator is constructed" << endl;
}

template <class T>
bool ListIterator<T>::NotNull() {
	if (list.first == 0) return false;
}

template <class T>
bool ListIterator<T>::NextNotNull() {
	if (current->link != 0) return true;
	else return false;
}

template <class T>
T* ListIterator<T>::First() {
	return &list.first->num;
}

template <class T>
T* ListIterator<T>::Next() {
	current = current->link;
	cout << "current = " << current->num;
	return &current->num;
}

template <class T>
T* ListIterator<T>::GetCurrent() {
	return &current->num;
}

template <class T>
ListIterator<T>::~ListIterator() {
}

template <class T>
T& ListIterator<T>::operator*() const {
	return current->num;
}

template <class T>
T* ListIterator<T>::operator->()const {
	return &current->num;
}

template <class T>
ListIterator<T>& ListIterator<T>::operator++() {
	current = current->link;
	return *this;
}

template <class T>
ListIterator<T> ListIterator<T>::operator ++(T) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

template <class T>
bool ListIterator<T>::operator != (const ListIterator<T> right) const {
	return current != right.current;
}

template <class T>
bool ListIterator<T>::operator == (const ListIterator<T> right) const {
	return current == right.current;
}

template <class T>
CircularList<T>::CircularList() : List<T>() { }

template <class T>
CircularList<T>::~CircularList() { }

template <class T>
void CircularList<T>::Add(T& x) {
	Node<T>* newNode = new Node<T>(x);
	if (this->first) { //nonempty list
		newNode->link = this->first->link;
		this->first->link = newNode;
	}
	else { //empty list
		this->first = newNode;
		newNode->link = newNode;
	}
}

template <class T>
void CircularList<T>::Delete(T& x) {
	Node<T>* newNode = new Node<T>(x);
	if (this->first) { //nonempty list
		Node<T>* Temp = this->first->link;
		this->first->link = this->first->link->link;
		delete Temp;
	}
	else { //empty list
		cout << "empty list" << endl;
	}
}

template <class T>
void CircularList<T>::DeleteNum(T& x) {
	//Node *newNode = new Node(x);
	//first, medium, last üũ
	if (this->first) { //nonempty list
		Node<T>* CurrentNode = this->first;
		Node<T>* PreNode = this->first;
		bool find = false;

		//while (CurrentNode->link != first || CurrentNode == first)
		while (CurrentNode->link != this->first)
		{
			if (CurrentNode->num == x)
			{
				find = true;

				if (CurrentNode == this->first) // first delete case
				{
					Node<T>* Temp = CurrentNode;

					while (CurrentNode->link != this->first)
					{
						CurrentNode = CurrentNode->link;
					}
					this->first = this->first->link;
					delete Temp;

					CurrentNode->link = this->first;
					break;
				}
				else if (CurrentNode->link != this->first) // medium delete case
				{
					PreNode->link = CurrentNode->link;
					delete CurrentNode;
					break;
				}
			}

			PreNode = CurrentNode;
			CurrentNode = CurrentNode->link;
		}//while end

		if (find == false)
		{
			if (CurrentNode->num == x) // last Delte Case
			{
				PreNode->link = this->first;
				delete CurrentNode;
				find = true;
			}

		}
		if (find == false)
			cout << "can't find " << x << endl;
	}
	else { //empty list
		cout << "empty list" << endl;
	}

}

template <class T>
void CircularList<T>::Show() {
	Node<T>* np;
	np = this->first;
	if (np->num > 0)
		do
		{
			cout << np->num << " ";
			np = np->link;
		} while (np != this->first);
	else cout << "List is empty" << endl;
}

/* listIteratorTest.cpp - List Iterator를 사용
- Add( )에서 학생들이 실습할 코드로
  1) add된 데이터를 last node로 추가하는 코드 작성,
  2) 입력된 값이 sort되도록 add( )를 수정
  3) sum(xi * xi+5)를 구하는 코드 작성
*/

//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습

template <class T>
T sum(const List<T>& l)
{
	ListIterator<T> li(l);
	if (!li.NotNull()) return 0;
	int retvalue = *li.First();
	while (li.NextNotNull() == true) {
		++li;//current를 증가시킴
		//retvalue = retvalue + *li.Next( );
		retvalue = retvalue + *li.GetCurrent();//현재 current가 가르키는 node의 값을 가져옴
	}
	return retvalue;
}


template <class T>
double avg(const List<T>& l)
{
	ListIterator<T> li(l);
	if (!li.NotNull()) return 0;
	int retvalue = *li.First();
	int count = 1;
	while (li.NextNotNull() == true) {
		++li;
		count++;
		//retvalue = retvalue + *li.Next( );
		retvalue = retvalue + *li.GetCurrent();
	}

	double result = (double)retvalue / count;

	return result;
}


template <class T>
T min(const List<T>& l)
{
	ListIterator<T> li(l);
	if (!li.NotNull()) return -1;
	int minValue = *li.First();

	while (li.NextNotNull() == true) {
		++li;
		if (minValue > * li.GetCurrent())
		{
			minValue = *li.GetCurrent();
		}
	}
	return minValue;
}


template <class T>
T max(const List<T>& l)
{
	ListIterator<T> li(l);
	if (!li.NotNull()) return -1;
	int maxValue = *li.First();

	while (li.NextNotNull() == true) {
		++li;
		if (maxValue < *li.GetCurrent())
		{
			maxValue = *li.GetCurrent();
		}
	}
	return maxValue;
}

template <class T>
void ListTesting() {
	int ch;
	List<T> st;
	while (1)
	{
		cout << "\n1.Add  2.Delete  3.Show  4. sum 5.avg 6.min 7.max 8.exit\nEnter ur choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:  cout << "enter the element ";
			cin >> ch;
			st.Add(ch);
			break;
		case 2:  st.Delete(ch);  break;
		case 3:  st.Show(); break;
		case 4:  cout << "sum( ) = " << sum(st) << endl; break;
		case 5:  cout << "avg( ) = " << avg(st) << endl; break;
		case 6:  cout << "min( ) = " << min(st) << endl; break;
		case 7:  cout << "max( ) = " << max(st) << endl; break;
		case 8:  return;
		}
	}

	return;
}


template <class T>
int main() {
    int ch;
	cout << endl << "List Testing begins: " << endl;
	CircularList<int> st[4];
	while (1)
	{
		cout << "\n1.Make_List1  2.Make_List 3.Merge  4.Print_List  5.exit\nEnter ur choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:	
			Make_List(st[0]);
			break;
		case 2:
			Make_List(st[1]);
			break;
		case 3:	
			st[2] = st[0].Merge(st[1]);
			break;
		case 4:
			Print_List(st[0]);
			Print_List(st[1]);
			Print_List(st[3]);
			break;
		case 5:	return;
		}
	}
	system("Pause");
    return 0;
}