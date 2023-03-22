//201624459_김태경 자료구조 기말고사 제출
//#pragma once

//기말고사
// 1. class Studernt 구현, treenode 데이터 Student 객체 사용
// 2. insert 후 출력(난수입력)
// 3. stackpostorder(); work 함수로 구현

#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int DefaultSize = 10;
enum Boolean { FALSE, TRUE };

class Student
{
	friend class Tree;
	friend class TreeNode;
	friend class Student;
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
	friend ostream& operator<<(ostream& os, Student& s);
	friend int operator==(const Student&, const Student&);
	friend int operator>(const Student&, const Student&);
public:
	Student(int si, float gr, int ag){
		sid = si;
		grade = gr;
		age = ag;
	}
private:
	int sid;
	float grade;
	int age;

};

int operator==(const Student& s, const Student& t) // 학생객체가 서로 같은지 확인하는 operator 오버로딩
{
	if(s.sid==t.sid){
		return 1;
	}
	else
	return 0;
	
}
int operator>(const Student& s, const Student& t){
	if(s.sid>t.sid){
		return 1;
	}
	else return 0;
}

ostream& operator<<(ostream& os, Student& s) {
		
		os << *s.Next() << endl;
		return os;
	}

template <class KeyType>
class Stack
{
public:
	Stack(int MaxStackSize = DefaultSize);

	Boolean IsFull();

	void Add(const KeyType& item);

	Boolean IsEmpty();

	KeyType* Delete(KeyType&);

	void StackEmpty() { cout << "empty" << endl; };
	void StackFull() { cout << "full" << endl; };
	void Output();
private:
	int top;
	KeyType* stack;
	int MaxSize;
};

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize)
{
	stack = new KeyType[MaxSize];
	top = -1;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsFull()
{
	if (top == MaxSize - 1) return TRUE;
	else return FALSE;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsEmpty()
{
	if (top == -1) return TRUE;
	else return FALSE;
}

template <class KeyType>
void Stack<KeyType>::Add(const KeyType& x)
{
	if (IsFull()) StackFull();
	else stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete(KeyType& x)
{
	if (IsEmpty()) { StackEmpty(); return 0; }
	x = stack[top--];
	return &x;
}

template <class KeyType>
void Stack<KeyType>::Output()
{
	cout << "top = " << top << endl;
	for (int i = 0; i <= top; i++)
		cout << i << ":" << stack[i] << endl;
}


template <class KeyType>
class Queue
{
	// \fBobjects\fR: A finite ordered list with zero or more elements.
public:
	Queue(int MaxQueueSize = 5);
	// Create an empty queue whose maximum size is \fIMaxQueueSize\fR

	bool IsFull();
	// if number of elements in the queue is equal to the maximum size of
	//   the queue, return TRUE (1); otherwise, return FALSE (0)

	void Add(const KeyType& item);
	// if IsFull(), then QueueFull(); else insert item into the top of the queue.

	bool IsEmpty();
	// if number of elements in the queue is equal to 0, return TRUE (1) else return FALSE (0).

	KeyType* Delete(KeyType&);
	// if IsEmpty(), then QueueEmpty(); else remove and return the topmost element of the Queue

	void QueueEmpty() { cout << "empty" << endl; };
	void QueueFull() { cout << "full" << endl; };
	void Output();
private:
	int front;
	int rear;
	KeyType* queue;
	int MaxSize;
};

template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) : MaxSize(MaxQueueSize)
{
	queue = new KeyType[MaxSize];
	front = rear = -1;
}

template <class KeyType>
inline bool  Queue<KeyType>::IsFull()
{
	if (rear == MaxSize - 1) return true;
	else return false;
}

template <class KeyType>
inline bool  Queue<KeyType>::IsEmpty()
{
	if (front == rear) return true;
	else return false;
}

template <class KeyType>
void Queue<KeyType>::Add(const KeyType& x)
// add x to the queue
{
	if (IsFull()) QueueFull();
	else queue[++rear] = x;
}

template <class KeyType>
KeyType* Queue<KeyType>::Delete(KeyType& x)
// remove and return front element from queue
{
	if (IsEmpty()) { QueueEmpty(); return 0; }
	x = queue[++front];
	return &x;
}

template <class KeyType>
void Queue<KeyType>::Output()
{
	cout << "front = " << front << "rear = " << rear << endl;
	for (int i = front + 1; i <= rear; i++)
		cout << i << ":" << queue[i] << endl;
}

class Tree;

class TreeNode {
	friend class Tree;
	friend class Student;
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
	
private:
	TreeNode* LeftChild;
	Student data;
	TreeNode* RightChild;

	TreeNode() {
		LeftChild = RightChild = 0;
	};

	TreeNode(Student ch, TreeNode* Lefty, TreeNode* Righty) {
		data = ch;
		LeftChild = Lefty;
		RightChild = Righty;
	}
};

class Tree {
	friend int operator==(const Tree&, const Tree&);
	friend class InorderIterator;
private:
	TreeNode* root;
	void inorder(TreeNode*);
	void stackpostorder(TreeNode*);
	TreeNode* copy(TreeNode*);
public:
	Tree(const Tree&);
	Tree() { root = 0; };
	void inorder();
	void stackpostorder();
	bool Insert(Student);
	int Delete(Student);
	Tree* Copy(); //void Copy(Tree&);
	
};


class InorderIterator {
	friend ostream& operator<<(ostream&, Tree&);
public:
	Student* Next();
	InorderIterator(Tree tree) : t(tree) {
		CurrentNode = t.root;
	};

private:
	Tree t;
	Stack<TreeNode*> s;
	TreeNode* CurrentNode;
};

ostream& operator<<(ostream& os, Tree& t) {
		InorderIterator tr(t);
		for (int i =0; i<30; i++){ 
			os << *tr.Next() << endl;
		}
		return os;
	}


Student* InorderIterator::Next()
{
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		Student& temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild;
		return &temp;
	}
	else return 1;
}

void Tree::inorder() //driving 함수
{
	inorder(root); //work 함수 / 오버로딩을 통해 구현
}


void Tree::stackpostorder()
{
	stackpostorder(root);
}

void Tree::inorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << " " << CurrentNode->data;
		inorder(CurrentNode->RightChild);
	}
}


void Tree::stackpostorder(root)
{
		Stack<TreeNode*> s;
		TreeNode* CurrentNode = root;
	while (1) {
		while (CurrentNode) {
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
		}
		if (!s.IsEmpty()) {
			CurrentNode = *s.Delete(CurrentNode);
			cout << CurrentNode->data << endl;
			CurrentNode = CurrentNode->RightChild;
		}
		else break;
	}
		cout << CurrentNode->data << " ";
}


Tree::Tree(const Tree& s)//copy constructor
{
	root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode* orignode)
{
	if (orignode) {
		TreeNode* temp = new TreeNode;
		temp->data = orignode->data;
		temp->LeftChild = copy(orignode->LeftChild);
		temp->RightChild = copy(orignode->RightChild);
		return temp;
	}
	else return 0;
}
// Driver
int operator==(const Tree& s, const Tree& t)
{
	return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode* a, TreeNode* b)
{
	if ((!a) && (!b)) return 1;  // both a and b are 0
	if (a && b &&                // both a and b are non-0
		(a->data == b->data)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}

bool Tree::Insert(Student x) {
	
		TreeNode* p = root;
		TreeNode* q = 0;
		while (p) {
			q = p;
			if (x == p->data) return false;
			if (x < p->data) p = p->LeftChild;
			else p = p->RightChild;
		}
		p = new TreeNode;
		p->LeftChild = p->RightChild = 0;
		p->data = x;
		if (!root) root = p;
		else if (x < q->data) q->LeftChild = p;
		else q->RightChild = p;
	
	return true;
}




int Tree::Delete(Student elm) {
	TreeNode* a = root->LeftChild;
	TreeNode* p = root;

	while(1){
		if(a->data< elm){ // operater > 오버로딩으로 sid를 비교하여 결정
			if(a->RightChild)
				return 0;
			p=a;
			a=a->RightChild;
		}
		else if(a->data > elm){
			if(a->LeftChild)
				return 0;
			p=a;
			a=a->LeftChild;
		}
		else{
			break;
		}
	}

	return 0;
}



int main(void)
{
	srand(time(NULL));
	Tree t;
	int eq = -1;
	int max = 0, x = 0;
	for (int i = 0; i<30; i++){ //30개의 Student객체를 Insert한다.
		Student x(rand()%100, (rand()%45)/10, rand()%30);
		cout << x <<endl; //student 객체 출력
		t.Insert(x); // insert후 출력
	}
	int delete(x);
	void stackpostorder(); // stackpostorder 출력 //work함수형식으로 구현
	
	system("pause");
	return 0;
}
