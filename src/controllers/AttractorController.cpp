#include "AttractorController.h"

void AttractorController::init(float sampleRate) {
    for(int i = 0; i < ATTRACTOR_COUNT; i++) {
        attractors1[i]->init(sampleRate);
        attractors2[i]->init(sampleRate);
        attractors2[i]->movePosition(Tuple(0.01, 0, 0));
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
    Attractor* attractor = attractors1[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[0]->analogWrite(attractor->getX()*amp);
    Hardware::hw.cvOutputPins[1]->analogWrite(attractor->getY()*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(attractor->getZ()*amp);

    attractor = attractors2[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[3]->analogWrite(attractor->getX()*amp);
    Hardware::hw.cvOutputPins[4]->analogWrite(attractor->getY()*amp);
    Hardware::hw.cvOutputPins[5]->analogWrite(attractor->getZ()*amp);

    Hardware::hw.gateOutPin.digitalWrite(attractor->getZ() > 0);
}