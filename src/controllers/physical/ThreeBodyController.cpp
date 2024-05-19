#include "ThreeBodyController.h"
#include "debug/debugfunctions.h"

void ThreeBodyController::init(float sampleRate) {
    Controller::init(sampleRate);
    ClockedController::init(sampleRate);
    configParam(Parameter::MODE, 0, Mode::CHAOTIC3);
    configParam(Parameter::OUTPUT_TYPE, 0, OutputType::DISTANCE);
    display.init();
    display.focusType();
    init();
}

void ThreeBodyController::init() {
    threeBody.init(sampleRate);
    Serial.println("Three Body");
    // Hardware::hw.display.textLine("THREE BODY");
    //printBodies();


    /**
     * Initial conditions taken from 
     * https://observablehq.com/@rreusser/periodic-planar-three-body-orbits
     * http://three-body.ipb.ac.rs/
     * To increase size without affecting pattern, multiply mass and initial position by the same amount
     */

    Array<Body, 3> bodies;
    switch(parameters[Parameter::MODE].value) {
        case Mode::STABLE1: // Massive star with opposite planets of equal mass
            display.setType("STABLE ORBIT");
            // Hardware::hw.display.textLine("STABLE ORBIT", OLEDDisplay::TEXTLINE_2);
            bodies[0].setMass(100);
            bodies[0].setPosition(Vector<2>(0, 0));
            bodies[0].setVelocity(Vector<2>(0, 0));
            bodies[1].setMass(1);
            bodies[1].setPosition(Vector<2>(0, 4));
            bodies[1].setVelocity(Vector<2>(5, 0));
            bodies[2].setMass(1);
            bodies[2].setPosition(Vector<2>(0, -3));
            bodies[2].setVelocity(Vector<2>(-4, 0));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::FIGURE8_STABLE_V1A: // Figure 8 Stable
            display.setType("FIGURE8 STABLE");
            // Hardware::hw.display.textLine("FIGURE8 STABLE", OLEDDisplay::TEXTLINE_2);
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.347111, 0.532728));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::FIGURE8_CHAOTIC_V17A: // Figure 8 Chaotic
            // Hardware::hw.display.textLine("FIGURE8 CHAOTIC", OLEDDisplay::TEXTLINE_2);
            display.setType("FIGURE8 CHAOTIC");
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.210832, 0.51741));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::BROUCKE_A2: // Broucke Stable
            // Hardware::hw.display.textLine("BROUCKE STABLE", OLEDDisplay::TEXTLINE_2);
            display.setType("BROUCKE STABLE");
            bodies[0].setMass(4);
            bodies[0].setPosition(Vector<2>(0.336130095, 0) * 4);
            bodies[0].setVelocity(Vector<2>(0, 1.532431537));
            bodies[1].setMass(4);
            bodies[1].setPosition(Vector<2>(0.7699893804, 0) * 4);
            bodies[1].setVelocity(Vector<2>(0, -0.6287350978));
            bodies[2].setMass(4);
            bodies[2].setPosition(Vector<2>(-1.1061194753, 0) * 4);
            bodies[2].setVelocity(Vector<2>(0, -0.9036964391));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::BROUCKE_ASYMETRICAL: // Stable state with 3 equal masses, found accidentally from CHAOTIC_BOUNCE1
            // Hardware::hw.display.textLine("BROUCKE ASYM", OLEDDisplay::TEXTLINE_2);
            display.setType("BROUCKE ASYM");
            bodies[0].setMass(4);
            bodies[0].setPosition(Vector<2>(-2.855484,-0.099324));
            bodies[0].setVelocity(Vector<2>(-0.14822,-0.47005));
            bodies[1].setMass(4);
            bodies[1].setPosition(Vector<2>(-1.785072,0.406224));
            bodies[1].setVelocity(Vector<2>(-1.47620,1.02377));
            bodies[2].setMass(4);
            bodies[2].setPosition(Vector<2>(4.640556,-0.306904));
            bodies[2].setVelocity(Vector<2>(-0.20557,1.39997));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::NONE);
            break;
        case Mode::CHAOTIC1_BOUNCE:
            // Hardware::hw.display.textLine("CHAOTIC BOUNCE", OLEDDisplay::TEXTLINE_2);
            display.setType("CHAOTIC BOUNCE");
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.201678, 0.409896));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::BOUNCE);
            break;
        case Mode::CHAOTIC1_ANTIGRAV:
            // Hardware::hw.display.textLine("CHAOTIC ANTIGRAV", OLEDDisplay::TEXTLINE_2);
            display.setType("CHAOTIC ANTIGRAV");
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.201678, 0.409896));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::ANTIGRAV);
            break;
        case Mode::CHAOTIC1_WRAP:
            // Hardware::hw.display.textLine("CHAOTIC WRAP", OLEDDisplay::TEXTLINE_2);
            display.setType("CHAOTIC WRAP");
            bodies = ThreeBody::initEqualInlineSystem(4, Vector<2>(0.201678, 0.409896));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::WRAP);
            break;
        case Mode::CHAOTIC2: // Large mass with 2 small masses
            // Hardware::hw.display.textLine("CHAOTIC 1L2S", OLEDDisplay::TEXTLINE_2);
            display.setType("CHAOTIC 1L2S");
            bodies[0].setMass(100);
            bodies[0].setPosition(Vector<2>(0, 0));
            bodies[0].setVelocity(Vector<2>(0, 0));
            bodies[1].setMass(1);
            bodies[1].setPosition(Vector<2>(0, 4));
            bodies[1].setVelocity(Vector<2>(5, 0));
            bodies[2].setMass(1);
            bodies[2].setPosition(Vector<2>(0, -4));
            bodies[2].setVelocity(Vector<2>(-4.9, 0));
            threeBody.setDriftCorrection(true);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::ANTIGRAV);
            break;
        case Mode::CHAOTIC3: // All different masses
            // Hardware::hw.display.textLine("CHAOTIC 1L1M1S", OLEDDisplay::TEXTLINE_2);
            display.setType("CHAOTIC 1L1M1S");
            bodies[0].setMass(100);
            bodies[0].setPosition(Vector<2>(0, 0));
            bodies[0].setVelocity(Vector<2>(0, 0));
            bodies[1].setMass(10);
            bodies[1].setPosition(Vector<2>(0, 4));
            bodies[1].setVelocity(Vector<2>(5, 0));
            bodies[2].setMass(1);
            bodies[2].setPosition(Vector<2>(0, -4));
            bodies[2].setVelocity(Vector<2>(-5, 0));
            threeBody.setDriftCorrection(false);
            threeBody.setEdgeMode(ThreeBody::EdgeMode::ANTIGRAV);
            break;
    }
    
    threeBody.setBodies(bodies);
    setOutputType((OutputType)parameters[Parameter::OUTPUT_TYPE].value);
    display.render();
}

int ThreeBodyController::cycleParameter(int amount) { 
    parameters.cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::MODE:
            display.focusType();
            break;
        case Parameter::OUTPUT_TYPE:
            display.focusOutput();
            break;
    }
    return parameters.getSelectedIndex(); 
}

void ThreeBodyController::cycleValue(int amount) { 
    uint8_t parameter = parameters.getSelectedIndex();
    uint8_t value = parameters.getSelected().cycle(amount);

    switch (parameter) {
        case Parameter::MODE:
            init();
            break;
        case Parameter::OUTPUT_TYPE:
            setOutputType((OutputType)value);
            break;
    }
    save();
}

void ThreeBodyController::setOutputType(OutputType outputType) {
    switch (outputType) {
        case OutputType::XY:
            display.setOutput("XY");
            break;
        case OutputType::DISTANCE:
            display.setOutput("DISTANCE");
            break;
    }
}

void ThreeBodyController::update() {
    clock.setFrequency(200);
    updateRate();
    updateAmp();
    updateSize();
    updateDamp();
    Hardware::hw.updateOutputLeds();
}

void ThreeBodyController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        threeBody.setSpeed(rateValue);
    }
}

void ThreeBodyController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
        totalGain = amp * size;
    }
}

void ThreeBodyController::updateSize() {
    if(sizeCvInput.update()) {
        size = sizeCvInput.getValue();
        threeBody.setLimit(5/size);
        totalGain = amp * size;
    }
}

void ThreeBodyController::updateDamp() {
    #if defined(OCTASOURCE_MKII)
        if(dampCvInput.update()) {
            threeBody.setDamp(dampCvInput.getValue());
        }
    #endif
}

void ThreeBodyController::process() {
    threeBody.process();

    switch (parameters[Parameter::OUTPUT_TYPE].value) {
        case OutputType::XY:
            Hardware::hw.cvOutputPins[0]->analogWrite(threeBody.getOutput(0)*totalGain);
            Hardware::hw.cvOutputPins[1]->analogWrite(threeBody.getOutput(1)*totalGain);
            Hardware::hw.cvOutputPins[2]->analogWrite(threeBody.getOutput(2)*totalGain);
            Hardware::hw.cvOutputPins[3]->analogWrite(threeBody.getOutput(3)*totalGain);
            Hardware::hw.cvOutputPins[4]->analogWrite(threeBody.getOutput(4)*totalGain);
            Hardware::hw.cvOutputPins[5]->analogWrite(threeBody.getOutput(5)*totalGain);
            break;
        case OutputType::DISTANCE:
            Array<Body, BODIES>& bodies = threeBody.getBodies();
            for(int i = 0; i < 3; i++) {
                Vector<2> diff = bodies[i].getPosition() - bodies[(i+1)%3].getPosition();
                float distance = diff.length();
                bool direction = distance < distances[i];
                if(direction != directions[i]) {
                    directions[i] = direction;
                    triggerOutputs[i].trigger();
                }
                distances[i] = diff.length();
                triggerOutputs[i].update();
                Hardware::hw.cvOutputPins[i]->analogWrite(distances[i]*totalGain*0.5);
            }
            break;
    }

    ClockedController::process();
    Hardware::hw.cvOutputPins[6]->analogWrite(threeBody.getOutput(oscBody*2)*totalGain);
    Hardware::hw.cvOutputPins[7]->analogWrite(threeBody.getOutput(oscBody*2+1)*totalGain);
}

void ThreeBodyController::onClock() {
    oscBody++;
    oscBody %= 3;
}

void ThreeBodyController::printBodies() {
    Serial.println("State:");
    printBody(threeBody.getBodies()[0]);
    printBody(threeBody.getBodies()[1]);
    printBody(threeBody.getBodies()[2]);
    Serial.println();
}

void ThreeBodyController::printBody(Body body) {
    print(body.getPosition());
    print(body.getVelocity());
}