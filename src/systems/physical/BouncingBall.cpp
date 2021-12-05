#include "BouncingBall.h"
#include <math.h>


void BouncingBall::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    speedMult = 1;
    velocity = startVelocity;
}

void BouncingBall::setParam(int param, float value) {
}

void BouncingBall::trigger() {
    velocity = startVelocity;
}

void BouncingBall::process() {
    float accel = -acceleration;
    float prevPos = pos[X];
    if(floorMode == FloorMode::INVERT) {
        if(pos[X] <= 0) {
            accel = acceleration;
        }
    }

    velocity += accel * dt;
    pos[X] += velocity * dt;

    if(floorMode == FloorMode::BOUNCE) {
        if(pos[X] <= 0) {
            velocity = -velocity * damp;
            pos[X] = 0;
        }
    } else {
        if((prevPos > 0 && pos[X] <= 0) || (prevPos < 0 && pos[X] >= 0)) {
            velocity = velocity * damp;
        }
    }
}
