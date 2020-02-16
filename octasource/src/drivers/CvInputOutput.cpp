
#include "CvInputOutput.h"


#define FACTOR (MAX_VALUE / (MAX_VOLTAGE - MIN_VOLTAGE))


CvInputOutput::CvInputOutput(SPIClass* spiClass, uint8_t convertPin, uint8_t selectPin) :
        _spiClass(spiClass),
        _selectPin(selectPin),
        _convertPin(convertPin) {
    _max11300 = new MAX11300(spiClass, convertPin, selectPin);

    _max11300->setPinModeAnalogOut(12, DACNegative5to5);
    _max11300->setPinModeAnalogOut(13, DACNegative5to5);
    _max11300->setPinModeAnalogOut(14, DACNegative5to5);
    _max11300->setPinModeAnalogOut(15, DACNegative5to5);
    _max11300->setPinModeAnalogOut(16, DACNegative5to5);
    _max11300->setPinModeAnalogOut(17, DACNegative5to5);
    _max11300->setPinModeAnalogOut(18, DACNegative5to5);
    _max11300->setPinModeAnalogOut(19, DACNegative5to5);

    _max11300->writeAnalogPin(12, MAX_VALUE/2);
    _max11300->writeAnalogPin(13, MAX_VALUE/2);
    _max11300->writeAnalogPin(14, MAX_VALUE/2);
    _max11300->writeAnalogPin(15, MAX_VALUE/2);
    _max11300->writeAnalogPin(16, MAX_VALUE/2);
    _max11300->writeAnalogPin(17, MAX_VALUE/2);
    _max11300->writeAnalogPin(18, MAX_VALUE/2);
    _max11300->writeAnalogPin(19, MAX_VALUE/2);

    _max11300->setDACmode(ImmediateUpdate);
}

void CvInputOutput::setValue(uint8_t index, uint16_t value) {
    _max11300->writeAnalogPin(index, value);
}

void CvInputOutput::setVoltage(uint8_t index, float voltage) {
    float absVoltage = voltage - MIN_VOLTAGE;
    float value = absVoltage * FACTOR;
    setValue(index, (uint16_t)value);
}
