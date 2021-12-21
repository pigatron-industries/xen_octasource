#include "FrequencyController.h"

void FrequencyController::init(float sampleRate) {
    AbstractOscillatorController::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setFrequency(i*1);
    }
}

void FrequencyController::update() {
    updateRate();
    updateAmp();
    updateWave();
    Hardware::hw.updateOutputLeds();
}

void FrequencyController::process() {
    AbstractOscillatorController::process();
}

void FrequencyController::updateRate() {
    if(bipolarRateCvInput.update()) {
        float rateValue = bipolarRateCvInput.getValue();
        setRate(rateValue);
    }
}

void FrequencyController::setRate(float baseFrequency) {
    switch (mode.value) {
        case Mode::LINEAR:
            for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                oscillators[i].setFrequency(baseFrequency/(i+1));
            }
            break;
        case Mode::EXP:
            for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                oscillators[i].setFrequency(baseFrequency/powf(2, i));
            }
            break;
        case Mode::UNCORRELATED:
            oscillators[0].setFrequency(baseFrequency);
            oscillators[1].setFrequency(baseFrequency/1.2020569);     // zeta 3
            oscillators[2].setFrequency(baseFrequency/1.41421356);    // root 2
            oscillators[3].setFrequency(baseFrequency/1.61803398875); // phi
            oscillators[4].setFrequency(baseFrequency/2.718281828);   // e
            oscillators[5].setFrequency(baseFrequency/M_PI);          // pi
            oscillators[6].setFrequency(baseFrequency/4.669201609);   // feigenbaum constant
            oscillators[7].setFrequency(baseFrequency/23.140692632);  // e^pi
            break;
        case Mode::PLANETARY:
            oscillators[0].setFrequency(baseFrequency);        // mercury
            oscillators[1].setFrequency(baseFrequency/2.553);  // venus
            oscillators[2].setFrequency(baseFrequency/4.152);  // earth
            oscillators[3].setFrequency(baseFrequency/7.810);  // mars
            oscillators[4].setFrequency(baseFrequency/49.243); // jupiter
            oscillators[5].setFrequency(baseFrequency/122.319);// saturn
            oscillators[6].setFrequency(baseFrequency/348.812);// uranus
            oscillators[7].setFrequency(baseFrequency/684.255);// neptune
            break;
    }
}