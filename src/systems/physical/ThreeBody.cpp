#include "ThreeBody.h"
#include <math.h>

#include <Arduino.h>

void ThreeBody::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    speedMult = 1;
}

void ThreeBody::setBodies(const List<Body, BODIES>& bodies) {
    Vector<2> centreOfMass = calculateCentreOfMass(bodies);
    Vector<2> momentum = calculateMomentum(bodies);
    for(int i = 0; i < BODIES; i++) {
        this->bodies[i] = bodies[i];
        this->bodies[i].position -= centreOfMass;
    }
    //TODO make sure total momentum (mass*velocity) of system is zero

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

    // Vector<2> momentum = calculateMomentum(bodies);
    // momentum.print();
    // Serial.println();
    // Vector<2> centreOfMass = calculateCentreOfMass(bodies);
    // centreOfMass.print();
    // Serial.println();

    limitBodies();
    setOutputs();
}

void ThreeBody::limitBodies() {
    for(int i = 0; i < BODIES; i++) {
        for(int dim = 0; dim < 2; dim++) {
            if(bodies[i].position[dim] > limit) {
                bodies[i].position[dim] = limit;
                bodies[i].velocity[dim] = -bodies[i].velocity[dim]*0.5;
            } else if (bodies[i].position[dim] < -limit) {
                bodies[i].position[dim] = -limit;
                bodies[i].velocity[dim] = -bodies[i].velocity[dim]*0.5;
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
            bodies[i].acceleration += r * ((g * bodies[j].mass) / (dist*dist*dist));
        }
    }
}

Vector<2> ThreeBody::calculateCentreOfMass(const List<Body, BODIES>& bodies) {
    Vector<2> massPosition = Vector<2>(0, 0);
    float totalMass = 0;
    for(int i = 0; i < BODIES; i++) {
        massPosition += bodies[i].position * bodies[i].mass;
        totalMass += bodies[i].mass;
    }
    return massPosition / totalMass;
}

Vector<2> ThreeBody::calculateMomentum(const List<Body, BODIES>& bodies) {
    Vector<2> momentum = Vector<2>(0, 0);
    for(int i = 0; i < BODIES; i++) {
        momentum += bodies[i].velocity * bodies[i].mass;
    }
    return momentum;
}
