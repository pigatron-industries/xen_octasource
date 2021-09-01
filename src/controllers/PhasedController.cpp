#include "PhasedController.h"

void PhasedController::init() {
    AbstractOscillatorController::init();
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setPhase(i*0.125);
    }
}

void PhasedController::update() {
    updateRate();
    updateAmp();
    updateWave();
    updateOutput();
}

void PhasedController::process() {
    AbstractOscillatorController::process();
}