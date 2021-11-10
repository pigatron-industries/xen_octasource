#include "ThreeBody.h"
#include <math.h>

void ThreeBody::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    pos[X] = 0;
    pos[Y] = 0;
    mult[X] = 1;
    mult[Y] = 1;
    offset[X] = 0;
    offset[Y] = 0;
    speedMult = 1;
}

void ThreeBody::setParam(int param, float value) {
    // switch(param) {
    //     case 0:
    //         p2.mass = value*2 + 0.2;
    //         break;
    //     case 1:
    //         p1.length = value*4;
    //         p2.length = 4-value*4;
    //         break;
    // }
}

void ThreeBody::process() {
    //TODO
}