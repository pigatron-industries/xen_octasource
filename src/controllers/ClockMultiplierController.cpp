#include "ClockMultiplierController.h"

void ClockMultiplierController::init(float sampleRate) {
    for(int i = 0; i < 9; i++) {
        clocks[i].init(sampleRate);
    }
    init();
}

void ClockMultiplierController::init() {
    Hardware::hw.display.text("CLOCK MULT");
}

void ClockMultiplierController::update() {
    if(rateCvInput.update()) {
        float rateValue = rateCvInput.getValue();
        for(int i = 0; i < 9; i++) {
            clocks[i].setFrequency(rateValue*(i+1));
        }
    }

    Hardware::hw.updateOutputLeds();
}

void ClockMultiplierController::process() {
    for(int i = 0; i < 8; i++) {
        if(clocks[i+1].process()) {
            triggerOutputs[i].trigger();
        }
        triggerOutputs[i].update();
    }

    if(clocks[0].process()) {
        controls.triggerOutput.trigger();
        syncClocks();
    }
    controls.triggerOutput.update();
}

void ClockMultiplierController::syncClocks() {
    for(int i = 0; i < 9; i++) {
        clocks[i].reset();
    }
}