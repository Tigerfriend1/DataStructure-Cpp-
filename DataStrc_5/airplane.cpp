//heap/priority를 통해
//airport landing and takeoff를 simulating 하는 프로그램 제작 
#include <iostream>
#include <time.h>

using namespace std;

class AirPlane{
    friend class LaningQ;
    private:
     char airId;
     char airName;
     char usingType;
     int remainingTime;
     int landingTime;
     int takeoffTime;
};

class LaningQ{
    virtual void Insert(const AirPlane&)=0;
    virtual AirPlane* DeleteLanding(AirPlane&)=0;
};

class TakeoffQ{

};

int main(){


    return 0;
}