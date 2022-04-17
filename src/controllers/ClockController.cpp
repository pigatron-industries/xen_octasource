#include "ClockController.h"
#include "common/Controls.h"

void ClockController::init(float sampleRate) {
    clock.init(sampleRate);
    clock.getFunction().setMidPoint(0.5, 0.5);
    clock.calculatePhaseIncrements();
    smoothClock.init(sampleRate);
    smoothClock.calculatePhaseIncrements();
    init();
}

void ClockController::init() {
    Serial.println("Clock");
    Hardware::hw.display.text("CLOCK");
    for(int i = 0; i < 8; i++) {
        clockDividers[i].reset();
    }

    switch(mode.value) {
        case Preset::INTEGER:
            Hardware::hw.display.text("INTEGER", Display::TEXTLINE_2);
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
            Hardware::hw.display.text("EVEN", Display::TEXTLINE_2);
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
            Hardware::hw.display.text("ODD", Display::TEXTLINE_2);
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
            Hardware::hw.display.text("POWER2", Display::TEXTLINE_2);
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
            Hardware::hw.display.text("PRIME", Display::TEXTLINE_2);
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
            Hardware::hw.display.text("FIBONACCI", Display::TEXTLINE_2);
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
            Hardware::hw.display.text("PPQN24", Display::TEXTLINE_2);
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
            smoothClock.setFrequency(rateValue);
        }
    }

    if(rangeInput.update()) {
        if(rangeInput.getValue()) {
            for(int i = 0; i < 8; i++) {
                gateOutputs[i].setZeroVoltage(-5);
            }
        } else {
            for(int i = 0; i < 8; i++) {
                gateOutputs[i].setZeroVoltage(0);
            }
        }
    }

#if defined(OCTASOURCE_MKII)
    if(distortionXCvInput.update() || distortionYCvInput.update() || lengthInput.update()) {
#else
    if(distortionXCvInput.update() || lengthInput.update()) {
#endif
        distortionX = distortionXCvInput.getValue();
#if defined(OCTASOURCE_MKII)
        distortionY = distortionYCvInput.getValue();
#endif
        clock.getFunction().setMidPoint(distortionX, distortionY);
        clock.setLength((int)lengthInput.getValue());
        clock.calculatePhaseIncrements();

        smoothClock.getFunction().setParams(distortionX, distortionY*1.8-0.9);
        smoothClock.setLength((int)lengthInput.getValue());
        smoothClock.calculatePhaseIncrements();

        Hardware::hw.display.drawWaveShape(&smoothClock.getFunction(), 0, 17, 64, 16, 1, false);
    }

    if(syncInput.update() && syncInput.isTriggeredOn()) {
        clock.externalTick();
    }

    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void ClockController::process() {
    // if(clock.process()) {
    //    tick();
    // }
    if(smoothClock.process()) {
        tick();
    }

    controls.triggerOutput.update();
}

void ClockController::tick() {
    controls.triggerOutput.trigger();
    for(int i = 0; i < 8; i++) {
        bool gate = clockGate[i].tick(clockDividers[i].tick());
        gateOutputs[i].gate(gate);
    }
}

void ClockController::setClockDivisorLength(int channel, int divisor, int length) {
    clockDividers[channel].setDivisor(divisor);
    clockGate[channel].setLength(length);
}
