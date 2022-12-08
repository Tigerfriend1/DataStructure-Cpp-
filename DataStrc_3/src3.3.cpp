#include <iostream>
#include <memory>
#include <cstring>
using namespace std;

template <class T>
class Queue{
public:
    Queue(int queueCapacity=10);
    bool IsEmpty();
    T& Front();
    T& Rear();
    void Push(T const& x);
    void Pop();
private:
    T* queue;
    int front;
    int rear;
    int capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity){
    queue= new T[capacity];
    front = rear = -1;
}

template <class T>
bool Queue<T>::IsEmpty(){return front ==rear;}

template <class T>
T& Queue<T>::Front(){
    if (IsEmpty()) throw "it is empty";
    return queue[front];
}

template <class T>
T& Queue<T>::Rear(){
    if (IsEmpty()) threow "it is empty, rear is empty";
    return queue[rear];
}

template <class T>
void Queue<T>::Push(T const& x){
    
}