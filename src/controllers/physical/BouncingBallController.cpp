#include "BouncingBallController.h"

void BouncingBallController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::MODE, 0, Mode::ROTATE-1);
    init();
}

void BouncingBallController::init() {
    Serial.println("Bouncing Ball");
    Hardware::hw.display.textLine("BOUNCE");
    setMode(parameters[Parameter::MODE].value);
    for(int i = 0; i < 4; i++) {
        bouncingBalls[i].init(sampleRate);
        bouncingBalls[i].setDamp(0.9);
        bouncingBalls[i].setAcceleration(i+1);
        bouncingBalls[i].setStartVelocityForHeight(5);
    }
}

void BouncingBallController::cycleValue(int amount) {
    uint8_t value = parameters.getSelected().cycle(amount);
    setMode(value);
    save();
}

void BouncingBallController::setMode(uint8_t mode) {
    switch(mode) {
        case Mode::BOUNCE_STEPPED:
            Hardware::hw.display.textLine("BOUNCE STEP", OLEDDisplay::TEXTLINE_2);
            break;
        case Mode::BOUNCE_TRIGGERS:
            Hardware::hw.display.textLine("BOUNCE TRIG", OLEDDisplay::TEXTLINE_2);
            break;
        case Mode::STEPPED_TRIGGERS:
            Hardware::hw.display.textLine("STEP TRIG", OLEDDisplay::TEXTLINE_2);
            break;
        case Mode::ROTATE:
            Hardware::hw.display.textLine("ROTATE", OLEDDisplay::TEXTLINE_2);
            break;
    }
}

void BouncingBallController::update() {
    updateRate();
    updateAmp();
    updateDamp();

    if(controls.syncInput.update() && controls.syncInput.isTriggeredOn()) {
        for(int i = 0; i < 4; i++) {
            bouncingBalls[i].trigger();
            controls.triggerOutput.trigger();
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
}

void BouncingBallController::process() {
    controls.triggerOutput.update();
    for(int i = 0; i < 4; i++) {
        bouncingBalls[i].process();
    }

    switch(parameters[Parameter::MODE].value) {
        case Mode::BOUNCE_STEPPED:
            for(int i = 0; i < 4; i++) {
                Hardware::hw.cvOutputPins[i*2]->analogWrite(bouncingBalls[i].getOutput(X)*amp);
                Hardware::hw.cvOutputPins[i*2+1]->analogWrite(bouncingBalls[i].getBounceHeight()*amp);
            }
            if(bouncingBalls[0].getBounced()) {
                controls.triggerOutput.trigger();
            }
            break;
        case Mode::BOUNCE_TRIGGERS:
            for(int i = 0; i < 4; i++) {
                Hardware::hw.cvOutputPins[i*2]->analogWrite(bouncingBalls[i].getOutput(X)*amp);
                triggerOutputs[i].update();
                if(bouncingBalls[i].getBounced()) {
                    triggerOutputs[i].trigger();
                    controls.triggerOutput.trigger();
                }
            }
            break;
        case Mode::STEPPED_TRIGGERS:
            for(int i = 0; i < 4; i++) {
                triggerOutputs[i].update();
                if(bouncingBalls[i].getBounced()) {
                    triggerOutputs[i].trigger();
                    controls.triggerOutput.trigger();
                }
                Hardware::hw.cvOutputPins[i*2]->analogWrite(bouncingBalls[i].getBounceHeight()*amp);
            }
            break;
        case Mode::ROTATE:
            if(bouncingBalls[0].getBounced()) {
                controls.triggerOutput.trigger();
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