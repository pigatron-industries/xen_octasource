#include "ClockController.h"

void ClockController::init() {
    clock.init(sampleRate);
}

void ClockController::update() {
    if(ratePotInput.update()) {
        float rateValue = ratePotInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            clock.setFrequency(rateValue);
        }
    }
}

void ClockController::process() {
    if(clock.process()) {
        tick();
    }
}

void ClockController::tick() {
    for(int i = 0; i < 8; i++) {
        if(clockDividers[i].tick()) {
            triggerOutputs[i].trigger();
        }
    }
}