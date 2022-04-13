#include "PendulumController.h"

void PendulumController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void PendulumController::init() {
    Serial.println("Pendulum");
    Hardware::hw.display.text("PENDULUM");
    doublePendulum.init(sampleRate / SAMPLE_RATE_DIVISOR);
    for(SpringPendulum& springPendulum : springPendulums) {
        springPendulum.init(sampleRate / SAMPLE_RATE_DIVISOR);
    }

    switch(mode.value) {
        case Mode::SPRING_PENDULUM:
            Hardware::hw.display.text("SPRING", Display::TEXTLINE_2);
            springPendulums[0].setInitialConditions(Vector<2>(-2.5, 0), Vector<2>(0, 0));
            springPendulums[0].setOffset(Vector<2>(0, 2.5));
            springPendulums[0].setScale(Vector<2>(1.5, 1.5) * 1);

            springPendulums[1].setInitialConditions(Vector<2>(0, -3), Vector<2>(0.2, 4));
            springPendulums[1].setOffset(Vector<2>(0, 3.3));
            springPendulums[1].setScale(Vector<2>(1, 2) * 2);

            springPendulums[2].setInitialConditions(Vector<2>(0, -3), Vector<2>(0.3, 6));
            springPendulums[2].setOffset(Vector<2>(0, 3.3));
            springPendulums[2].setScale(Vector<2>(1, 2) * 1);

            springPendulums[3].setInitialConditions(Vector<2>(0, -3), Vector<2>(0.4, 8));
            springPendulums[3].setOffset(Vector<2>(0, 3.3));
            springPendulums[3].setScale(Vector<2>(1, 2) * 1);
            break;
        case Mode::DOUBLE_PENDULUM:
            Hardware::hw.display.text("DOUBLE", Display::TEXTLINE_2);
            break;
    }
}

void PendulumController::update() {
    updateRate();
    updateAmp();
    updateParams();
    Hardware::hw.updateOutputLeds();
}

void PendulumController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        doublePendulum.setSpeed(rateValue);
        for(SpringPendulum& springPendulum : springPendulums) {
            springPendulum.setSpeed(rateValue);
        }
    }
}

void PendulumController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void PendulumController::updateParams() {
    if(stiffnessCvInput.update()) {
        float stiffnesssCvValue = stiffnessCvInput.getValue();
        for(SpringPendulum& springPendulum : springPendulums) {
            springPendulum.setSpringStiffness(stiffnesssCvValue);
        }
    }

    if(param1CvInput.update()) {
        doublePendulum.setParam(0, param1CvInput.getValue());
    }
    
    #if defined(OCTASOURCE_MKII)
        if(param2CvInput.update()) {
            doublePendulum.setParam(1, param2CvInput.getValue());
        }
    #endif
}

void PendulumController::process() {
    if(clockDivider.tick()) {
        switch(mode.value) {
        case Mode::SPRING_PENDULUM:
            for(SpringPendulum& springPendulum : springPendulums) {
                springPendulum.process();
            }
            Hardware::hw.cvOutputPins[0]->analogWrite(springPendulums[0].getOutput(X)*amp);
            Hardware::hw.cvOutputPins[1]->analogWrite(springPendulums[0].getOutput(Y)*amp);
            Hardware::hw.cvOutputPins[2]->analogWrite(springPendulums[1].getOutput(X)*amp);
            Hardware::hw.cvOutputPins[3]->analogWrite(springPendulums[1].getOutput(Y)*amp);
            Hardware::hw.cvOutputPins[4]->analogWrite(springPendulums[2].getOutput(X)*amp);
            Hardware::hw.cvOutputPins[5]->analogWrite(springPendulums[2].getOutput(Y)*amp);
            Hardware::hw.cvOutputPins[6]->analogWrite(springPendulums[3].getOutput(X)*amp);
            Hardware::hw.cvOutputPins[7]->analogWrite(springPendulums[3].getOutput(Y)*amp);
            break;
        case Mode::DOUBLE_PENDULUM:
            doublePendulum.process();
            Hardware::hw.cvOutputPins[0]->analogWrite(doublePendulum.getOutput(X)*amp);
            Hardware::hw.cvOutputPins[1]->analogWrite(doublePendulum.getOutput(Y)*amp);
            Hardware::hw.cvOutputPins[2]->analogWrite(doublePendulum.getOutput(Z)*amp);
            Hardware::hw.cvOutputPins[3]->analogWrite(doublePendulum.getOutput(W)*amp);
            break;
        }
    }
}