#include "TriangleWave.h"



TriangleWave::TriangleWave() {
}


float TriangleWave::getValue(float position) {
    if(position < MAX_POSITION/2) {
        return (position*2 - MAX_POSITION/2)*2;
    } else {
        return MAX_POSITION*2 - (position*2 - MAX_POSITION/2)*2;
    }
}
