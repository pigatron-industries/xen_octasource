#include "BouncingBallController.h"

void BouncingBallController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void BouncingBallController::init() {
    Serial.println("Bouncing Ball");
    for(int i = 0; i < 4; i++) {
        bouncingBalls[i].init(sampleRate);
        bouncingBalls[i].setDamp(0.9);
        bouncingBalls[i].setAcceleration(i+1);
        bouncingBalls[i].setStartVelocityForHeight(5);
    }
}

void BouncingBallController::update() {
    updateRate();
    updateAmp();
    updateDamp();

    if(triggerInput.update() && triggerInput.isTriggeredOn()) {
        for(int i = 0; i < 4; i++) {
            bouncingBalls[i].trigger();
            triggerOutput.trigger();
            rotateOutput = 0;
        }
    }

    Hardware::hw.updateOutputLeds();
}

void BouncingBallController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(int i = 0; i < 4; i++) {
            bouncingBalls[i].setSpeed(rateValue);
        }
    }
}

void BouncingBallController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void BouncingBallController::updateDamp() {
    if(dampCvInput.update()) {
        float dampValue = dampCvInput.getValue();
        for(int i = 0; i < 4; i++) {
            bouncingBalls[i].setDamp(dampValue);
        }
    }
    
    // #if defined(OCTASOURCE_MKII)
    //     if(param2CvInput.update()) {
    //     }
    // #endif
}

void BouncingBallController::process() {
    triggerOutput.update();
    for(int i = 0; i < 4; i++) {
        bouncingBalls[i].process();
    }

    switch(mode.value) {
        case Mode::BOUNCE:
            for(int i = 0; i < 4; i++) {
                Hardware::hw.cvOutputPins[i*2]->analogWrite(bouncingBalls[i].getOutput(X)*amp);
                Hardware::hw.cvOutputPins[i*2+1]->analogWrite(bouncingBalls[i].getBounceHeight()*amp);
            }
            if(bouncingBalls[0].getBounced()) {
                triggerOutput.trigger();
            }
            break;
        case Mode::TRIGGERS:
            for(int i = 0; i < 4; i++) {
                triggerOutputs[i].update();
                if(bouncingBalls[i].getBounced()) {
                    triggerOutputs[i].trigger();
                    triggerOutput.trigger();
                }
                Hardware::hw.cvOutputPins[i*2+1]->analogWrite(bouncingBalls[i].getBounceHeight()*amp);
            }
            break;
        case Mode::ROTATE:
            if(bouncingBalls[0].getBounced()) {
                triggerOutput.trigger();
                Hardware::hw.cvOutputPins[rotateOutput]->analogWrite(0);
                rotateOutput++;
                if(rotateOutput >= 8) {
                    rotateOutput = 0;
                }
            }
            Hardware::hw.cvOutputPins[rotateOutput]->analogWrite(bouncingBalls[0].getOutput(X)*amp);
            break;
    }
}