#include "AbstractOscillatorController.h"

void AbstractOscillatorController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
    }
}

void AbstractOscillatorController::update() {
    updateRate();
    updateAmp();
    updateWave();
}

void AbstractOscillatorController::updateRate() {
    if(rateCvInput.update()) {
        float rateValue = rateCvInput.getValue();
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
                oscillators[i].setWaveform(Oscillator::WAVE_RAMP);
            } else if (waveValue < 4) {
                oscillators[i].setWaveform(Oscillator::WAVE_SAW);
            } else {
                oscillators[i].setWaveform(Oscillator::WAVE_SQUARE);
            }
        }
    }
}

void AbstractOscillatorController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process());
    }
}
