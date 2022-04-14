#include "DelayController.h"

void DelayController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        delays[i].init(sampleRate/SAMPLERATE_DIVIDER, DELAYBUFFER_SIZE, Hardware::hw.memPool);
        delays[i].setDelay((float)DELAYBUFFER_SIZE/8*(i+1));
        filters[i].init(sampleRate);
        filters[i].setResonance(0);
        filters[i].setFrequency(1/((i+1)*0.1));
    }
    init();
}

void DelayController::init() {
    Serial.println("Delay");
    Hardware::hw.display.text("DELAY");
    switch(mode.value) {
        case Mode::DELAY:
            Hardware::hw.display.text("DELAY", Display::TEXTLINE_2);
            break;
        case Mode::SLEW:
            Hardware::hw.display.text("SLEW", Display::TEXTLINE_2);
            break;
    }
}

void DelayController::update() {
    if(timeCvInput.update()) {
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            float time = timeCvInput.getValue();
            filters[i].setFrequency(1/((i+1)*time));
            delays[i].setDelay((float)DELAYBUFFER_SIZE/OUTPUTS*(i+1)*time);
        }
    }

    // value = Hardware::hw.syncCvPin.analogRead();
    // for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
    //     delays[i].write(value);
    // }

    Hardware::hw.updateOutputLeds();
}

void DelayController::process() {
     bool tick = clockDivider.tick();
     if(tick) {
        value = Hardware::hw.syncCvPin.analogRead();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            delays[i].write(value);
        }
     }

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        filters[i].process(value);
    }

    switch(mode.value) {
        case Mode::DELAY:
            //if(tick) {
                for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                    Hardware::hw.cvOutputPins[i]->analogWrite(delays[i].read());
                }
            //}
            break;
        case Mode::SLEW:
            for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
                Hardware::hw.cvOutputPins[i]->analogWrite(filters[i].low());
            }
            break;
    }
}
