#include "RampWave.h"



RampWave::RampWave() {
}


float RampWave::getValue(float position) {
    return (position - MAX_POSITION/2)*2;
}
