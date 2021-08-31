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
                    oscillators[i].setFrequency(rateValue/(i+1));
                }
                break;
            case Mode::EXP:
                for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                    oscillators[i].setFrequency(rateValue/powf(2, i));
                }
                break;
            case Mode::UNCORRELATED:
                oscillators[0].setFrequency(rateValue);
                oscillators[1].setFrequency(rateValue/1.41421356);    // Square root of 2
                oscillators[2].setFrequency(rateValue/1.61803398875); // Golden Ratio
                oscillators[3].setFrequency(rateValue/2.718281828);   // Euler's Number
                oscillators[4].setFrequency(rateValue/M_PI);          // Pi
                oscillators[5].setFrequency(rateValue/(1.41421356*2));
                oscillators[6].setFrequency(rateValue/(1.61803398875*2));
                oscillators[7].setFrequency(rateValue/(2.718281828*2));
                break;
        }
    }
}