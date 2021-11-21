#include "VoltageMeterController.h"

void VoltageMeterController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void VoltageMeterController::init() {
    Serial.println("Voltage Meter");
}

void VoltageMeterController::update() {
    value = Hardware::hw.syncCvPin.analogRead();
}

void VoltageMeterController::process() {
    if(value > 0) {
        for(int i = 0; i < 8; i++) {
            rangePos(i, i*0.625);
        }
    } else {
        rangeNeg(0, 0);
        for(int i = 1; i < 8; i++) {
            rangeNeg(8-i, -i*0.625);
        }
    }
}


void VoltageMeterController::rangePos(int index, float start) {
    if(value > start) {
        Hardware::hw.cvOutputPins[index]->analogWrite((value-start)*8);
    } else {
        Hardware::hw.cvOutputPins[index]->analogWrite(0);
    }
}

void VoltageMeterController::rangeNeg(int index, float start) {
    if(value < start) {
        Hardware::hw.cvOutputPins[index]->analogWrite((value-start)*8);
    } else {
        Hardware::hw.cvOutputPins[index]->analogWrite(0);
    }
}