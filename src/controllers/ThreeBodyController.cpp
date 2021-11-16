#include "ThreeBodyController.h"

void ThreeBodyController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void ThreeBodyController::init() {
    threeBody.init(sampleRate);
    Serial.println("Three Body");
    //printBodies();

    Array<Body, 3> bodies;
    switch(mode.value) {
        case Mode::STABLE1: // Massive star with opposite planets of equal mass
            bodies[0].mass = 100;
            bodies[0].position = Vector<2>(0, 0);
            bodies[0].velocity = Vector<2>(0, 0);
            bodies[1].mass = 1;
            bodies[1].position = Vector<2>(0, 4);
            bodies[1].velocity = Vector<2>(5, 0);
            bodies[2].mass = 1;
            bodies[2].position = Vector<2>(0, -3);
            bodies[2].velocity = Vector<2>(-4, 0);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::STABLE2: // Lagrange point L5 (TODO)
            bodies[0].mass = 100;
            bodies[0].position = Vector<2>(0, 0);
            bodies[0].velocity = Vector<2>(0, 0);
            bodies[1].mass = 1;
            bodies[1].position = Vector<2>(0, 4);
            bodies[1].velocity = Vector<2>(5, 0);
            bodies[2].mass = 0.01;
            bodies[2].position = rotate(bodies[1].position, -M_PI/3);
            bodies[2].velocity = rotate(bodies[1].velocity, -M_PI/3);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::STABLE3: // Sun, Earth, Moon (Moon escapes after a few orbits)
            bodies[0].mass = 100;
            bodies[0].position = Vector<2>(0, 0);
            bodies[0].velocity = Vector<2>(0, 0);
            bodies[1].mass = 1;
            bodies[1].position = Vector<2>(0, 4);
            bodies[1].velocity = Vector<2>(-5, 0);
            bodies[2].mass = 0.1;
            bodies[2].position = Vector<2>(0, 4.5);
            bodies[2].velocity = Vector<2>(-5.5, 0);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::STABLE4: // Figure 8
            bodies[0].mass = 4;
            bodies[0].position = Vector<2>(-4, 0);
            bodies[0].velocity = Vector<2>(0.347111, 0.532728);
            bodies[1].mass = 4;
            bodies[1].position = Vector<2>(4, 0);
            bodies[1].velocity = Vector<2>(0.347111, 0.532728);
            bodies[2].mass = 4;
            bodies[2].position = Vector<2>(0, 0);
            bodies[2].velocity = Vector<2>(-2*0.347111, -2*0.532728);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::STABLE5: // Stable state with 3 equal masses
            bodies[0].mass = 10;
            bodies[0].position = Vector<2>(-7.13871,-0.24831);
            bodies[0].velocity = Vector<2>(-0.14822,-0.47005);
            bodies[1].mass = 10;
            bodies[1].position = Vector<2>(-4.46268,1.01556);
            bodies[1].velocity = Vector<2>(-1.47620,1.02377);
            bodies[2].mass = 10;
            bodies[2].position = Vector<2>(11.60139,-0.76726);
            bodies[2].velocity = Vector<2>(-0.20557,1.39997);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::BOUNCE);
            break;
        case Mode::CHAOTIC_BOUNCE1: // Equal masses
            bodies[0].mass = 10;
            bodies[0].position = Vector<2>(0, 4);
            bodies[0].velocity = Vector<2>(2, 0);
            bodies[1].mass = 10;
            bodies[1].position = rotate(bodies[0].position, M_PI*2/3);
            bodies[1].velocity = rotate(bodies[0].velocity, M_PI*2/3);
            bodies[2].mass = 10;
            bodies[2].position = rotate(bodies[0].position, -M_PI*2/3);
            bodies[2].velocity = rotate(bodies[0].velocity, -M_PI*2/3);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::BOUNCE);
            break;
        case Mode::CHAOTIC_BOUNCE2: // Large mass with 2 small masses
            bodies[0].mass = 100;
            bodies[0].position = Vector<2>(0, 0);
            bodies[0].velocity = Vector<2>(0, 0);
            bodies[1].mass = 1;
            bodies[1].position = Vector<2>(0, 4);
            bodies[1].velocity = Vector<2>(5, 0);
            bodies[2].mass = 1;
            bodies[2].position = Vector<2>(0, -4);
            bodies[2].velocity = Vector<2>(-4.9, 0);
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::BOUNCE);
            break;
        case Mode::CHAOTIC_BOUNCE3: // All different masses
            bodies[0].mass = 100;
            bodies[0].position = Vector<2>(0, 0);
            bodies[0].velocity = Vector<2>(0, 0);
            bodies[1].mass = 10;
            bodies[1].position = Vector<2>(0, 4);
            bodies[1].velocity = Vector<2>(5, 0);
            bodies[2].mass = 1;
            bodies[2].position = Vector<2>(0, -4);
            bodies[2].velocity = Vector<2>(-5, 0);
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::BOUNCE);
            break;
        case Mode::CHAOTIC_WRAP1:
            bodies[0].mass = 10;
            bodies[0].position = Vector<2>(0, 4);
            bodies[0].velocity = Vector<2>(2, 0);
            bodies[1].mass = 10;
            bodies[1].position = rotate(bodies[0].position, M_PI*2/3);
            bodies[1].velocity = rotate(bodies[0].velocity, M_PI*2/3);
            bodies[2].mass = 10;
            bodies[2].position = rotate(bodies[0].position, -M_PI*2/3);
            bodies[2].velocity = rotate(bodies[0].velocity, -M_PI*2/3);
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::WRAP);
            break;
    }
    
    threeBody.setBodies(bodies);
}

void ThreeBodyController::update() {
    updateRate();
    updateAmp();
}

void ThreeBodyController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        threeBody.setSpeed(rateValue);
    }
}

void ThreeBodyController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
        threeBody.setLimit(5/amp);
    }
}

void ThreeBodyController::process() {
    threeBody.process();
    Hardware::hw.cvOutputPins[0]->analogWrite(threeBody.getOutput(0)*amp);
    Hardware::hw.cvOutputPins[1]->analogWrite(threeBody.getOutput(1)*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(threeBody.getOutput(2)*amp);
    Hardware::hw.cvOutputPins[3]->analogWrite(threeBody.getOutput(3)*amp);
    Hardware::hw.cvOutputPins[4]->analogWrite(threeBody.getOutput(4)*amp);
    Hardware::hw.cvOutputPins[5]->analogWrite(threeBody.getOutput(5)*amp);
}

void ThreeBodyController::printBodies() {
    Serial.println("State:");
    printBody(threeBody.getBodies()[0]);
    printBody(threeBody.getBodies()[1]);
    printBody(threeBody.getBodies()[2]);
    Serial.println();
}

void ThreeBodyController::printBody(Body body) {
    print(body.position);
    print(body.velocity);
}