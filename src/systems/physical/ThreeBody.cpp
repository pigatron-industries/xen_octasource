#include "ThreeBody.h"
#include <math.h>

#include <Arduino.h>


Array<Body, BODIES> ThreeBody::initEqualInlineSystem(int mass, Vector<2> velocity) {
    Array<Body, 3> bodies;
    bodies[0].mass = mass;
    bodies[0].position = Vector<2>(-1, 0) * mass;
    bodies[0].velocity = velocity;
    bodies[1].mass = mass;
    bodies[1].position = Vector<2>(1, 0) * mass;
    bodies[1].velocity = velocity;
    bodies[2].mass = mass;
    bodies[2].position = Vector<2>(0, 0) * mass;
    bodies[2].velocity = velocity * -2; // opposite and equal to other 2 velocities
    return bodies;
}


void ThreeBody::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    speedMult = 1;
}

void ThreeBody::setBodies(const Array<Body, BODIES>& bodies) {
    for(int i = 0; i < BODIES; i++) {
        this->bodies[i] = bodies[i];
    }

    //Vector<2> momentum = calculateMomentum(bodies);
    // Serial.print("momentum: ");
    // momentum.print();
    // Serial.println();

    doDriftCorrection();
    setOutputs();
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
    for(int i = 0; i < BODIES; i++) {
        calculateAcceleration(i);
    }
    for(int i = 0; i < BODIES; i++) {
        bodies[i].velocity += bodies[i].acceleration * dt;
        bodies[i].position += bodies[i].velocity * dt;
    }

    if(driftCorrection) {
        doDriftCorrection();
    }
    limitBodies();
    setOutputs();
}

void ThreeBody::limitBodies() {
    for(int i = 0; i < BODIES; i++) {
        for(int dim = 0; dim < 2; dim++) {
            if(bodies[i].position[dim] > limit) {
                if(edgeMode == EdgeMode::BOUNCE) {
                    bodies[i].position[dim] = limit;
                    if(bodies[i].velocity[dim] > 0) {
                        bodies[i].velocity[dim] = -bodies[i].velocity[dim]*damp;
                    }
                } else if(edgeMode == EdgeMode::WRAP)  {
                    bodies[i].position[dim] = -limit;
                    bodies[i].velocity[dim] = bodies[i].velocity[dim]*damp;
                }
            } else if (bodies[i].position[dim] < -limit) {
                if(edgeMode == EdgeMode::BOUNCE) {
                    bodies[i].position[dim] = -limit;
                    if(bodies[i].velocity[dim] < 0) {
                        bodies[i].velocity[dim] = -bodies[i].velocity[dim]*damp;
                    }
                } else if(edgeMode == EdgeMode::WRAP)  {
                    bodies[i].position[dim] = limit;
                    bodies[i].velocity[dim] = bodies[i].velocity[dim]*damp;
                }
            }
        }
    }
}

void ThreeBody::setOutputs() {
    pos[0] = bodies[0].position[X];
    pos[1] = bodies[0].position[Y];
    pos[2] = bodies[1].position[X];
    pos[3] = bodies[1].position[Y];
    pos[4] = bodies[2].position[X];
    pos[5] = bodies[2].position[Y];
}

void ThreeBody::calculateAcceleration(int i) {
    bodies[i].acceleration = Vector<2>(0, 0);
    for(int j = 0; j < BODIES; j++) {
        if(j != i) {
            Vector<2> r = bodies[j].position - bodies[i].position;
            float dist = r.length();
            if(dist <= minDist) {
                dist = minDist;
            }
            bodies[i].acceleration += r * ((G * bodies[j].mass) / (dist*dist*dist));
        }
    }
    if(edgeMode == EdgeMode::ANTIGRAV) {
        applyAntiGrav(i);
    }
}

void ThreeBody::applyAntiGrav(int body, int dim, int dir) {
    float dist = limit - dir*bodies[body].position[dim];
    if(dist <= minDist) {
        dist = minDist;
    }
    if(dir * bodies[body].velocity[dim] > 0) {
        bodies[body].acceleration[dim] -= dir / (dist*dist);
    } else {
        bodies[body].acceleration[dim] -= damp*dir / (dist*dist);
    }
}

void ThreeBody::applyAntiGrav(int body) {
    applyAntiGrav(body, X, 1);
    applyAntiGrav(body, X, -1);
    applyAntiGrav(body, Y, 1);
    applyAntiGrav(body, Y, -1);
}

Vector<2> ThreeBody::calculateCentreOfMass(const Array<Body, BODIES>& bodies) {
    Vector<2> massPosition = Vector<2>(0, 0);
    float totalMass = 0;
    for(int i = 0; i < BODIES; i++) {
        massPosition += bodies[i].position * bodies[i].mass;
        totalMass += bodies[i].mass;
    }
    return massPosition / totalMass;
}

Vector<2> ThreeBody::calculateMomentum(const Array<Body, BODIES>& bodies) {
    Vector<2> momentum = Vector<2>(0, 0);
    for(int i = 0; i < BODIES; i++) {
        momentum += bodies[i].velocity * bodies[i].mass;
    }
    return momentum;
}

void ThreeBody::doDriftCorrection() {
    Vector<2> centreOfMass = calculateCentreOfMass(bodies);
    for(int i = 0; i < BODIES; i++) {
        bodies[i].position -= centreOfMass;
    }

    // Vector<2> momentumDiv = calculateMomentum(bodies) / BODIES;
    // for(int i = 0; i < BODIES; i++) {
    //     bodies[i].velocity -= momentumDiv / bodies[i].mass;
    // }
}
