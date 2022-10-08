//Bag 자료구조 구현
#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100

template <class T>
class Bag{
public:
    Bag(int bagCapacity=10);
    ~Bag();
    bool IsFull();
    int Size() const;
    bool IsEmpty() const;
    virtual T& Pop() ;
    virtual void Push(const T&); 
    //virtual로 compile때가 아닌 run할때를 기준으로 실행되게 함.

private:
    T* array; 
    int capacity;
    int top;
};

template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity){
    if (capacity<1)
        throw "Capacity must be > 0 and end.!!";
    array = new T[capacity];
    top = -1; // = empty
}

template <class T>
Bag<T>::~Bag(){
    delete[] array;
}

template <class T>
void ChangeSizeID(T*& a, int oldsize, int newsize){
    if(newsize<0) throw "new length must be>=0"; //새로 만들 배열은 음수가 될 수 없다.

    T* temp = new T[newsize];   //새로 만들 사이즈 temp배열 생성
    int number=oldsize;    //복사할 사이즈 : number
    if(oldsize>newsize) number=newsize; // 배열크기 초과 복사에 의한 오버플로우 방지
    memcpy(temp, a, sizeof(int)*number); // temp에 a의 number사이즈만큼 복사
    delete[] a; //a배열 삭제 한 후 temp복사.
    a=temp;

}

template <class T>
int Bag<T>::Size() const{
    return top+1; // 배열 끝 index인 top+1
}

template <class T>
bool Bag<T>::IsEmpty() const{
    return top<0; //top = -1이라면 empty true
}

template <class T>
void Bag<T>::Push(const T& x){
    if(top>capacity-1){
        ChangeSizeID(array, capacity, capacity*2);
        capacity=capacity*2;
    }
    array[++top]=x;
    //현재 채워진 부분 +1번째에 입력값 x를 push
}

template <class T>
T& Bag<T>::Pop() {
    T popValue;
    int deletepoint = top / 2;
    popValue=array[deletepoint];
    memcpy(array+deletepoint, array+deletepoint+1, sizeof(int)*top-deletepoint);
    //pop한 인덱스 다음부터 top-dp만큼 복사
    top--;
    return popValue;

}


template <class T>
inline bool Bag<T>::IsFull(){ 
    if(top==MaxSize-1){ //정의된 MaxSize 100-1이랑 top index가 같으면 full상태이니 true출력
        return true;
    }
    else return false;
}


int main(){
    Bag<int> b(4);
    int N;
    for (int i=0;i<4;i++){
        cin >> N;
        b.Push(N);
    }

    if(b.IsEmpty()){
        cout<<"it's empty!"<<endl;
    }
    else {
        cout<<"it's not empty"<<endl;
    }

    while (!b.IsEmpty()){
        cout<<b.Pop()<<endl;
    }
    system("pause");
    return 0;
}