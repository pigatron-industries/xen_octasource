#include "MultipliedController.h"

void MultipliedController::init(float sampleRate) {
    AbstractOscillatorController::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setFrequency(i*1);
    }
}

void MultipliedController::update() {
    updateRate();
    updateAmp();
    updateWave();
    updateOutput();
}

void MultipliedController::process() {
    AbstractOscillatorController::process();
}

void MultipliedController::updateRate() {
    if(ratePotInput.update()) {
        float rateValue = ratePotInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            oscillators[i].setFrequency(rateValue*(i+1));
        }
    }
}