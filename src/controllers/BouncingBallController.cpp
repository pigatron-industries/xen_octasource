#include "BouncingBallController.h"

void BouncingBallController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void BouncingBallController::init() {
    Serial.println("Bouncing Ball");
    for(int i = 0; i < 8; i++) {
        bouncingBalls[i].init(sampleRate);
        bouncingBalls[i].setDamp(0.9);
        bouncingBalls[i].setAcceleration(i+1);
        bouncingBalls[i].setStartVelocityForHeight(5);
    }
}

void BouncingBallController::update() {
    updateRate();
    updateAmp();
    updateParams();

    if(triggerInput.update() && triggerInput.isTriggeredOn()) {
        for(int i = 0; i < 8; i++) {
            bouncingBalls[i].trigger();
        }
    }
}

void BouncingBallController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(int i = 0; i < 8; i++) {
            bouncingBalls[i].setSpeed(rateValue);
        }
    }
}

void BouncingBallController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void BouncingBallController::updateParams() {
    if(param1CvInput.update()) {
    }
    
    #if defined(OCTASOURCE_MKII)
        if(param2CvInput.update()) {
        }
    #endif
}

void BouncingBallController::process() {
    for(int i = 0; i < 8; i++) {
        bouncingBalls[i].process();
        Hardware::hw.cvOutputPins[i]->analogWrite(bouncingBalls[i].getOutput(X)*amp);
    }
}