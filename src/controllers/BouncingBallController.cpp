#include "BouncingBallController.h"

void BouncingBallController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void BouncingBallController::init() {
    bouncingBall.init(sampleRate);
    Serial.println("Bouncing Ball");
}

void BouncingBallController::update() {
    updateRate();
    updateAmp();
    updateParams();
}

void BouncingBallController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        bouncingBall.setSpeed(rateValue);
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
    bouncingBall.process();
    Hardware::hw.cvOutputPins[0]->analogWrite(bouncingBall.getOutput(X)*amp);
}