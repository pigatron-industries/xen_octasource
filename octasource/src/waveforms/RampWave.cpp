#include "RampWave.h"



RampWave::RampWave() {
}


float RampWave::getValue(float position) {
    return (position - 0.5) * 10;
}
