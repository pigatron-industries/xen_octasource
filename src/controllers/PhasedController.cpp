#include "PhasedController.h"

void PhasedController::init(float sampleRate) {
    AbstractOscillatorController::init(sampleRate);
    init();
}

void PhasedController::init() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setPhase(i*0.125);
    }
}

void PhasedController::update() {
    switch (mode.value) {
        case Mode::BIPOLAR_LFO:
            updateRateBipolar();
            break;
        case Mode::EXPONENTIAL_VCO:
            updateRateExponential();
            break;
    }
    updateAmp();
    updateWave();
    updatePhase();
}

void PhasedController::updatePhase() {
    // if(phaseCvInput.update()) {
    //     float phaseDiffValue = phaseCvInput.getValue();
    //     float phase = oscillators[0].getPhase();
    //     for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
    //         oscillators[i].setPhase(phase + i*phaseDiffValue);
    //     }
    // }
}

void PhasedController::process() {
    AbstractOscillatorController::process();
}