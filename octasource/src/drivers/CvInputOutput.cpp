
#include "CvInputOutput.h"


#define FACTOR (MAX_VALUE / (MAX_VOLTAGE - MIN_VOLTAGE))


CvInputOutput::CvInputOutput(SPIClass* spiClass, uint8_t convertPin, uint8_t selectPin) :
        _spiClass(spiClass),
        _selectPin(selectPin),
        _convertPin(convertPin) {
    _max11300 = new MAX11300(spiClass, convertPin, selectPin);
    _max11300->setDACmode(ImmediateUpdate);
    _max11300->setADCmode(ContinuousSweep);
}

void CvInputOutput::setPinModeAnalogOut(uint8_t index) {
    _max11300->setPinModeAnalogOut(index, DACNegative5to5);
    _max11300->writeAnalogPin(index, MAX_VALUE/2);
}

void CvInputOutput::setPinModeAnalogIn(uint8_t index) {
    _max11300->setPinModeAnalogIn(index, ADCNegative5to5);
}

void CvInputOutput::setValue(uint8_t index, uint16_t value) {
    _max11300->writeAnalogPin(index, value);
}

uint16_t CvInputOutput::getValue(uint8_t index) {
    return _max11300->readAnalogPin(index);
}

void CvInputOutput::setVoltage(uint8_t index, float voltage) {
    float absVoltage = voltage - MIN_VOLTAGE;
    float value = absVoltage * FACTOR;
    setValue(index, (uint16_t)value);
}

float CvInputOutput::getVoltage(uint8_t index) {
    uint16_t value = getValue(index);
    float absVoltage = float(value) / FACTOR;
    float voltage = absVoltage + MIN_VOLTAGE;
    return voltage;
}
