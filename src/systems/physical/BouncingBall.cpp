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
    time = calcInitBounceTimeAtHeight();
}

void BouncingBall::process() {
    time += dt;
    pos[X] = calcHeightAtTime(bounceVelocity, time);

    if(pos[X] <= 0) {
        bounceVelocity = bounceVelocity * damp;
        time = 0;
        pos[X] = 0;
    }
}

float BouncingBall::calcHeightAtTime(float initVelocity, float time) {
    return (initVelocity * time) - (0.5 * acceleration * time * time);
}

float BouncingBall::calcInitBounceTimeAtHeight() {
    // quadratic formula
    return (-startVelocity + sqrtf(startVelocity*startVelocity - 2*acceleration*pos[X])) / -acceleration;
}

float BouncingBall::calcInitBounceTimeAtMax() {
    return startVelocity/acceleration;
}

float BouncingBall::calcInitVelocityForHeight(float height) {
    return sqrtf(2*height*acceleration);
}