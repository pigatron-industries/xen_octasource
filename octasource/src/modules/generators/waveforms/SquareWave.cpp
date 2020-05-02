#include "SquareWave.h"

#include <math.h>


SquareWave::SquareWave() {
}


float SquareWave::getValue(float position) {
    if(position < MAX_POSITION/2) {
        return MAX_POSITION;
    } else {
        return -MAX_POSITION;
    }
}
