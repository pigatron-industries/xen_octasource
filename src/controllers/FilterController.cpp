#include "FilterController.h"

void FilterController::init(float sampleRate) {
    Controller::init(sampleRate);
    sineOscillator.init(sampleRate);
    triangleOscillator.init(sampleRate);
    sawOscillator.init(sampleRate);
    pulseOscillator.init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        filters[i].init(sampleRate);
    }
    init();
}

void FilterController::init() {
    Serial.println("Filter");
}

void FilterController::update() {
    updateRateBipolar();
    updateFilterFrequency();
    updateFilterResonance();
    updateAmp();
    Hardware::hw.updateOutputLeds();
}

void FilterController::updateRateBipolar() {
    if(Controls::bipolarRateCvInput.update()) {
        float rateValue = Controls::bipolarRateCvInput.getValue();
        sineOscillator.setFrequency(rateValue);
        triangleOscillator.setFrequency(rateValue);
        sawOscillator.setFrequency(rateValue);
        pulseOscillator.setFrequency(rateValue);
    }
}

void FilterController::updateFilterFrequency() {
    if(filterCvInput.update()) {
        float filterFrequency = filterCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            filters[i].setFrequency(filterFrequency);
        }
    }
}

void FilterController::updateFilterResonance() {
    #if defined(OCTASOURCE_MKII)
        if(resonanceCvInput.update()) {
            float resonance = resonanceCvInput.getValue();
            for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                filters[i].setResonance(resonance);
            }
        }
    #endif
}

void FilterController::updateAmp() {
    if(Controls::ampCvInput.update()) {
        ampValue = Controls::ampCvInput.getValue();
    }
}

void FilterController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        float value = oscillators[i]->process();
        filters[i].process(value);
        Hardware::hw.cvOutputPins[i]->analogWrite(filters[i].low() * ampValue);
    }
}
