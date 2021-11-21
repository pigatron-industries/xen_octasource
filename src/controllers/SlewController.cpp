#include "SlewController.h"

void SlewController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        filters[i].init(sampleRate);
        filters[i].setResonance(0);
        filters[i].setFrequency(1/((i+1)*0.1));
    }
    init();
}

void SlewController::init() {
    Serial.println("Quantizer");
}

void SlewController::update() {
}

void SlewController::process() {
    if(clockDivider.tick()) {
        value = Hardware::hw.syncCvPin.analogRead();
    }

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        filters[i].process(value);
        Hardware::hw.cvOutputPins[i]->analogWrite(filters[i].low());
    }
}
