#include "EnvelopeController.h"

void EnvelopeController::init(float sampleRate) {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        envelopes[i].init(sampleRate);
        envelopes[i].setSegmentLength(0, 0.5);
        envelopes[i].setSegmentEndValue(0, 5);
        envelopes[i].setSegmentLength(1, 0.5);
        envelopes[i].setSegmentEndValue(1, 0);
    }
    init();
}

void EnvelopeController::init() {
    Serial.println("Envelope");
    envelopeIndex = -1;
}

void EnvelopeController::update() {
    updateAttackReleaseTime();
    updateLength();
    updateAmp();

    if(triggerInput.update()) {
        if(triggerInput.isTriggeredOn()) {
            if(envelopeIndex >= 0) {
                envelopes[envelopeIndex].trigger(false);
            }
            envelopeIndex++;
            if(envelopeIndex >= length) {
                envelopeIndex = 0;
            }
            envelopes[envelopeIndex].trigger(true);
        } else if (mode.value == Mode::GATED) {
            envelopes[envelopeIndex].trigger(false);
        }
    }
}

void EnvelopeController::updateAttackReleaseTime() {
    if(attackTimeCvInput.update()) {
        float attackTimeValue = attackTimeCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            envelopes[i].setSegmentLength(0, attackTimeValue);
        }
    }
    if(releaseTimeCvInput.update()) {
        float releaseTimeValue = releaseTimeCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            envelopes[i].setSegmentLength(1, releaseTimeValue);
        }
    }
}

void EnvelopeController::updateLength() {
    #if defined(OCTASOURCE_MKII)
        if(lengthCvInput.update()) {
            length = lengthCvInput.getValue();
        }
    #endif
}

void EnvelopeController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void EnvelopeController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        float value = envelopes[i].process();
        Hardware::hw.cvOutputPins[i]->analogWrite(value);
    }
}