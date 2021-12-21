#include "DoublePendulumController.h"

void DoublePendulumController::init(float sampleRate) {
    Controller::init(sampleRate / SAMPLE_RATE_DIVISOR);
    init();
}

void DoublePendulumController::init() {
    doublePendulum.init(sampleRate);
    Serial.println("Double Pendulum");
}

void DoublePendulumController::update() {
    updateRate();
    updateAmp();
    updateParams();
    Hardware::hw.updateOutputLeds();
}

void DoublePendulumController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        doublePendulum.setSpeed(rateValue);
    }
}

void DoublePendulumController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void DoublePendulumController::updateParams() {
    if(param1CvInput.update()) {
        doublePendulum.setParam(0, param1CvInput.getValue());
    }
    
    #if defined(OCTASOURCE_MKII)
        if(param2CvInput.update()) {
            doublePendulum.setParam(1, param2CvInput.getValue());
        }
    #endif
}

void DoublePendulumController::process() {
    if(clockDivider.tick()) {
        doublePendulum.process();
        Hardware::hw.cvOutputPins[0]->analogWrite(doublePendulum.getOutput(X)*amp);
        Hardware::hw.cvOutputPins[1]->analogWrite(doublePendulum.getOutput(Y)*amp);
        Hardware::hw.cvOutputPins[2]->analogWrite(doublePendulum.getOutput(Z)*amp);
        Hardware::hw.cvOutputPins[3]->analogWrite(doublePendulum.getOutput(W)*amp);
    }
}