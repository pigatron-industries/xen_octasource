
#include "CvOutput.h"


#define FACTOR (MAX_VALUE / (MAX_VOLTAGE - MIN_VOLTAGE))


CvOutput::CvOutput(SPIClass* spiClass, uint8_t convertPin, uint8_t* selectPins, uint8_t devices) :
        _spiClass(spiClass),
        _selectPins(selectPins),
        _convertPin(convertPin),
        _devices(devices) {
    _max11300 = new MAX11300*[devices];
    for(int i = 0; i < devices; i++) {
        //pinMode(selectPins[i], OUTPUT);
        _max11300[i] = new MAX11300(spiClass, convertPin, selectPins[i]);
        for(int j = 0; j < 20; j++) {
            _max11300[i]->setPinModeAnalogOut(j, DACNegative5to5);
            _max11300[0]->writeAnalogPin(j, MAX_VALUE/2);
        }
    }
}

void CvOutput::setValue(uint8_t index, uint16_t value) {
    uint8_t device = index / 20;
    uint8_t devicePin = index % 20;
    Serial.println("cvOutput::setValue");
    Serial.println(device);
    Serial.println(devicePin);
    _max11300[device]->writeAnalogPin(devicePin, value);
}

void CvOutput::setVoltage(uint8_t index, float voltage) {
    Serial.println("cvOutput::setVoltage");
    Serial.println(index);
    Serial.println(voltage);
    float absVoltage = voltage - MIN_VOLTAGE;
    float value = absVoltage * FACTOR;
    setValue(index, (uint16_t)value);
}
