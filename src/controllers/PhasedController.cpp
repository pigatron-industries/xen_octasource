#include "PhasedController.h"

void PhasedController::init(float sampleRate) {
    AbstractOscillatorController::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setPhase(i*0.125);
    }
}

void PhasedController::update() {
    updateRate();
    updateAmp();
    updateWave();
}

void PhasedController::process() {
    AbstractOscillatorController::process();
}