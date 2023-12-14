#include "MdMeasureDistance.h"

DrUltraSonic drul=DrUltraSonic(ECHO_PIN,TRIG_PIN);

double MdMeasureDistance::getDistance(){
    double distance;

    if(drul.measureReturnTime()>0){
        distance = (340.0/1000000) * drul.measureReturnTime() * 0.5 * 100;
    }else {
        distance=0;
    }
    return distance;
}