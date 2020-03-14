#ifndef InputTask_h
#define InputTask_h

#include <inttypes.h>

#include "../lib/task/AbstractInputTask.h"
#include "../drivers/CvInputOutput.h"
#include "../drivers/PotCalibration.h"
#include "../modules/OctaSource.h"


#define RATE_POT_PIN 0
#define RATE_CV_PIN 1
#define WAVE_POT_PIN 2
#define WAVE_CV_PIN 3
#define LENGTH_POT_PIN 4
#define LENGTH_CV_PIN 5
#define TRIGGER_PIN 6

#define MODE_SWITCH_PIN 0


class InputTask : public AbstractInputTask {

public:
    InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource);
    void init();
    void execute();

private:
    OctaSource& _octasource;

    PotCalibration _ratePotCalibration;
    PotCalibration _amplitudePotCalibration;
    PotCalibration _wavePotCalibration;

    bool _calibrationMode;

    float rateVoltageToFrequency(float voltage);

};

#endif
