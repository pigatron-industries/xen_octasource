#include "EnvelopeController.h"

void EnvelopeController::init(float sampleRate) {

    envelopeShape.segment(0).setLength(0.5);
    envelopeShape.segment(0).setStartValue(0);
    envelopeShape.segment(0).setEndValue(1);
    
    envelopeShape.segment(1).setLength(0.5);
    envelopeShape.segment(1).setStartValue(1);
    envelopeShape.segment(1).setEndValue(0);

    envelopeShape.setSustainPhase(0.5);

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        envelopes[i].init(sampleRate);
    }
    init();
}

void EnvelopeController::init() {
    Serial.println("Sequential Envelope");
    envelopeIndex = -1;
}

void EnvelopeController::update() {
    updateAttackReleaseTime();
    updateLength();
    updateAmp();

    if(controls.syncInput.update()) {
        if(controls.syncInput.isTriggeredOn()) {
            if(envelopeIndex >= 0) {
                envelopes[envelopeIndex].setGate(false);
            }
            envelopeIndex++;
            if(envelopeIndex >= length) {
                envelopeIndex = 0;
            }
            envelopes[envelopeIndex].setGate(true);
        } else if (mode.value == Mode::GATED) {
            envelopes[envelopeIndex].setGate(false);
        }
    }

    Hardware::hw.updateOutputLeds();
}

void EnvelopeController::updateAttackReleaseTime() {
    if(attackTimeCvInput.update()) {
        float attackTimeValue = attackTimeCvInput.getValue();
        envelopeShape.setSegmentLength(0, attackTimeValue);
        envelopeShape.setSustainPhase(attackTimeValue);
    }
    if(releaseTimeCvInput.update()) {
        float releaseTimeValue = releaseTimeCvInput.getValue();
        envelopeShape.setSegmentLength(1, releaseTimeValue);
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
    if(controls.ampCvInput.update()) {
        amp = controls.ampCvInput.getValue();
    }
}

void EnvelopeController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        float value = envelopes[i].process();
        Hardware::hw.cvOutputPins[i]->analogWrite(value*amp);
    }
}