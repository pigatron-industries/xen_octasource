#include "ClockedController.h"

void ClockedController::init(float sampleRate) {
    Serial.println("ClockedController::init");
    clock.init(sampleRate);
}

void ClockedController::init() {
}

void ClockedController::update() {
    updateRate();
}

bool ClockedController::updateRate(bool force) {
    if(clock.getState() != InternalExternalClock::State::CLK_EXTERNAL) {
        if(rateCvInput.update() || force) {
            clock.setFrequency(rateCvInput.getValue());
            return true;
        }
    } else if(clock.getState() == InternalExternalClock::State::CLK_EXTERNAL) {
        //TODO set multiply / divide for external clock
        // float externalFrequency = clock.getFrequency();
        // if(externalFrequency != syncFrequency || syncMultCvInput.update() || force) {
        //     syncFrequency = externalFrequency;
        //     int multInputValue = syncMultCvInput.getIntValue();
        //     float mult = multInputValue >= 0 ? multInputValue+1 : 1/float(-multInputValue);
        //     clock.setFrequency(syncFrequency * mult);
        //     return true;
        // }
    }
    return false;
}

void ClockedController::updateSync() {
    if(syncInput.update() && syncInput.isTriggeredOn()) {
        clock.externalTick(); 
    }
}

void ClockedController::process() {
    if(clock.process()) {
        this->onClock();
    }

    if(syncDivider.tick()) {
        updateSync();
    }
}