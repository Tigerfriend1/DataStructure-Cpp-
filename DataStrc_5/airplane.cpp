//heap/priority를 통해 airport landing and takeoff를 simulating 하는 프로그램 제작 
// 이,착륙 class(display, Insert, DeleteLandOver/DeleteTakeoff)구현
// 이, 착륙 대기시간 비교함수 미구현
#include <iostream>
#include <time.h>

using namespace std;

const int APmax=1000;

class AirPlane{
    friend class LaningQ;
    friend class LandingHeap;
    friend class TakeoffQ;
    friend class TakeoffHeap;
    private:
     char airId;
     char airName;
     char usingType;
     int remainingTime;
     int landingTime;
     int takeoffTime;
    public:
     AirPlane(int remainingTime) : remainingTime(remainingTime){}
     
};

class LandingQ{
    virtual void Insert(const AirPlane&)=0;
    virtual AirPlane* DeleteLandOver(AirPlane&)=0;
};
class LandingHeap{
    public:
        LandingHeap(int sz = APmax)
        {
            MaxSize=sz;
            n=0;
            Landing = new AirPlane[MaxSize+1]; //착륙대기 비행기
        };
        void display();
        void Insert(const AirPlane& x);
        AirPlane* DeleteLandOver(AirPlane&);
    private:
        AirPlane* Landing;
        int n;
        int MaxSize;
        void LandingEmpty(){cout<<"Landing Q is empty!!"<<endl;};
        void LandingFull(){cout<<"Landing Q is Full!!"<<endl;};
};

void LandingHeap::display(){ //airId와 airName을 출력
    for(int i=1; i<=n; i++){
        cout<<"("<<i<<", "<<Landing[i].airId<<", "<<Landing[i].airName<<endl;
    }
}

void LandingHeap::Insert(const AirPlane& x){ //landingTime을 남은 시간과 비교해서 넣음.
    if (n==MaxSize){LandingFull(); return;}
    n++;
    int i;
    for(i=n; 1;){
        if(i==1) break;
        if(x.remainingTime < Landing[i/2].remainingTime) break;
        Landing[i]=Landing[i/2];
        i /= 2;
    }
    Landing[i]=x;
}

AirPlane* LandingHeap::DeleteLandOver(AirPlane& x){ //착륙한 비행기를 삭제
    int i,j;
    if(!n) {LandingEmpty(); return 0;}
    x = Landing[1];
    AirPlane k =Landing[n];
    n--;

    for (i=1, j=2; j<=n;){
        if(j<n) {
            if(Landing[j].remainingTime<Landing[j+1].remainingTime) j++;
        }
        if(k.remainingTime>=Landing->remainingTime) break;
        Landing[i]=Landing[j];
        i=j;
        j*=2;
    }
    Landing[i]=k;
    return &x;

}

class TakeoffQ{
    virtual void Insert(const AirPlane&)=0;
    virtual AirPlane* DeleteTakeoff(AirPlane&)=0;
};
class TakeoffHeap{
public:
        TakeoffHeap(int sz = APmax)
        {
            MaxSize=sz;
            n=0;
            Takingoff = new AirPlane[MaxSize+1]; //이륙대기 비행기
        };
        void display();
        void Insert(const AirPlane& x);
        AirPlane* DeleteTakeoff(AirPlane&);
    private:
        AirPlane* Takingoff;
        int n;
        int MaxSize;
        void TakeoffEmpty(){cout<<"Takeoff Q is empty!!"<<endl;};
        void TakeoffFull(){cout<<"Takeoff Q is Full!!"<<endl;};
};

void TakeoffHeap::display(){ //airId와 airName을 출력
    for(int i=1; i<=n; i++){
        cout<<"("<<i<<", "<<Takingoff[i].airId<<", "<<Takingoff[i].airName<<endl;
    }
}

void TakeoffHeap::Insert(const AirPlane& x){ //takeoffTime을 남은 시간과 비교해서 넣음.
    if (n==MaxSize){TakeoffFull(); return;}
    n++;
    int i;
    for(i=n; 1;){
        if(i==1) break;
        if(x.remainingTime > Takingoff[i/2].remainingTime) break;
        Takingoff[i]=Takingoff[i/2];
        i /= 2;
    }
    Takingoff[i]=x;
}

AirPlane* TakeoffHeap::DeleteTakeoff(AirPlane& x){ //착륙한 비행기를 삭제
    int i,j;
    if(!n) {TakeoffEmpty(); return 0;}
    x = Takingoff[1];
    AirPlane k =Takingoff[n];
    n--;

    for (i=1, j=2; j<=n;){
        if(j<n) {
            if(Takingoff[j].remainingTime>Takingoff[j+1].remainingTime) j++;
        }
        if(k.remainingTime<=Takingoff->remainingTime) break;
        Takingoff[i]=Takingoff[j];
        i=j;
        j*=2;
    }
    Takingoff[i]=k;
    return &x;

}


int main(){
    
    LandingHeap Landing(10);
    TakeoffHeap Takingoff(10);
    Landing.Insert(AirPlane(rand()/300));
    Takingoff.Insert(AirPlane(rand()/180));
    
    

    return 0;
}