﻿//소스코드 5.1: binary tree
//#pragma once
//make a binary tree 

//split(), delete()

#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int DefaultSize = 10;
enum Boolean { FALSE, TRUE };

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
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
private:
	TreeNode* LeftChild;
	int data;
	TreeNode* RightChild;

	TreeNode() {
		LeftChild = RightChild = 0;
	};

	TreeNode(int ch, TreeNode* Lefty, TreeNode* Righty) {
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
	void preorder(TreeNode*);
	void postorder(TreeNode*);
	TreeNode* copy(TreeNode*);
public:
	Tree(const Tree&);
	Tree() { root = 0; };

	bool Insert(int);
	void Split(int i, Tree& B, Tree& C, int& x);
	int Delete(int);//임의 값 x를 delete하는 구현 실습
	void inorder();
	void preorder();
	void postorder();
	void NoStackInorder();
	void NonrecInorder();
	void LevelOrder();
	Tree* Copy(); //void Copy(Tree&);
	TreeNode* InorderSucc(TreeNode*);
};
TreeNode* Tree::InorderSucc(TreeNode* current)
{
	TreeNode* temp = current->RightChild;
	if (current->RightChild != NULL)
		while (temp->LeftChild != NULL) temp = temp->LeftChild;
	return temp;
}

class InorderIterator {
public:
	int* Next();
	InorderIterator(Tree tree) : t(tree) {
		CurrentNode = t.root;
	};

private:
	Tree t;
	Stack<TreeNode*> s;
	TreeNode* CurrentNode;
};


int* InorderIterator::Next()
{
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		int& temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild;
		return &temp;
	}
	else return 0;
}

void Tree::inorder() //driving 함수
{
	inorder(root); //work 함수 / 오버로딩을 통해 구현
}

void Tree::preorder()
{
	preorder(root);
}

void Tree::postorder()
{
	postorder(root);
}

void Tree::inorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << " " << CurrentNode->data;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
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
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{
	if ((!a) && (!b)) return 1;  // both a and b are 0
	if (a && b &&                // both a and b are non-0
		(a->data == b->data)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}

bool Tree::Insert(int x) {//binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을 설계하여 구현
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

void Tree::Split(int i, Tree& B, Tree& C, int& x)

{

	if (!root) {// empty tree

		B.root = C.root = 0; x = 0;

		return;

	}



	int mode = 0;

	TreeNode* prev = root;

	TreeNode* current = root;

	C.root = root;

	while (current)

		if (i == current->data) {  // split at t

			if (current == root) {

				x = current->data;

				B.root = current->LeftChild; 

				C.root = current->RightChild;

				return;

			}

			if (mode == 0) {//left child을 뜯어 낸다

				prev->LeftChild = current->RightChild;

				B.root = current->LeftChild;

				

			}

			else {

				prev->RightChild = current->LeftChild;

				B.root = current->RightChild;



			}

			C.root = root;

			x = current->data;

			return;

		}

		else if (i < current->data) {

			prev = current;

			mode = 0;

			current = current->LeftChild;

		}

		else {

			prev = current;

			mode = 1;

			current = current->RightChild;

		}



	return;

}
int Tree::Delete(int elm) {
	TreeNode* a = root->LeftChild;
	TreeNode* p = root;

	while(1){
		if(a->data < elm){
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

void Tree::NonrecInorder()//void Tree::inorder(TreeNode *CurrentNode)와 비교
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
}
void Tree::LevelOrder()
{
	Queue <TreeNode*> q;
	TreeNode* CurrentNode = root;
	while (CurrentNode) {
		cout << CurrentNode->data << endl;
		if (CurrentNode->LeftChild)
			q.Add(CurrentNode->LeftChild);
		if (CurrentNode->RightChild)
			q.Add(CurrentNode->RightChild);
		CurrentNode = *q.Delete(CurrentNode);
	}
}
void Tree::NoStackInorder() //inorder()와 비교
{
	if (!root) return;
	TreeNode* top = 0, * LastRight = 0, * p, * q, * r, * r1;//local variable이 key point
	p = q = root;
	while (1) {
		while (1) {
			if ((!p->LeftChild) && (!p->RightChild)) {
				cout << p->data; break;
			}
			if (!p->LeftChild) {
				cout << p->data;
				r = p->RightChild; p->RightChild = q;
				q = p; p = r;
			}
			else {
				r = p->LeftChild; p->LeftChild = q;
				q = p; p = r;
			}
		}
		TreeNode* av = p;
		while (1) {
			if (p == root) return;
			if (!q->LeftChild) {
				r = q->RightChild; q->RightChild = p;
				p = q; q = r;
			}
			else if (!q->RightChild) {
				r = q->LeftChild; q->LeftChild = p;
				p = q; q = r; cout << p->data;
			}
			else
				if (q == LastRight) {
					r = top; LastRight = r->LeftChild;
					top = r->RightChild;
					r->LeftChild = r->RightChild = 0;
					r = q->RightChild; q->RightChild = p;
					p = q; q = r;
				}
				else {
					cout << q->data;
					av->LeftChild = LastRight; av->RightChild = top;
					top = av; LastRight = q;
					r = q->LeftChild; q->LeftChild = p;
					r1 = q->RightChild; q->RightChild = r;
					p = r1;
					break;
				}
		}
	}
}


int main(void)
{
	srand(time(NULL));
	Tree t;
	int eq = -1;
	char select = 'i';
	int max = 0, x = 0;
	while (select != 'q')
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select i:Insert, r: remove, d:Display, e:NonrecInorder, f:preorder, g:postorder, h:copy and compare, q : Quit =>";
		cin >> select;
		switch (select)
		{
		case 'i':
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				rnd = rand() / 10;
				if (!t.Insert(rnd)) cout << "Insert Duplicated data" << endl;
			}

			break;
		case 'r':
			int x;
			cin >> x;
			cout << t.Delete(x);//입력된 x에 대한 tree 노드를 찾아 삭제한다.
			cout << endl;
			break;
		case 'd':
			t.inorder();
			cout << endl;
			break;
		case 'e':
			t.NonrecInorder();
			break;
		case 'f':
			t.preorder();
			break;
		case 'g':
			t.postorder();
			break;
		case 'h':
			eq = (t == Tree(t));//copy constructor를 호출
			if (eq) {
				cout << "compare result: true" << endl;
			}
			else
				cout << "compare result: false" << endl;
			break;
		case 'q':
			cout << "Quit" << endl;
			break;

		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}
