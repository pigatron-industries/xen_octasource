#include "AudioFrequencyController.h"

void AudioFrequencyController::init(float sampleRate) {
    AbstractOscillatorController::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        oscillators[i].setFrequency(i*1);
    }
}

void AudioFrequencyController::init() {
    Serial.println("Audio Frequency");
    updateRate();
}

void AudioFrequencyController::update() {
    updateRate();
    updateAmp();
    updateWave();
    Hardware::hw.updateOutputLeds();
}

void AudioFrequencyController::updateRate() {
    if(expRateCvInput.update())
    FrequencyController::setRate(expRateCvInput.getValue());
}

void AudioFrequencyController::process() {
    // bool tick = clockDivider.tick();
    // if(tick) {
    //     FrequencyController::setRate(expRateCvInput.getValue());
    // }
    AbstractOscillatorController::process();
}