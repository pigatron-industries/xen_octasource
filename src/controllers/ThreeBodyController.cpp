#include "ThreeBodyController.h"
#include "debug/debug.h"

void ThreeBodyController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void ThreeBodyController::init() {
    threeBody.init(sampleRate);
    Serial.println("Three Body");
    //printBodies();


    /**
     * Initial conditionas taken from 
     * https://observablehq.com/@rreusser/periodic-planar-three-body-orbits
     * http://three-body.ipb.ac.rs/
     * To increase size without affecting pattern, multiply mass and initial position by the same amount
     */

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
        case Mode::FIGURE8_STABLE_V1A: // Figure 8 Stable
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.347111, 0.532728));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::FIGURE8_CHAOTIC_V17A: // Figure 8 Chaotic
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.210832, 0.51741));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::BROUCKE_A2: // Broucke Stable
            bodies[0].mass = 4;
            bodies[0].position = Vector<2>(0.336130095, 0) * 4;
            bodies[0].velocity = Vector<2>(0, 1.532431537);
            bodies[1].mass = 4;
            bodies[1].position = Vector<2>(0.7699893804, 0) * 4;
            bodies[1].velocity = Vector<2>(0, -0.6287350978);
            bodies[2].mass = 4;
            bodies[2].position = Vector<2>(-1.1061194753, 0) * 4;
            bodies[2].velocity = Vector<2>(0, -0.9036964391);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::BROUCKE_ASYMETRICAL: // Stable state with 3 equal masses, found accidentally from CHAOTIC_BOUNCE1
            bodies[0].mass = 4;
            bodies[0].position = Vector<2>(-2.855484,-0.099324);
            bodies[0].velocity = Vector<2>(-0.14822,-0.47005);
            bodies[1].mass = 4;
            bodies[1].position = Vector<2>(-1.785072,0.406224);
            bodies[1].velocity = Vector<2>(-1.47620,1.02377);
            bodies[2].mass = 4;
            bodies[2].position = Vector<2>(4.640556,-0.306904);
            bodies[2].velocity = Vector<2>(-0.20557,1.39997);
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::CHAOTIC1_BOUNCE:
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.201678, 0.409896));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::BOUNCE);
            break;
        case Mode::CHAOTIC1_ANTIGRAV:
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.201678, 0.409896));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::ANTIGRAV);
            break;
        case Mode::CHAOTIC1_WRAP:
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.201678, 0.409896));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::WRAP);
            break;
        case Mode::CHAOTIC2: // Large mass with 2 small masses
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
            threeBody.setEdgeMode(ThreeBody::EdgeMode::ANTIGRAV);
            break;
        case Mode::CHAOTIC3: // All different masses
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
            threeBody.setEdgeMode(ThreeBody::EdgeMode::ANTIGRAV);
            break;
    }
    
    threeBody.setBodies(bodies);
}

void ThreeBodyController::update() {
    updateRate();
    updateAmp();
    updateSize();
    updateDamp();
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
        totalGain = amp * size;
    }
}

void ThreeBodyController::updateSize() {
    if(sizeCvInput.update()) {
        size = sizeCvInput.getValue();
        threeBody.setLimit(5/size);
        totalGain = amp * size;
    }
}

void ThreeBodyController::updateDamp() {
    #if defined(OCTASOURCE_MKII)
        if(dampCvInput.update()) {
            threeBody.setDamp(dampCvInput.getValue());
        }
    #endif
}

void ThreeBodyController::process() {
    threeBody.process();
    Hardware::hw.cvOutputPins[0]->analogWrite(threeBody.getOutput(0)*totalGain);
    Hardware::hw.cvOutputPins[1]->analogWrite(threeBody.getOutput(1)*totalGain);
    Hardware::hw.cvOutputPins[2]->analogWrite(threeBody.getOutput(2)*totalGain);
    Hardware::hw.cvOutputPins[3]->analogWrite(threeBody.getOutput(3)*totalGain);
    Hardware::hw.cvOutputPins[4]->analogWrite(threeBody.getOutput(4)*totalGain);
    Hardware::hw.cvOutputPins[5]->analogWrite(threeBody.getOutput(5)*totalGain);
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