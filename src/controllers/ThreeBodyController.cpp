#include "ThreeBodyController.h"

void ThreeBodyController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void ThreeBodyController::init() {
    threeBody.init(sampleRate);
    Serial.println("Three Body");

    List<Body, 3> bodies;

    bodies[0].mass = 100;
    bodies[0].position = Vector<2>(0, 0);
    bodies[0].velocity = Vector<2>(0, 0);
    
    bodies[1].mass = 1;
    bodies[1].position = Vector<2>(0, 4);
    bodies[1].velocity = Vector<2>(5, 0);
    
    bodies[2].mass = 1;
    bodies[2].position = Vector<2>(0, -4);
    bodies[2].velocity = Vector<2>(-5, 0);
    
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
    printBody(threeBody.getBodies()[0]);
    printBody(threeBody.getBodies()[1]);
    printBody(threeBody.getBodies()[2]);
    Serial.println();
}

void ThreeBodyController::printBody(Body body) {
    Serial.print("(");
    Serial.print(body.position[X]);
    Serial.print(",");
    Serial.print(body.position[Y]);
    Serial.print(") ");
}