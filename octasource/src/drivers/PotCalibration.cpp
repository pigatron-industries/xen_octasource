#include "PotCalibration.h"

#include <Arduino.h>

#define VIRTUAL_MIN -5
#define VIRTUAL_MAX 5

PotCalibration::PotCalibration(float realMin, float realMax) :
    _realMin(realMin),
    _realMax(realMax) {
}

float PotCalibration::getCalibratedValue(float realValue) {
    float realRange = _realMax - _realMin;
    float virtualRange = VIRTUAL_MAX - VIRTUAL_MIN;
    float virtualValue = (((realValue - _realMin) * virtualRange) / realRange) + VIRTUAL_MIN;
    return virtualValue;
}
