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
    time = calcTimeToHeight(startVelocity, pos[X]);
    bounceHeight = calcHeightAtTime(bounceVelocity, calcTimeToMaxHeight(bounceVelocity));
}

void BouncingBall::process() {
    time += dt;
    pos[X] = calcHeightAtTime(bounceVelocity, time);

    if(pos[X] <= 0) {
        bounceVelocity = bounceVelocity * damp;
        time = 0;
        pos[X] = 0;
        bounceHeight = calcHeightAtTime(bounceVelocity, calcTimeToMaxHeight(bounceVelocity));
        if(bounceHeight > 0) {
            bounced = true;
        } else {
            bounced = false;
        }
    } else {
        bounced = false;
    }
}

float BouncingBall::calcHeightAtTime(float initVelocity, float time) {
    return (initVelocity * time) - (0.5 * acceleration * time * time);
}

float BouncingBall::calcTimeToHeight(float initVelocity, float height) {
    // quadratic formula
    return (-initVelocity + sqrtf(initVelocity*initVelocity - 2*acceleration*height)) / -acceleration;
}

float BouncingBall::calcTimeToMaxHeight(float initVelocity) {
    return initVelocity/acceleration;
}

float BouncingBall::calcInitVelocityForHeight(float height) {
    return sqrtf(2*height*acceleration);
}