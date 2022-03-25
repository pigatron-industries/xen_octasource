#include "PhasedController.h"

void PhasedController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
    }
    init();
}

void PhasedController::init() {
    Serial.println("Phase");
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setPhase(i*0.125);
    }
}

void PhasedController::update() {
    switch (mode.value) {
        case Mode::BIPOLAR_LFO:
            updateRateBipolar();
            break;
        case Mode::EXPONENTIAL_VCO:
            updateRateExponential();
            break;
    }
    updateAmp();
    updateWave();
    updatePhase();
    Hardware::hw.updateOutputLeds();
}

void PhasedController::updateRateBipolar() {
    if(controls.bipolarRateCvInput.update()) {
        float rateValue = controls.bipolarRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void PhasedController::updateRateExponential() {
    if(controls.expRateCvInput.update()) {
        float rateValue = controls.expRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void PhasedController::updateAmp() {
    if(controls.ampCvInput.update()) {
        ampValue = controls.ampCvInput.getValue();
    }
}

void PhasedController::updateWave() {
    if(controls.waveCvInput.update()) {
        float waveValue = controls.waveCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            if(waveValue < 1) {
                waveSelector.select(0);
            } else if (waveValue < 2) {
                waveSelector.select(1);
            } else if (waveValue < 3) {
                waveSelector.select(2);
            } else {
                waveSelector.select(3);
            }
        }
    }
}

void PhasedController::updatePhase() {
    // if(Controls::phaseCvInput.update()) {
    //     float phaseDiffValue = Controls::phaseCvInput.getValue();
    //     float phase = oscillators[0].getPhase();
    //     for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
    //         oscillators[i].setPhase(phase + i*phaseDiffValue);
    //     }
    // }
}

void PhasedController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process() * ampValue);
    }
}
