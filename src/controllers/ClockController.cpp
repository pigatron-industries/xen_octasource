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
        case Mode::INTEGER:
            clockDividers[0].setDivisor(2);
            clockDividers[1].setDivisor(3);
            clockDividers[2].setDivisor(4);
            clockDividers[3].setDivisor(5);
            clockDividers[4].setDivisor(6);
            clockDividers[5].setDivisor(7);
            clockDividers[6].setDivisor(8);
            clockDividers[7].setDivisor(9);
            break;
        case Mode::EVEN:
            clockDividers[0].setDivisor(2);
            clockDividers[1].setDivisor(4);
            clockDividers[2].setDivisor(6);
            clockDividers[3].setDivisor(8);
            clockDividers[4].setDivisor(10);
            clockDividers[5].setDivisor(12);
            clockDividers[6].setDivisor(14);
            clockDividers[7].setDivisor(16);
            break;
        case Mode::ODD:
            clockDividers[0].setDivisor(3);
            clockDividers[1].setDivisor(5);
            clockDividers[2].setDivisor(7);
            clockDividers[3].setDivisor(9);
            clockDividers[4].setDivisor(11);
            clockDividers[5].setDivisor(13);
            clockDividers[6].setDivisor(15);
            clockDividers[7].setDivisor(17);
            break;
        case Mode::POWER2:
            clockDividers[0].setDivisor(2);
            clockDividers[1].setDivisor(4);
            clockDividers[2].setDivisor(8);
            clockDividers[3].setDivisor(16);
            clockDividers[4].setDivisor(32);
            clockDividers[5].setDivisor(64);
            clockDividers[6].setDivisor(128);
            clockDividers[7].setDivisor(256);
            break;
        case Mode::PRIME:
            clockDividers[0].setDivisor(2);
            clockDividers[1].setDivisor(3);
            clockDividers[2].setDivisor(5);
            clockDividers[3].setDivisor(7);
            clockDividers[4].setDivisor(11);
            clockDividers[5].setDivisor(13);
            clockDividers[6].setDivisor(17);
            clockDividers[7].setDivisor(19);
            break;
        case Mode::FIBONACCI:
            clockDividers[0].setDivisor(2);
            clockDividers[1].setDivisor(3);
            clockDividers[2].setDivisor(5);
            clockDividers[3].setDivisor(8);
            clockDividers[4].setDivisor(13);
            clockDividers[5].setDivisor(21);
            clockDividers[6].setDivisor(34);
            clockDividers[7].setDivisor(55);
            break;
        case Mode::PPQN24:
            clockDividers[0].setDivisor(1); // Clock
            clockDividers[1].setDivisor(6);
            clockDividers[2].setDivisor(8); //24/3
            clockDividers[3].setDivisor(12);
            clockDividers[4].setDivisor(24);
            clockDividers[5].setDivisor(32);//96/3
            clockDividers[6].setDivisor(48);
            clockDividers[7].setDivisor(96);
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
    for(int i = 0; i < 8; i++) {
        triggerOutputs[i].update();
    }
}

void ClockController::tick() {
    triggerOutput.trigger();
    for(int i = 0; i < 8; i++) {
        if(clockDividers[i].tick()) {
            triggerOutputs[i].trigger();
        }
    }
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