#include "MainController.h"
#include "hwconfig.h"
#include "Config.h"
#include "lib/io/SerialUtil.h"
#include "Hardware.h"

#include <Arduino.h>
#include <math.h>


#define TRANSMIT_TIME 10000

MainController* MainController::mainController = nullptr;

MainController::MainController(float sampleRate) {
    MainController::mainController = this;
    this->sampleRate = sampleRate;
}

void MainController::registerController(Controller& controller) {
    controllers.addController(controller);
}

void MainController::init() {
    Hardware::hw.encoderButton.update();
    if(Hardware::hw.encoderButton.held()) {
        doCalibration();
    }

    Config::load();
    loadCalibration();

    controllers.setActiveController(Config::data.mode.controllerIndex);
    controllers.getActiveController()->setMode(Config::data.mode.controllerMode);
    controllerInit();
}

void MainController::controllerInit() {
    interruptTimer.end();

    #if defined(OCTASOURCE_MKII)
        Hardware::hw.encoderLeds[Config::data.mode.controllerIndex]->analogWrite(0);
    #endif

    Config::data.mode.controllerIndex = controllers.getActiveControllerIndex();
    Config::saveMode();

    if(controllers.getActiveController()->getSampleRate() > 0) {
        controllers.getActiveController()->init();
    } else {
        controllers.getActiveController()->init(sampleRate);
    }

    #if defined(OCTASOURCE_MKII)
        Hardware::hw.encoderLeds[Config::data.mode.controllerIndex]->analogWrite(1);
    #endif

    int intervalMicros = 1000000/sampleRate;
    interruptTimer.begin(MainController::interruptHandler, intervalMicros);
}

void MainController::interruptHandler() {
    mainController->process();
}

void MainController::update() {
    Hardware::hw.encoderButton.update();
    if(Hardware::hw.encoder.update()) {
        if(Hardware::hw.encoderButton.held()) {
            //change controller when button held down
            if(Hardware::hw.encoder.getMovement() != 0) {
                cycled = true;
                controllers.cycle(Hardware::hw.encoder.getMovement());
                controllerInit();
            } 
        } else {
            //change controller mode
            if(Hardware::hw.encoder.getMovement() != 0) {
                Config::data.mode.controllerMode = controllers.getActiveController()->cycleMode(Hardware::hw.encoder.getMovement());
                controllers.getActiveController()->init();
                Config::saveMode();
                Serial.print("Mode: ");
                Serial.println(Config::data.mode.controllerMode);
            }
        }
    }
    if(Hardware::hw.encoderButton.released()) {
        Serial.print("Released");
        if(!cycled) {
            controllerInit();
        }
        cycled = false;
    }

    //TODO long press switches to slave mode
    controllers.getActiveController()->update();

    #if defined(OCTASOURCE_MKI)
        Hardware::hw.max11300.send();
    #endif
}

void MainController::process() {
    controllers.getActiveController()->process();
    #if defined(OCTASOURCE_MKII)
        Hardware::hw.dac8164a.send();
        Hardware::hw.dac8164b.send();
    #endif
}


void MainController::doCalibration() {
    #if defined(OCTASOURCE_MKI)
        Serial.println("Calibration mode started.");
        Serial.println("Release mode switch...");
        displayVoltage(0);
        Hardware::hw.encoderButton.waitForPressAndRelease();

        Serial.println("Turn all pots left, then press mode switch...");
        Serial.println();
        displayVoltage(-5);
        Hardware::hw.encoderButton.waitForPressAndRelease();

        Config::data.calibration[0].min = Hardware::hw.rateCvPin.binaryRead();
        Config::data.calibration[1].min = Hardware::hw.waveCvPin.binaryRead();
        Config::data.calibration[2].min = Hardware::hw.ampCvPin.binaryRead();

        Serial.println("Turn all pots right, then press mode switch...");
        Serial.println();
        displayVoltage(5);
        Hardware::hw.encoderButton.waitForPressAndRelease();

        Config::data.calibration[0].max = Hardware::hw.rateCvPin.binaryRead();
        Config::data.calibration[1].max = Hardware::hw.waveCvPin.binaryRead();
        Config::data.calibration[2].max = Hardware::hw.ampCvPin.binaryRead();

        Config::saveCalibration();
    #endif
}

void MainController::loadCalibration() {
    #if defined(OCTASOURCE_MKI)
        Hardware::hw.rateCvPin.setBinaryRange(Config::data.calibration[0].min, Config::data.calibration[0].max);
        Hardware::hw.waveCvPin.setBinaryRange(Config::data.calibration[1].min, Config::data.calibration[1].max);
        Hardware::hw.ampCvPin.setBinaryRange(Config::data.calibration[2].min, Config::data.calibration[2].max);
    #endif
}

void MainController::displayVoltage(float voltage) {
    // TODO put back in once mkii cvOutputPins defined
    #if defined(OCTASOURCE_MKI)
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            Hardware::hw.cvOutputPins[i]->analogWrite(voltage);
        }
    #endif
}