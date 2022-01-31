#include "AttractorController.h"

void AttractorController::init(float sampleRate) {
    for(size_t i = 0; i < attractors1.getSize(); i++) {
        attractors1[i]->init(sampleRate);
        attractors2[i]->init(sampleRate);
        attractors2[i]->changePosition(Vector<3>(0.01, 0, 0));
    }
    init();
}

void AttractorController::init() {
    Serial.println("Attractor");
}

void AttractorController::update() {
    updateRate();
    updateAmp();
    Hardware::hw.updateOutputLeds();
}

void AttractorController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(size_t i = 0; i < attractors1.getSize(); i++) {
            attractors1[i]->setSpeed(rateValue);
            attractors2[i]->setSpeed(rateValue);
        }
    }
}

void AttractorController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void AttractorController::process() {
    ContinuousSystem* attractor = attractors1[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[0]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[1]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(attractor->getOutput(Z)*amp);

    attractor = attractors2[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[3]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[4]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[5]->analogWrite(attractor->getOutput(Z)*amp);

    Hardware::hw.gateOutPin.digitalWrite(attractor->getOutput(Z) > 0);
}