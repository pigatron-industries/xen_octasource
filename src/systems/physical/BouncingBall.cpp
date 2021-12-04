#include "BouncingBall.h"
#include <math.h>


void BouncingBall::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    speedMult = 1;
    velocity = 1;
}

void BouncingBall::setParam(int param, float value) {
}

void BouncingBall::trigger(float velocity) {
    this->velocity = velocity;
}

void BouncingBall::process() {
    velocity += -acceleration * dt;
    pos[X] += velocity * dt;
}
