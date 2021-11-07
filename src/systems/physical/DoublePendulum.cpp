#include "DoublePendulum.h"
#include <math.h>

void DoublePendulum::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    pos[X] = 0;
    pos[Y] = 0;
    mult[X] = 1;
    mult[Y] = -1;
    offset[X] = 0;
    offset[Y] = 0;
    speedMult = 1;

    p1.mass = 2;
    p2.mass = 2;
    p1.length = 2;
    p2.length = 2;
    p1.velocity = 0;
    p2.velocity = 0;

    p2.angle = M_PI+0.01;
    p1.angle = M_PI-0.01;
}

void DoublePendulum::setParam(int param, float value) {
    switch(param) {
        case 0:
            p2.mass = value*2 + 0.2;
            break;
        case 1:
            p1.length = value*4;
            p2.length = 4-value*4;
            break;
    }
}

void DoublePendulum::process() {
    float p2LengthMultMass = p2.length * p2.mass;

    float cosP1Angle = cosf(p1.angle);
    float sinP1Angle = sinf(p1.angle);
    float sinP1AngleMinusP2Angle = sinf(p1.angle-p2.angle);
    float p2MassMultCos2P1AngleMinusP2Angle = p2.mass * cosf(2*(p1.angle-p2.angle));
    float p1VelocitySquared = p1.velocity * p1.velocity;
    float p2VelocitySquared = p2.velocity * p2.velocity;
    float p1VelocitySquaredMultLength = p1VelocitySquared * p1.length;
    float p2VelocitysquaredMultLengthMultMass = p2VelocitySquared * p2LengthMultMass;

    float p1Acceleration = -g * (2*p1.mass*p2.mass) * sinP1Angle;
    p1Acceleration -= g * p2.mass * sinf(p1.angle-2*p2.angle);
    p1Acceleration -= 2 * p2VelocitysquaredMultLengthMultMass * sinP1AngleMinusP2Angle;
    p1Acceleration -= p1VelocitySquaredMultLength * p2.mass * sinf(2*(p1.angle-p2.angle));
    p1Acceleration /= p1.length * (2 * p1.mass + p2.mass - p2MassMultCos2P1AngleMinusP2Angle);

    float p2Acceleration = (p1.mass+p2.mass) * p1VelocitySquaredMultLength;
    p2Acceleration += g * (p1.mass+p2.mass) * cosP1Angle;
    p2Acceleration += p2VelocitysquaredMultLengthMultMass * cosf(p1.angle-p2.angle);
    p2Acceleration *= 2 * sinP1AngleMinusP2Angle;
    p2Acceleration /= p2.length * (2 * p1.mass + p2.mass - p2MassMultCos2P1AngleMinusP2Angle);

    p1.velocity += p1Acceleration * dt;
    p2.velocity += p2Acceleration * dt;

    if(p1.velocity > maxVelocity) {
        p1.velocity = maxVelocity;
    } else if(p1.velocity < -maxVelocity) {
        p1.velocity = -maxVelocity;
    }
    if(p2.velocity > maxVelocity) {
        p2.velocity = maxVelocity;
    } else if(p2.velocity < -maxVelocity) {
        p2.velocity = -maxVelocity;
    }

    p1.angle += p1.velocity * dt;
    p2.angle += p2.velocity * dt;

    p1.positionX = sinP1Angle * p1.length;
    p1.positionY = cosP1Angle * p1.length;
    p2.positionX = p1.positionX + sinf(p2.angle) * p2.length;
    p2.positionY = p1.positionY + cosf(p2.angle) * p2.length;

    pos[X] = p2.positionX;
    pos[Y] = p2.positionY;
}