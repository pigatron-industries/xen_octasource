#include "ClockController.h"

void ClockController::init(float sampleRate) {
    clock.init(sampleRate);
    init();
}

void ClockController::init() {
    Serial.println("Clock");
    for(int i = 0; i < 8; i++) {
        clockDividers[i].reset();
    }

    clock.getFunction().setMidPoint(0.5, 0.5);
    clock.calculatePhaseIncrements();

    switch(mode.value) {
        case Preset::INTEGER:
            setClockDivisorLength(0, 2, 1);
            setClockDivisorLength(1, 3, 2);
            setClockDivisorLength(2, 4, 3);
            setClockDivisorLength(3, 5, 4);
            setClockDivisorLength(4, 6, 5);
            setClockDivisorLength(5, 7, 6);
            setClockDivisorLength(6, 8, 7);
            setClockDivisorLength(7, 9, 8);
            break;
        case Preset::EVEN:
            setClockDivisorLength(0, 2,  1);
            setClockDivisorLength(1, 4,  2);
            setClockDivisorLength(2, 6,  3);
            setClockDivisorLength(3, 8,  4);
            setClockDivisorLength(4, 10, 5);
            setClockDivisorLength(5, 12, 6);
            setClockDivisorLength(6, 14, 7);
            setClockDivisorLength(7, 16, 8);
            break;
        case Preset::ODD:
            setClockDivisorLength(0, 3,  1);
            setClockDivisorLength(1, 5,  2);
            setClockDivisorLength(2, 7,  3);
            setClockDivisorLength(3, 9,  4);
            setClockDivisorLength(4, 11, 5);
            setClockDivisorLength(5, 13, 6);
            setClockDivisorLength(6, 15, 7);
            setClockDivisorLength(7, 17, 8);
            break;
        case Preset::POWER2:
            setClockDivisorLength(0, 2, 1);
            setClockDivisorLength(1, 4, 2);
            setClockDivisorLength(2, 8, 4);
            setClockDivisorLength(3, 16, 8);
            setClockDivisorLength(4, 32, 16);
            setClockDivisorLength(5, 64, 32);
            setClockDivisorLength(6, 128, 64);
            setClockDivisorLength(7, 256, 128);
            break;
        case Preset::PRIME:
            setClockDivisorLength(0, 2,  1);
            setClockDivisorLength(1, 3,  2);
            setClockDivisorLength(2, 5,  3);
            setClockDivisorLength(3, 7,  5);
            setClockDivisorLength(4, 11, 7);
            setClockDivisorLength(5, 13, 11);
            setClockDivisorLength(6, 17, 13);
            setClockDivisorLength(7, 19, 17);
            break;
        case Preset::FIBONACCI:
            setClockDivisorLength(0, 2,  1);
            setClockDivisorLength(1, 3,  2);
            setClockDivisorLength(2, 5,  3);
            setClockDivisorLength(3, 8,  5);
            setClockDivisorLength(4, 13, 8);
            setClockDivisorLength(5, 21, 13);
            setClockDivisorLength(6, 34, 21);
            setClockDivisorLength(7, 55, 34);
            break;
        case Preset::PPQN24:
            setClockDivisorLength(0, 3,  1);
            setClockDivisorLength(1, 6,  3);
            setClockDivisorLength(2, 8,  4);
            setClockDivisorLength(3, 12, 6);
            setClockDivisorLength(4, 24, 12);
            setClockDivisorLength(5, 32, 16);
            setClockDivisorLength(6, 48, 24);
            setClockDivisorLength(7, 96, 48);
            break;
    }
}

void ClockController::update() {
    if(rateCvInput.update()) {
        float rateValue = rateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            clock.setFrequency(rateValue);
        }
    }

    if(distortionXCvInput.update() || distortionYCvInput.update() || lengthInput.update()) {
        distortionX = distortionXCvInput.getValue();
        distortionY = distortionYCvInput.getValue();
        clock.getFunction().setMidPoint(distortionX, distortionY);
        clock.setLength((int)lengthInput.getValue());
        clock.calculatePhaseIncrements();
    }

    if(Controls::syncInput.update() && Controls::syncInput.isTriggeredOn()) {
        clock.externalTick();
    }

    updateOutputLeds();
}

void ClockController::process() {
    if(clock.process()) {
        tick();
    }

    triggerOutput.update();
}

void ClockController::tick() {
    triggerOutput.trigger();
    for(int i = 0; i < 8; i++) {
        bool gate = clockGate[i].tick(clockDividers[i].tick());
        gateOutputs[i].gate(gate);
    }
}

void ClockController::setClockDivisorLength(int channel, int divisor, int length) {
    clockDividers[channel].setDivisor(divisor);
    clockGate[channel].setLength(length);
}

void ClockController::updateOutputLeds() {
    #if defined(OCTASOURCE_MKII)
        float distortionAmount = distortionX - distortionY;
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            float value = Hardware::hw.cvOutputPins[i]->getAnalogValue();
            if(value > 0) {
                Hardware::hw.outputGreenLeds[i]->analogWrite(value*0.1);
            } else {
                Hardware::hw.outputGreenLeds[i]->analogWrite(0);
                if(distortionAmount > 0) {
                    Hardware::hw.outputRedLeds[i]->analogWrite(0);
                    Hardware::hw.outputBlueLeds[i]->analogWrite(distortionAmount*0.1);
                } else {
                    Hardware::hw.outputRedLeds[i]->analogWrite(-distortionAmount*0.1);
                    Hardware::hw.outputBlueLeds[i]->analogWrite(0);
                }
            }
        }
    #endif
}