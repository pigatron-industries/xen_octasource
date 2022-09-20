#include "MainController.h"
#include "hwconfig.h"
#include "lib/io/SerialUtil.h"
#include "Hardware.h"

#include <Arduino.h>
#include <math.h>


#define TRANSMIT_TIME 10000

MainController* MainController::mainController = nullptr;

MainController::MainController(float sampleRate) : AbstractMainController(Hardware::hw.encoder) {
    MainController::mainController = this;
    this->sampleRate = sampleRate;
}

void MainController::init() {
    Hardware::hw.init();
    AbstractMainController::init();

    this->shortPress = &MainController::incrementMode;
    this->clockWise = &MainController::incrementValue;
    this->antiClockWise = &MainController::decrementValue;
    this->initOnModeSelect = false;

    encoder.getEncoderButton().update();
    if(encoder.getEncoderButton().held()) {
        // TODO load calibration controller
    }
}

void MainController::controllerInit() {
    interruptTimer.end();
    saveMode();

    #if defined(OCTASOURCE_MKII)
        for(int i = 0; i < 16; i++) {
            Hardware::hw.encoderLeds[i]->analogWrite(0);
            Hardware::hw.clearOutputLeds();
        }
    #endif

    Hardware::hw.display.clear();

    if(controllers.getSelected()->getSampleRate() > 0) {
        controllers.getSelected()->init();
    } else {
        controllers.getSelected()->init(sampleRate);
    }

    #if defined(OCTASOURCE_MKII)
        Hardware::hw.encoderLeds[controllers.getSelectedIndex()]->analogWrite(1);
    #endif

    int intervalMicros = 1000000/sampleRate;
    interruptTimer.begin(MainController::interruptHandler, intervalMicros);
}

void MainController::interruptHandler() {
    mainController->process();
}

void MainController::update() {
    RotaryEncoderButton::EncoderEvent event = encoder.getEncoderEvent();
    if(event == RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS) {
        
    }
    doEncoderEvent(event);
    controllers.getSelected()->update();

    #if defined(OCTASOURCE_MKII)
        Hardware::hw.display.update();
    #endif

    #if defined(OCTASOURCE_MKI)
        Hardware::hw.max11300.send();
    #endif

    PROFILE_PRINT
}

void MainController::process() {
    PROFILE_START
    controllers.getSelected()->process();
    #if defined(OCTASOURCE_MKII)
        Hardware::hw.dac8164a.send();
        Hardware::hw.dac8164b.send();
    #endif
    PROFILE_END
}
