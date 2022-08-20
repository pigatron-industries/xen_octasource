#include "RandomController.h"

void RandomController::init(float sampleRate) {
    clock.init(sampleRate);
    init();
}

void RandomController::init() {
    Serial.println("Random");
    Hardware::hw.display.textLine("RANDOM");
}

void RandomController::update() {
    if(rateCvInput.update()) {
        float rateValue = rateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            clock.setFrequency(rateValue);
        }
    }

    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }

    if(chanceCvInput.update()) {
        chanceValue = chanceCvInput.getValue();
    }

    if(controls.syncInput.update() && controls.syncInput.isTriggeredOn()) {
        clock.reset();
        tick();
    }

    Hardware::hw.updateOutputLeds();
}

void RandomController::process() {
    triggerOutputs[0].update();
    triggerOutputs[1].update();
    triggerOutputs[2].update();
    triggerOutputs[3].update();

    if(clock.process()) {
        tick();
    }
}

void RandomController::tick() {
    if(random(-5, 5) < chanceValue) {
        triggerOutputs[0].trigger();
    } else {
        triggerOutputs[1].trigger();
    }

    if(random(-5, 5) < chanceValue) {
        triggerOutputs[2].trigger();
    } else {
        triggerOutputs[3].trigger();
    }

    Hardware::hw.cvOutputPins[1]->analogWrite(random(-5, 5)*amp);
    Hardware::hw.cvOutputPins[3]->analogWrite(random(-5, 5)*amp);
    Hardware::hw.cvOutputPins[5]->analogWrite(random(-5, 5)*amp);
    Hardware::hw.cvOutputPins[7]->analogWrite(random(-5, 5)*amp);
}