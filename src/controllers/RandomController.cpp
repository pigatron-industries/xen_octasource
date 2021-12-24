#include "RandomController.h"

void RandomController::init(float sampleRate) {
    clock.init(sampleRate);
    init();
}

void RandomController::init() {
    Serial.println("Random");
}

void RandomController::update() {
    if(rateCvInput.update()) {
        float rateValue = rateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            clock.setFrequency(rateValue);
        }
    }

    if(chanceCvInput.update()) {
        chanceValue = chanceCvInput.getValue();
    }

    if(triggerInput.update() && triggerInput.isTriggeredOn()) {
        clock.reset();
        tick();
    }

    Hardware::hw.updateOutputLeds();
}

void RandomController::process() {
    triggerOutputs[0].update();
    triggerOutputs[1].update();

    noise = random(-5, 5);
    Hardware::hw.cvOutputPins[2]->analogWrite(noise);
    
    if(clock.process()) {
        tick();
    }
}

void RandomController::tick() {
    if(noise < chanceValue) {
        triggerOutputs[0].trigger();
    } else {
        triggerOutputs[1].trigger();
    }
    Hardware::hw.cvOutputPins[3]->analogWrite(noise);
}