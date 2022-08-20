#include "CalibrationController.h"

void CalibrationController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void CalibrationController::init() {
    Serial.println("Calibration");
    Hardware::hw.display.textLine("CALIBRATION");

    page.setLabel(1, "OUTP:");
    page.setValue(1, parameters.getSelectedIndex());
    page.setLabel(2, "VOLT:");
    page.setLabel(3, "OFST:");
    startCalibrate();
}

int CalibrationController::cycleMode(int amount) {
    saveCalibration();
    parameters.cycle(amount);
    startCalibrate();
    return parameters.getSelectedIndex();
}

void CalibrationController::cycleValue(int amount) {
    if(currentVoltage == 0) {
        calibration.offset(-amount);
    } else {
        calibration.scale(-amount);
    }
    updateOutput();
}

void CalibrationController::update() {
    if(octaveInput.update()) {
        currentVoltage = octaveInput.getIntValue();
        updateOutput();
    }

    Hardware::hw.updateOutputLeds();
}

void CalibrationController::startCalibrate() {
    int output = parameters.getSelectedIndex();
    calibration.calibratePin(Hardware::hw.cvOutputPins[output]);

    updateOutput();

    page.setValue(1, output);
}

void CalibrationController::saveCalibration() {
    int output = parameters.getSelectedIndex();
    Hardware::hw.cvOutputPins[output]->saveCalibration();
}

void CalibrationController::updateOutput() {
    int output = parameters.getSelectedIndex();
    uint16_t binaryValue = calibration.convertReverse(currentVoltage);
    Hardware::hw.cvOutputPins[output]->analogWrite(currentVoltage);

    page.setValue(2, currentVoltage);
    page.setValue(3, binaryValue);
}

void CalibrationController::process() {

}