#include "FilterController.h"

void FilterController::init(float sampleRate) {
    AbstractOscillatorController::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
        filters[i].init(sampleRate);
    }
    oscillators[0].setWaveform(Oscillator::WAVE_SIN);
    oscillators[1].setWaveform(Oscillator::WAVE_TRI);
    oscillators[2].setWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    oscillators[3].setWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);

    oscillators[4].setWaveform(Oscillator::WAVE_SIN);
    oscillators[5].setWaveform(Oscillator::WAVE_TRI);
    oscillators[6].setWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    oscillators[7].setWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
    init();
}

void FilterController::init() {
}

void FilterController::update() {
    updateRateBipolar();
    updateFilterFrequency();
    updateFilterResonance();
    updateAmp();
    Hardware::hw.updateOutputLeds();
}

void FilterController::updateRateBipolar() {
    if(bipolarRateCvInput.update()) {
        float rateValue = bipolarRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue);
        }
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

void FilterController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        float value = oscillators[i].process();
        filters[i].process(value);
        Hardware::hw.cvOutputPins[i]->analogWrite(filters[i].low());
        //Hardware::hw.cvOutputPins[i]->analogWrite(value);
    }
}
