#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

template <class T>
class Stack{
public:
    Stack(int stackCapacity=10);
    bool IsEmpty();
    bool IsFull();
    T& Top();
    void Push(const T& item);
    T& Pop();
private:
    T* stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity){
    if(capacity<1) throw "stackcapacity must be >0";
    T* stack=new T[capacity];
    top=-1;
}


template <class T>
bool Stack<T>::IsEmpty(){
    if(top<0) return true;
    else return false;
}

template <class T>
bool Stack<T>::IsFull(){
    if(top==capacity-1) return true;
    else return false;
}

template <class T>
void ChangeSizeID(T*& a, int oldSize, int newSize){
    T* temp = new T[newSize];
    int number = oldSize;
    if(oldSize > newSize) number=newSize;
    memcpy(temp,a,sizeof(int)*number);
    delete[] a;
    a = temp;
}

template <class T>
void Stack<T>::Push(const T& item){
    if (IsFull()==true){
        ChangeSizeID(stack, capacity, capacity*2);
        capacity *= 2;
    }
    stack[++top]=item;
}

template <class T>
T& Stack<T>::Pop(){
    if(IsEmpty()==true) throw "stack is empty!";

    T deletePos;
    deletePos=top;
    memcpy(stack,stack,top);
    top--;
    return deletePos;
}

template <class T>
T& Stack<T>::Top(){
    if (IsEmpty()==true) throw "stack is empty!";
    return stack[top];
}


int main(){
    Stack<int> s(4);
    int N;
    for (int i=0; i<4;i++){
        cin >> N;
        s.Push(N);
    }

    if (s.IsEmpty()) cout<<"it is empty"<<endl;
    else cout<< "it is not empty"<<endl;

    while (!s.IsEmpty()){
        cout << s.Top()<<endl;
        cout<< s.Pop()<<endl;
    }

    return 0;

}



