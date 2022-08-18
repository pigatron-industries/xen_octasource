#include "TrochoidController.h"

void TrochoidController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void TrochoidController::init() {
    Serial.println("Trochoid");
    Hardware::hw.display.text("TROCHOID");
    hypotrochoid.init(sampleRate);
    updateParams();
}

void TrochoidController::update() {
    updateRate();
    updateParams();
    Hardware::hw.updateOutputLeds();
}

void TrochoidController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        hypotrochoid.setFrequency(rateValue);
    }
}

void TrochoidController::updateParams() {
    if(largeRadiusInput.update() | smallRadiusInput.update()) {
        hypotrochoid.setRadiusLargeSmall(largeRadiusInput.getValue(), smallRadiusInput.getValue());
    }
    
    #if defined(OCTASOURCE_MKII)
    if(pointRadiusInput.update()) {
        float pointRadius = pointRadiusInput.getValue();
        hypotrochoid.setRadiusPoint(pointRadius);
    }
    #endif
}

void TrochoidController::process() {
    hypotrochoid.process();
    Vector<2>& output = hypotrochoid.getOutput();
    Hardware::hw.cvOutputPins[0]->analogWrite(output[X]);
    Hardware::hw.cvOutputPins[1]->analogWrite(output[Y]);
    Hardware::hw.cvOutputPins[2]->analogWrite(output.length());
}