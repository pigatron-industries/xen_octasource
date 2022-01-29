#include "AudioFrequencyController.h"

void AudioFrequencyController::init(float sampleRate) {
    FrequencyController::init(sampleRate);
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
    if(Controls::expRateCvInput.update()) {
        FrequencyController::setRate(Controls::expRateCvInput.getValue());
    }
}

void AudioFrequencyController::process() {
    FrequencyController::process();
}
