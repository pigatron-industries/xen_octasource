#include "ClockController.h"

void ClockController::init() {
    AbstractOscillatorController::init();
}

void ClockController::update() {
    updateRate();
    updateAmp();
    updateWave();
    updateOutput();
}

void ClockController::process() {
    AbstractOscillatorController::process();
}