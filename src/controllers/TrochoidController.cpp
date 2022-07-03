#include "TrochoidController.h"

void TrochoidController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void TrochoidController::init() {
    Serial.println("Trochoid");
    Hardware::hw.display.text("TROCHOID");
    hypotrochoid.init(sampleRate);

    // switch(mode.value) {
    //     case Mode::HYPOTROCHOID:
    //         Hardware::hw.display.text("HYPOTROCHOID", Display::TEXTLINE_2);
    //         break;
    // }

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
    //if(clockDivider.tick()) {
        //switch(mode.value) {
        //case Mode::HYPOTROCHOID:
            hypotrochoid.process();
            Hardware::hw.cvOutputPins[0]->analogWrite(hypotrochoid.getOutput(X));
            Hardware::hw.cvOutputPins[1]->analogWrite(hypotrochoid.getOutput(Y));
            // break;
        //}
    //}
}