#include "BouncingBall.h"
#include <math.h>


void BouncingBall::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    speedMult = 1;
    time = 0;
    startVelocity = 3;
    bounceVelocity = 3;
}

void BouncingBall::setParam(int param, float value) {
}

void BouncingBall::trigger() {
    bounceVelocity = startVelocity;
    time = calcStartBounceTimeAtHeight();
}

void BouncingBall::process() {
    time += dt;
    pos[X] = (bounceVelocity * time) - (0.5 * acceleration * time * time);

    if(pos[X] <= 0) {
        bounceVelocity = bounceVelocity * damp;
        time = 0;
        pos[X] = 0;
    }
}

float BouncingBall::calcStartBounceTimeAtHeight() {
    return (-startVelocity + sqrtf(startVelocity*startVelocity - 2*acceleration*pos[X])) / -acceleration;
}
