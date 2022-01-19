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
    if(bipolarRateCvInput.update()) {
        float rateValue = bipolarRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void PhasedController::updateRateExponential() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void PhasedController::updateAmp() {
    if(ampCvInput.update()) {
        float ampValue = ampCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setAmp(ampValue);
        }
    }
}

void PhasedController::updateWave() {
    if(waveCvInput.update()) {
        float waveValue = waveCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            if(waveValue < 1) {
                oscillators[i].setWaveform(Oscillator::WAVE_SIN);
            } else if (waveValue < 2) {
                oscillators[i].setWaveform(Oscillator::WAVE_TRI);
            } else if (waveValue < 3) {
                oscillators[i].setWaveform(Oscillator::WAVE_POLYBLEP_SAW);
            } else {
                oscillators[i].setWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
            }
        }
    }
}

void PhasedController::updatePhase() {
    // if(phaseCvInput.update()) {
    //     float phaseDiffValue = phaseCvInput.getValue();
    //     float phase = oscillators[0].getPhase();
    //     for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
    //         oscillators[i].setPhase(phase + i*phaseDiffValue);
    //     }
    // }
}

void PhasedController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process());
    }
}
