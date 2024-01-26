#include "BurstController.h"

void BurstController::init(float sampleRate) {
    configParam(Parameter::BURST_OUTPUTS, 0, 8);
    configParam(Parameter::BURST_SHAPE, 0, shapes.getSize()-1);

    for(int i = 0; i < outputs; i++) {
        bursts[i].init(sampleRate);
    }
    externalClock.init(sampleRate);

    parameters[Parameter::BURST_OUTPUTS].last = OUTPUT_CV_COUNT-1;
    parameters[Parameter::BURST_SHAPE].last = shapes.getSize()-1;

    std::get<0>(shapes.getObjects()).setWidth(0.5);
    std::get<1>(shapes.getObjects()).setPeakPosition(0.5);
    std::get<2>(shapes.getObjects()).setPeakPosition(0);
    std::get<3>(shapes.getObjects()).setPeakPosition(1);

    shapes.select(0);

    init();
}

void BurstController::init() {
    Serial.println("Burst");
    Hardware::hw.display.textLine("BURST");

    outputs = parameters[Parameter::BURST_OUTPUTS].value + 1;

    page.setLabel(1, "OUT:");
    page.setLabel(2, "SHP:");
    page.setLabel(3, "LEN:");
    page.setValue(1, outputs);
    page.setValue(2, parameters[Parameter::BURST_SHAPE].value);
    page.selectLine(parameters.getSelectedIndex()+1);
}

int BurstController::cycleParameter(int amount) {
    parameters.cycle(amount);
    page.selectLine(parameters.getSelectedIndex()+1);
    return parameters.getSelectedIndex(); 
}

void BurstController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::BURST_OUTPUTS:
            outputs = parameters[Parameter::BURST_OUTPUTS].value + 1;
            page.setValue(1, outputs);
            break;
        case Parameter::BURST_SHAPE:
            shapes.select(parameters[Parameter::BURST_SHAPE].value);
            page.setValue(2, parameters[Parameter::BURST_SHAPE].value);
            break;
    }
    save();
}

void BurstController::update() {
    if(syncInput.update() && syncInput.isTriggeredOn()) {
        externalClock.externalTick();
        if(!sync && externalClock.getState() == InternalExternalClock::State::CLK_EXTERNAL) {
            Hardware::hw.display.textLine("SYNC", OLEDDisplay::TEXTLINE_1, DISPLAY_FONT_WIDTH*9);
            sync = true;
        }
    }

    if(sync && externalClock.getState() == InternalExternalClock::State::CLK_INTERNAL) {
        sync = false;
        Hardware::hw.display.textLine("    ", OLEDDisplay::TEXTLINE_1, DISPLAY_FONT_WIDTH*9);
    }

    if(burstLengthInput.update()) {
        burstLength = burstLengthInput.getValue();
        page.setValue(3, burstLength);
    }

    if(triggerInput.update() && triggerInput.isTriggeredOn()) {
        slopeInput.update();
        float burstRate;
        if(sync) {
            burstRateMultInput.update();
            int burstRateMult = burstRateMultInput.getIntValue();
            if(burstRateMult >= 0) {
                burstRate = externalClock.getFrequency() * (burstRateMult+1);
            } else {
                burstRate = externalClock.getFrequency() / fabsf(burstRateMult);
            }
        } else {
            burstRateInput.update();
            burstRate = burstRateInput.getValue();
        }
        bursts[nextOutput].start(burstRate, burstLength, slopeInput.getValue());
        nextOutput++;
        if(nextOutput >= outputs) {
            nextOutput = 0;
        }
    }

    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void BurstController::process() {
    externalClock.process();
    for(int i = 0; i < outputs; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(bursts[i].process() * 5);
    }
}
