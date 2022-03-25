#include "AudioFrequencyController.h"

void AudioFrequencyController::init(float sampleRate) {
    FrequencyController::init(sampleRate);
}

void AudioFrequencyController::init() {
    Serial.println("Audio Frequency");
    Hardware::hw.display.title("AUDIO");
    updateRate();
}

void AudioFrequencyController::update() {
    updateRate();
    updateAmp();
    updateWave();
    Hardware::hw.updateOutputLeds();
}

void AudioFrequencyController::updateRate() {
    if(controls.expRateCvInput.update()) {
        FrequencyController::setRate(controls.expRateCvInput.getValue());
    }
}

void AudioFrequencyController::process() {
    FrequencyController::process();
}
