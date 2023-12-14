#include "HighAndLow.h"

int HighAndLow::RandomCard(){
    
    randomSeed(0);
    int randNumber = random(0, 9);
    return randNumber;    
}