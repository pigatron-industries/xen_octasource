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
    Hardware::hw.display.textLine("ENVELOPE");
    switch(parameters[Parameter::MODE].value) {
        case Mode::LATCHED:
            Hardware::hw.display.textLine("LATCHED", OLEDDisplay::TEXTLINE_2);
            break;
        case Mode::GATED:
            Hardware::hw.display.textLine("GATED", OLEDDisplay::TEXTLINE_2);
            break;
    }
    envelopeIndex = -1;
}

void EnvelopeController::update() {
    updateAttackReleaseTime();
    updateLength();
    updateAmp();

    if(syncInput.update()) {
        if(syncInput.isTriggeredOn()) {
            if(envelopeIndex >= 0) {
                envelopes[envelopeIndex].setGate(false);
            }
            envelopeIndex++;
            if(envelopeIndex >= length) {
                envelopeIndex = 0;
            }
            envelopes[envelopeIndex].setGate(true);
        } else if (parameters[Parameter::MODE].value == Mode::GATED) {
            envelopes[envelopeIndex].setGate(false);
        }
    }

    rangeInput.update();
    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
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
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void EnvelopeController::process() {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        float value = envelopes[i].process();
        if(rangeInput.getValue()) {
            value = (value * 2) - 1;
        }
        Hardware::hw.cvOutputPins[i]->analogWrite(value*amp);
    }
}