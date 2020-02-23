#ifndef InputTask_h
#define InputTask_h

#include <inttypes.h>

#include "../lib/Task.h"
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

class InputTask : public Task {

public:
    InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource);
    void init();
    void execute();

private:
    CvInputOutput& _cvInputOutput;
    OctaSource& _octasource;

    PotCalibration _ratePotCalibration;
    PotCalibration _amplitudePotCalibration;

    float rateVoltageToFrequency(float voltage);

};

#endif
