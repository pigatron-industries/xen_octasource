#include "AbstractOscillatorController.h"

void AbstractOscillatorController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
    }
}

void AbstractOscillatorController::update() {
    updateRateBipolar();
    updateAmp();
    updateWave();
}

void AbstractOscillatorController::updateRateBipolar() {
    if(bipolarRateCvInput.update()) {
        float rateValue = bipolarRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void AbstractOscillatorController::updateRateExponential() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void AbstractOscillatorController::updateAmp() {
    if(ampCvInput.update()) {
        float ampValue = ampCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setAmp(ampValue);
        }
    }
}

void AbstractOscillatorController::updateWave() {
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

void AbstractOscillatorController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process());
    }
}
