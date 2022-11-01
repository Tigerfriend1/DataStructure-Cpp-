// template, last, AddSort함수를 구현하여 입력함과 동시에 sort할 수 있도록 구현.
#include <iostream>
#include <cstdlib>
using namespace std;


template <class T> class ListIterator;
template <class T> class CircularList;

template <class T>
class Node {
	friend class ListIterator<T>;
	friend class CircularList<T>;
public:
	Node(T elememt =0 , Node<T>* next = 0);
	~Node();
private:
	T num ;
	Node<T>* link;
};

template <class T>
class CircularList {
	friend class ListIterator<T>;
public:
    CircularList();
	~CircularList();
	void Add(T&);
	void AddSort(T&); //입력받으면서 동시에 sort할 수 있는 함수를 제작.
	virtual void Show();
    CircularList<T>& Merge(CircularList<T>&);
    //T Rand(); //난수생성기, 난수를 생성하여 AddSort함수에 넣는다.
	
private:
	Node<T>* last;
	Node<T>* head; //head node
};

template <class T>
class ListIterator {
public:
	ListIterator(const CircularList<T>& lst);
	~ListIterator();
	// bool NotNull();
	// bool NextNotNull();
	T* Last();
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
	const CircularList<T>& list;//existing list
};

template <class T>
Node<T>::Node(T element, Node<T>* next) {
	num = element;
	link = next;
}
template <class T>
Node<T>::~Node() {
}


template <class T>
CircularList<T>::CircularList() {
    head = new Node<T>(-1);
    last = new Node<T>(0);
	//head->num=-1;  //헤드의 값은 -1이다.
	head->link=head; //처음 헤드는 자기자신을 가르킨다.
    last=head;
}

template <class T>
CircularList<T>::~CircularList() { }



template <class T>
void CircularList<T>::Add(T& x) { //이건 정렬이 아닌 last위치에 넣는 Add함수
	Node<T>* p = this->last; //p는 현재 last위치의 node다.
	Node<T>* newNode = new Node<T>(x);
	p->link = newNode; // head를 가르키던 p는 이제 newNode를 가르킨다.
	newNode->link = this->head; //newNode를 head를 가르키게한다
	this->last= newNode; //last를 newNode를 가르키게 만든다.
}

template <class T>
void CircularList<T>::AddSort(T& x) { //입력 받으며 정렬하는 함수
	Node<T>* p = this->head->link; //헤드 다음번을 가르킴
	Node<T>* q = this->head; //헤드를 가르킴(p 한칸 뒤에서 따라감)
	Node<T>* newNode = new Node<T>(x);
	if (this->last->num<=x){ //last값 즉, 현재 가장 큰값보다 더 큰값일때
		p=this->last;
		newNode->link=this->head;
		p->link=newNode;
		this->last=newNode;
		return;
	}
	while(!(x>q->num && x<=p->num)){ //x값이 q와 p 사이에 올때까지 실행
		p=p->link; //한칸씩 전진
		q=q->link;
	}
	q->link=newNode; // q는 newNode를 가르킴
	newNode->link=p; // newNode는 p를 가르킴
	
}

template <class T>
void CircularList<T>::Show() {
	Node<T>* np;
	np = this->head->link;
	if (this->last->num > 0)
		do
		{
			cout << np->num << " ";
			np = np->link;
		} while (np != this->head);
	else cout << "List is empty" << endl;
}

template <class T>
CircularList<T>& CircularList<T>::Merge(CircularList<T>& l){
	CircularList<T> mlist;
	Node<T>* r = this->head; //r은 p나q를 따라감
    Node<T>* p = this->head->link; //p는 A의 첫번째 노드를 가르킴
	Node<T>* q = l.head->link; //q는 B의 첫번째 노드를 가르킴
    
    do
    {
		Node<T>* c;
        if((p->num <= q->num)&&p->num!=-1){ //A가 B보다 작으면
            c=r; //r값을 c에 백업
			r=p; //p의 현재값 받음
            p=p->link; //p는 한칸 전진
			r->link=c; //r값 뒤에 c를 붙임
			
        }
        else{
            c=r; //B가 A보다 값이 작으면
            r=q;
            q=q->link;
			r->link=c;
        }
        
        
        if((p==this->head)&&(q==l.head)){//p,q 모두 lastnode에 도착하면 탈출
            mlist.last = this -> last;
            break;
        }
    } while (1); 
    
    
    return mlist;
}

template <class T>
ListIterator<T>::ListIterator(const CircularList<T>& lst) :
	list(lst), current(lst.last) {
	cout << "List Iterator is constructed" << endl;
}

template <class T>
T* ListIterator<T>::Last() {
	return &list.last->num;
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

int main(){

	int value=10;
	
	
	CircularList<int> st[3];

    for (int i=0; i<3; i++){
        value=rand() % 20;      //난수를 생성하여 값을 AddSort에 넣음
        st[0].AddSort(value);      
    }
    cout<<"A is : ";
	st[0].Show();

    

    for (int i=0; i<3; i++){
        value=rand() % 20;      //난수를 생성하여 값을 AddSort에 넣음
        st[1].AddSort(value);      
    }
    cout<<endl<<"B is : ";
	st[1].Show();

    st[0].Merge(st[1]);

    st[2]=st[0];

    st[2].Show(); //merge
	//system("Pause");
    return 0;
}