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
    
    Config::data.mode.controllerIndex = controllers.getActiveControllerIndex();
    Config::saveMode();

    controllers.getActiveController()->init(sampleRate);

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
                controllers.cycle(Hardware::hw.encoder.getMovement());
                controllerInit();
            } 
        } else {
            //change controller mode
            if(Hardware::hw.encoder.getMovement() != 0) {
                Config::data.mode.controllerMode = controllers.getActiveController()->cycleMode(Hardware::hw.encoder.getMovement());
                controllers.getActiveController()->init();
                Config::saveMode();
            }
        }
    }

    //TODO long press switches to slave mode
    controllers.getActiveController()->update();
}

void MainController::process() {
    controllers.getActiveController()->process();
}


void MainController::doCalibration() {
    Serial.println("Calibration mode started.");
    Serial.println("Release mode switch...");
    displayVoltage(0);
    Hardware::hw.encoderButton.waitForPressAndRelease();

    Serial.println("Turn all pots left, then press mode switch...");
    Serial.println();
    displayVoltage(-5);
    Hardware::hw.encoderButton.waitForPressAndRelease();

    Config::data.calibration[0].min = Hardware::hw.ratePotPin.read();
    Config::data.calibration[1].min = Hardware::hw.wavePotPin.read();
    Config::data.calibration[2].min = Hardware::hw.ampPotPin.read();

    Serial.println("Turn all pots right, then press mode switch...");
    Serial.println();
    displayVoltage(5);
    Hardware::hw.encoderButton.waitForPressAndRelease();

    Config::data.calibration[0].max = Hardware::hw.ratePotPin.read();
    Config::data.calibration[1].max = Hardware::hw.wavePotPin.read();
    Config::data.calibration[2].max = Hardware::hw.ampPotPin.read();

    Config::saveCalibration();
}

void MainController::loadCalibration() {
    Hardware::hw.ratePotPin.setInputRange(Config::data.calibration[0].min, Config::data.calibration[0].max);
    Hardware::hw.wavePotPin.setInputRange(Config::data.calibration[1].min, Config::data.calibration[1].max);
    Hardware::hw.ampPotPin.setInputRange(Config::data.calibration[2].min, Config::data.calibration[2].max);
}

void MainController::displayVoltage(float voltage) {
    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        Hardware::hw.cvOutputPins[i].writeVoltage(voltage);
    }
}