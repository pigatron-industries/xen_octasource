#include "AbstractInputTask.h"
#include "../../hwconfig.h"
#include "../../Config.h"

#include <Arduino.h>

AbstractInputTask::AbstractInputTask() {
    _calibrationMode = false;
    _potCalibrationSize = 0;
    _calibrationMode = 0;
}

void AbstractInputTask::setPotCalibration(uint8_t modeSwitchPin, uint8_t potCalibrationSize, uint8_t displayLedPin) {
    _modeSwitchPin = modeSwitchPin;
    _potCalibrationSize = potCalibrationSize;
    _displayLedPin = displayLedPin;
    _potCalibration = new PotCalibration[_potCalibrationSize];
}

void AbstractInputTask::init() {
    Task::init();
    pinMode(_modeSwitchPin, INPUT_PULLUP);
    digitalWrite(_modeSwitchPin, HIGH);

    float* realMin = Config::instance.getCalibrationRealMin();
    float* realMax = Config::instance.getCalibrationRealMax();
    for(int i = 0; i < _potCalibrationSize; i++) {
        _potCalibration[i].setRealMin(realMin[i]);
        _potCalibration[i].setRealMax(realMax[i]);
    }

    // Check for calibration mode
    delay(100);
    if(digitalRead(_modeSwitchPin) == LOW) {
        doCalibrationSequence();
    }

}

float AbstractInputTask::getValue(uint8_t pin) {
    return Hardware::hw.cvPins[pin].readVoltage();
}

float AbstractInputTask::getCalibratedValue(uint8_t pin) {
    float voltage = Hardware::hw.cvPins[pin].readVoltage();

    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        if(_potCalibration[i].getPin() == pin) {
            return _potCalibration[i].getCalibratedValue(voltage);
        }
    }

    return voltage;
}

void AbstractInputTask::doCalibrationSequence() {
    Hardware::hw.max11300.setPinModeAnalogOut(_displayLedPin, DACNegative5to5);
    Hardware::hw.cvPins[_displayLedPin].writeVoltage(5.0);
    Serial.println("Calibration mode started.");
    Serial.println("Release mode switch...");

    while (digitalRead(_modeSwitchPin) == LOW) {
    }

    Hardware::hw.cvPins[_displayLedPin].writeVoltage(-5.0);
    Serial.println("Turn all pots left, then press mode switch...");
    delay(100);
    while (digitalRead(_modeSwitchPin) == HIGH) {}
    delay(100);
    while (digitalRead(_modeSwitchPin) == LOW) {}

    // Read in min voltages for each pot
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        float voltage = Hardware::hw.cvPins[_potCalibration[i].getPin()].readVoltage();
        _potCalibration[i].setRealMin(voltage);
    }

    Hardware::hw.cvPins[_displayLedPin].writeVoltage(5.0);
    Serial.println("Turn all pots right, then press mode switch...");
    delay(100);
    while (digitalRead(_modeSwitchPin) == HIGH) {}
    delay(100);
    while (digitalRead(_modeSwitchPin) == LOW) {}

    // Read in max voltages for each pot
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        float voltage = Hardware::hw.cvPins[_potCalibration[i].getPin()].readVoltage();
        _potCalibration[i].setRealMax(voltage);
        Serial.println(voltage);
    }

    Config::instance.savePotCalibration(_potCalibration, _potCalibrationSize);
    Serial.println("Calibration finished.");
}
