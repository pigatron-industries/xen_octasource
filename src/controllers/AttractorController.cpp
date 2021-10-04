#include "AttractorController.h"

void AttractorController::init(float sampleRate) {
    for(int i = 0; i < ATTRACTOR_COUNT; i++) {
        attractors[i]->init(sampleRate);
    }
    init();
}

void AttractorController::init() {
}

void AttractorController::update() {
    updateRate();
    updateAmp();
    // if(cCvInput.update()) {
    //     lorenzAttractor.setB(cCvInput.getValue());
    // }
}

void AttractorController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(int i = 0; i < ATTRACTOR_COUNT; i++) {
            attractors[i]->setSpeed(rateValue);
        }
    }
}

void AttractorController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void AttractorController::process() {
    Attractor* attractor = attractors[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[0]->analogWrite(attractor->getX()*amp);
    Hardware::hw.cvOutputPins[1]->analogWrite(attractor->getY()*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(attractor->getZ()*amp);
}