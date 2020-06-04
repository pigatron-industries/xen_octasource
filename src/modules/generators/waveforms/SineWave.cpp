#include "SineWave.h"

#include <math.h>


SineWave::SineWave() {
}


float SineWave::getValue(float position) {
    return MAX_POSITION * sin(position/(MAX_POSITION/(2*M_PI)));
}
