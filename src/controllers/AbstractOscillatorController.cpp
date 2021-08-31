#include "AbstractOscillatorController.h"

void AbstractOscillatorController::init(float sampleRate) {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
        oscillators[i].setFrequency(1);
        oscillators[i].setAmp(5);
        oscillators[i].setWaveform(Oscillator::WAVE_SIN);
    }
}

void AbstractOscillatorController::update() {
    updateRate();
    updateAmp();
    updateWave();
    updateOutput();
}

void AbstractOscillatorController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        outputValues[i] = oscillators[i].process();
    }
}


void AbstractOscillatorController::updateRate() {
    if(ratePotInput.update()) {
        float rateValue = ratePotInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
    }
}

void AbstractOscillatorController::updateAmp() {
    if(ampPotInput.update()) {
        float ampValue = ampPotInput.getValue();
        Serial.println(ampValue);
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setAmp(ampValue);
        }
    }
}

void AbstractOscillatorController::updateWave() {
    if(wavePotInput.update()) {
        float waveValue = wavePotInput.getValue();
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

void AbstractOscillatorController::updateOutput() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i].writeVoltage(outputValues[i]);
    }
}