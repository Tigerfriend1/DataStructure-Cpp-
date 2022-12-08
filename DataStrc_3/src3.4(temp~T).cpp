#include <iostream>
#include <memory>
#include <cstring>
#include <string>
using namespace std;

template <class T>
class Deque{
public:
    Deque(int DequeCapacity=2);
    bool IsEmpty();
    T& Front();
    T& Back();
    void push_front(T const& x);
    void push_back(T const& x);
    void pop_front();
    void pop_back();
    void show_data();
    
private:
    T* deque;
    int front;
    int back;
    int capacity;
    static int count; //원소의 개수를 static으로 표현
};

template <class T>
Deque<T>::Deque(int dequeCapacity) : capacity(dequeCapacity){
    deque= new T[capacity];
    front = 1;
    back = 0;
    //front와 back을 엇갈리게 하여 시작.(empty확인을 용이하게 하기 위함.)
}

template <class T>
bool Deque<T>::IsEmpty(){return front >back;} //front>back 시점이 비어있는 시점.

template <class T>
T& Deque<T>::Front(){
    if (IsEmpty()) throw "it is empty";
    return deque[front];
}

template <class T>
T& Deque<T>::Back(){
    if (IsEmpty()) throw "it is empty, back is empty";
    return deque[back];
}


template <class T>
void Deque<T>::push_front(T const& x){
    if (deque[0] !=""){ //emtpy check
        //index[0] is not empty -> should extend array!
        //capacity*2 and copy
        T* newDeque= new T[capacity*2];
        memcpy(newDeque+(capacity/3), deque, sizeof(T)*capacity); // 
        front=capacity/3;
        back=front+count-1;
        capacity*=2;
        //delete[] deque;
        deque=newDeque;
    }
    
    deque[--front] = x;
    count ++;
}

template <class T>
void Deque<T>::push_back(T const& x){
    if (deque[capacity-1] !=""){ //emtpy check
        //index[0] is not empty -> should extend array!
        //capacity*2 and copy
        T* newDeque= new T[capacity*2];
        memcpy(newDeque+(2*(capacity/3)-count+1), deque, sizeof(T)*capacity); 
        //back을 기준으로 복사하기 위함. 약2/3지점에서 front위치를 잡고 그 위치를 기준으로 복사.
        back=2*(capacity/3); // 약 2/3지점으로 이동
        front=back-count+1;
        capacity*=2;
        delete[] deque;
        deque=newDeque;
    }
    deque[++back]=x;
    count ++;
}

template <class T>
void Deque<T>::pop_front(){
    if(IsEmpty()) throw "Deque is empty! Can't delete.";
    count --;
    deque[front++].~T();
    
}

template <class T>
void Deque<T>::pop_back(){
    if(IsEmpty()) throw "Deque is empty! Can't delete.";
    count --;
    deque[back--].~T();
}

template <class T>
void Deque<T>::show_data(){
    printf("%d\n" ,count);
    for (int i=0; i<count; i++){
        printf("%s", &deque[i]);
    }
    printf("\n");
}

template <class T>
int Deque<T>::count = 0;

int main(){
    Deque<string> d; 
    for (int i=0; i<10; i++){
        //front와 back에 번갈아가며 push
        d.push_front("a");
        d.push_back("b");
    }
    

    if (d.IsEmpty()){
        cout<<"empty"<<endl;
    }
    else{
        cout<<"not empty"<<endl;
    }

    while (!d.IsEmpty()){
        d.show_data();
        cout<<"Front_pop is : "<<d.Front()<<endl;
        d.pop_front();
        cout<<"Back_pop is : "<<d.Back()<<endl;
        d.pop_back();
    }
    system("pause");
    return 0;
}
