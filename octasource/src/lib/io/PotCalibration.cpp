#include "PotCalibration.h"

#include <Arduino.h>

PotCalibration::PotCalibration() :
    PotCalibration(-5, 5, -5, 5) {
}

PotCalibration::PotCalibration(float realMin, float realMax, float virtualMin, float virtualMax) :
    _realMin(realMin),
    _realMax(realMax),
    _virtualMin(virtualMin),
    _virtualMax(virtualMax) {
}

float PotCalibration::getCalibratedValue(float realValue) {
    float realRange = _realMax - _realMin;
    float virtualRange = _virtualMax - _virtualMin;
    float virtualValue = (((realValue - _realMin) * virtualRange) / realRange) + _virtualMin;
    return virtualValue;
}
