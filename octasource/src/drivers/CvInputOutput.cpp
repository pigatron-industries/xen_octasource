
#include "CvInputOutput.h"


#define FACTOR (MAX_VALUE / (MAX_VOLTAGE - MIN_VOLTAGE))


CvInputOutput::CvInputOutput(SPIClass* spiClass, uint8_t convertPin, uint8_t selectPin) :
        _spiClass(spiClass),
        _selectPin(selectPin),
        _convertPin(convertPin) {
    _max11300 = new MAX11300(spiClass, convertPin, selectPin);

    _max11300->setPinModeAnalogOut(0, DACNegative5to5);
    _max11300->setPinModeAnalogOut(1, DACNegative5to5);
    _max11300->setPinModeAnalogOut(2, DACNegative5to5);
    _max11300->setPinModeAnalogOut(3, DACNegative5to5);
    _max11300->setPinModeAnalogOut(4, DACNegative5to5);
    _max11300->setPinModeAnalogOut(5, DACNegative5to5);
    _max11300->setPinModeAnalogOut(6, DACNegative5to5);
    _max11300->setPinModeAnalogOut(7, DACNegative5to5);

    _max11300->writeAnalogPin(0, MAX_VALUE/2);
    _max11300->writeAnalogPin(1, MAX_VALUE/2);
    _max11300->writeAnalogPin(2, MAX_VALUE/2);
    _max11300->writeAnalogPin(3, MAX_VALUE/2);
    _max11300->writeAnalogPin(4, MAX_VALUE/2);
    _max11300->writeAnalogPin(5, MAX_VALUE/2);
    _max11300->writeAnalogPin(6, MAX_VALUE/2);
    _max11300->writeAnalogPin(7, MAX_VALUE/2);
}

void CvInputOutput::setValue(uint8_t index, uint16_t value) {
    _max11300->writeAnalogPin(index, value);
}

void CvInputOutput::setVoltage(uint8_t index, float voltage) {
    float absVoltage = voltage - MIN_VOLTAGE;
    float value = absVoltage * FACTOR;
    setValue(index, (uint16_t)value);
}
