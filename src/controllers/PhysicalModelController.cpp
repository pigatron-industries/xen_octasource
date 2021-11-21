#include "PhysicalModelController.h"

void PhysicalModelController::init(float sampleRate) {
    Controller::init(sampleRate / SAMPLE_RATE_DIVISOR);
    init();
}

void PhysicalModelController::init() {
    for(int i = 0; i < MODEL_COUNT; i++) {
        models[i]->init(sampleRate);
    }
    Serial.println("Physical Model");
}

void PhysicalModelController::update() {
    updateRate();
    updateAmp();
    updateParams();
}

void PhysicalModelController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(int i = 0; i < MODEL_COUNT; i++) {
            models[i]->setSpeed(rateValue);
        }
    }
}

void PhysicalModelController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void PhysicalModelController::updateParams() {
    if(param1CvInput.update()) {
        ContinuousSystem* model = models[mode.value];
        model->setParam(0, param1CvInput.getValue());
    }
    
    #if defined(OCTASOURCE_MKII)
        if(param2CvInput.update()) {
            ContinuousSystem* model = models[mode.value];
            model->setParam(1, param2CvInput.getValue());
        }
    #endif
}

void PhysicalModelController::process() {
    if(clockDivider.tick()) {
        ContinuousSystem* model = models[mode.value];
        model->process();
        Hardware::hw.cvOutputPins[0]->analogWrite(model->getOutput(X)*amp);
        Hardware::hw.cvOutputPins[1]->analogWrite(model->getOutput(Y)*amp);
    }
}