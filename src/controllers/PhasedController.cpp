#include "PhasedController.h"

void PhasedController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].init(sampleRate);
    }
    clock.init(sampleRate/SAMPLERATE_DIVIDER);
    init();
}

void PhasedController::init() {
    Serial.println("Phase");
    Hardware::hw.display.textLine("PHASE");
    resetPhases();
}

void PhasedController::resetPhases() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setPhase(i*0.125);
    }
}

void PhasedController::update() {
    updateRate();
    updateAmp();
    updateWave();
    updatePhase();
    Hardware::hw.updateOutputLeds();
}

void PhasedController::updateRate() {
    if(clock.getState() != InternalExternalClock::State::CLK_EXTERNAL) {
        switch (parameters[Parameter::MODE].value) {
            case Mode::BIPOLAR_LFO:
                if(bipolarRateCvInput.update()) {
                    setFrequency(bipolarRateCvInput.getValue());
                }
                break;
            case Mode::EXPONENTIAL_VCO:
                if(expRateCvInput.update()) {
                    setFrequency(expRateCvInput.getValue());
                }
                break;
        }
    } else if(clock.getState() == InternalExternalClock::State::CLK_EXTERNAL) {
        float externalFrequency = clock.getFrequency();
        if(externalFrequency != syncFrequency || syncMultCvInput.update()) {
            syncFrequency = externalFrequency;
            int mult = syncMultCvInput.getIntValue();
            setFrequency(syncFrequency * mult);
        }
    }
}

void PhasedController::updateAmp() {
    if(ampCvInput.update()) {
        ampValue = ampCvInput.getValue();
    }
}

void PhasedController::updateWave() {
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

void PhasedController::updatePhase() {
    // if(Controls::phaseCvInput.update()) {
    //     float phaseDiffValue = Controls::phaseCvInput.getValue();
    //     float phase = oscillators[0].getPhase();
    //     for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
    //         oscillators[i].setPhase(phase + i*phaseDiffValue);
    //     }
    // }
}

void PhasedController::updateSync() {
    if(syncInput.update() && syncInput.isTriggeredOn()) {
        clock.externalTick();
    }
    if(hardSyncInput.update() && hardSyncInput.isTriggeredOn()) {
        resetPhases();
    }
}

void PhasedController::setFrequency(float frequency) {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setFrequency(frequency);
    }
}

void PhasedController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(oscillators[i].process() * ampValue);
    }
    if(clockDivider.tick()) {
        updateSync();
        clock.process();
    }
}
