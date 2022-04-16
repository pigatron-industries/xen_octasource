#include "FrequencyController.h"

void FrequencyController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
        oscillators[i].setFrequency(1);
    }
    clock.init(sampleRate/SAMPLERATE_DIVIDER);
    init();
}

void FrequencyController::init() {
    Serial.println("Frequency");
    Hardware::hw.display.text("FREQUENCY");
    switch(mode.value) {
        case Mode::LINEAR:
            Hardware::hw.display.text("LINEAR", Display::TEXTLINE_2);
            break;
        case Mode::EXP:
            Hardware::hw.display.text("EXPONENTIAL", Display::TEXTLINE_2);
            break;
        case Mode::POLYRHYTHM:
            Hardware::hw.display.text("POLYRHYTHM", Display::TEXTLINE_2);
            break;
        case Mode::INTERVAL:
            Hardware::hw.display.text("INTERVAL", Display::TEXTLINE_2);
            break;
        case Mode::UNCORRELATED:
            Hardware::hw.display.text("UNCORRELATED", Display::TEXTLINE_2);
            break;
        case Mode::PLANETARY:
            Hardware::hw.display.text("PLANETARY", Display::TEXTLINE_2);
            break;
    }
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setPhase(0);
    }
    setRate(rateCvInput.getValue());
}

void FrequencyController::update() {
    updateRate();
    updateAmp();
    updateWave();
    Hardware::hw.updateOutputLeds();
}

void FrequencyController::updateRate() {
    if(clock.getState() != Clock::State::CLK_EXTERNAL) {
        if(rateCvInput.update()) {
            float frequency = rateCvInput.getValue();
            setRate(frequency);
        }
    } else if(clock.getState() == Clock::State::CLK_EXTERNAL) {
        float externalFrequency = clock.getFrequency();
        if(externalFrequency != syncFrequency || syncMultCvInput.update()) {
            syncFrequency = externalFrequency;
            int multInputValue = syncMultCvInput.getIntValue();
            float mult = multInputValue >= 0 ? multInputValue+1 : 1/float(-multInputValue);
            setRate(syncFrequency * mult);
        }
    }
}

void FrequencyController::setRate(float baseFrequency) {
    switch (mode.value) {
        case Mode::LINEAR:
            oscillators[0].setFrequency(baseFrequency);
            oscillators[1].setFrequency(baseFrequency/2);
            oscillators[2].setFrequency(baseFrequency/3);
            oscillators[3].setFrequency(baseFrequency/4);
            oscillators[4].setFrequency(baseFrequency/5);
            oscillators[5].setFrequency(baseFrequency/6);
            oscillators[6].setFrequency(baseFrequency/7);
            oscillators[7].setFrequency(baseFrequency/8);
            break;
        case Mode::EXP:
            oscillators[0].setFrequency(baseFrequency);
            oscillators[1].setFrequency(baseFrequency/2);
            oscillators[2].setFrequency(baseFrequency/4);
            oscillators[3].setFrequency(baseFrequency/8);
            oscillators[4].setFrequency(baseFrequency/16);
            oscillators[5].setFrequency(baseFrequency/32);
            oscillators[6].setFrequency(baseFrequency/64);
            oscillators[7].setFrequency(baseFrequency/128);
            break;
        case Mode::POLYRHYTHM:
            oscillators[0].setFrequency(baseFrequency*8/8);
            oscillators[1].setFrequency(baseFrequency*7/8);
            oscillators[2].setFrequency(baseFrequency*6/8);
            oscillators[3].setFrequency(baseFrequency*5/8);
            oscillators[4].setFrequency(baseFrequency*4/8);
            oscillators[5].setFrequency(baseFrequency*3/8);
            oscillators[6].setFrequency(baseFrequency*2/8);
            oscillators[7].setFrequency(baseFrequency*1/8);
            break;
        case Mode::INTERVAL:
            oscillators[0].setFrequency(baseFrequency);
            oscillators[1].setFrequency(baseFrequency/1.2);     // Minor THird
            oscillators[2].setFrequency(baseFrequency/1.25);    // Major Third
            oscillators[3].setFrequency(baseFrequency/1.33333); // Perfect Fourth
            oscillators[4].setFrequency(baseFrequency/1.5);     // Perfect Fifth
            oscillators[5].setFrequency(baseFrequency/1.6);     // Minor Sixth
            oscillators[6].setFrequency(baseFrequency/1.66667); // Major Sixth
            oscillators[7].setFrequency(baseFrequency/2);       // Octave
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
    if(ampCvInput.update()) {
        ampValue = ampCvInput.getValue();
    }
}

void FrequencyController::updateWave() {
    if(waveCvInput.update()) {
        float waveValue = waveCvInput.getValue();
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
        Hardware::hw.display.drawWaveShape(&waveSelector, 0, 17, 32, 16, 2);
    }
}

void FrequencyController::updateSync() {
    if(syncInput.update() && syncInput.isTriggeredOn()) {
        clock.externalTick();
    }
    // if(hardSyncInput.update() && hardSyncInput.isTriggeredOn()) {
    //     resetPhases();
    // }
}

void FrequencyController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process() * ampValue);
    }
    if(clockDivider.tick()) {
        updateSync();
        clock.process();
    }
}
