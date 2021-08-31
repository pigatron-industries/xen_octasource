#include "FrequencyController.h"

void FrequencyController::init() {
    AbstractOscillatorController::init();
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setFrequency(i*1);
    }
}

void FrequencyController::update() {
    updateRate();
    updateAmp();
    updateWave();
    updateOutput();
}

void FrequencyController::process() {
    AbstractOscillatorController::process();
}

void FrequencyController::updateRate() {
    if(ratePotInput.update()) {
        float rateValue = ratePotInput.getValue();
        switch (mode.value) {
            case Mode::LINEAR:
                for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                    oscillators[i].setFrequency(rateValue*(i+1));
                }
                break;
            case Mode::EXP:
                for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                    oscillators[i].setFrequency(rateValue*powf(2, i));
                }
                break;
        }
    }
}