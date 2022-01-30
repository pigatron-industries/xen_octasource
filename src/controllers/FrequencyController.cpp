#include "FrequencyController.h"

void FrequencyController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
        oscillators[i].setFrequency(1);
    }
    init();
}

void FrequencyController::init() {
    Serial.println("Frequency");
}

void FrequencyController::update() {
    updateRate();
    updateAmp();
    updateWave();
    Hardware::hw.updateOutputLeds();
}

void FrequencyController::updateRate() {
    if(Controls::bipolarRateCvInput.update()) {
       float rateValue = Controls::bipolarRateCvInput.getValue();
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

void FrequencyController::updateAmp() {
    if(Controls::ampCvInput.update()) {
        ampValue = Controls::ampCvInput.getValue();
    }
}

void FrequencyController::updateWave() {
    if(Controls::waveCvInput.update()) {
        float waveValue = Controls::waveCvInput.getValue();
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

void FrequencyController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process() * ampValue);
    }
}
