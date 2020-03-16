#ifndef InputTask_h
#define InputTask_h

#include <Bounce2.h>

#include <inttypes.h>

#include "../lib/io/AbstractInputTask.h"
#include "../modules/OctaSource.h"


#define RATE_POT_PIN 0
#define RATE_CV_PIN 1
#define WAVE_POT_PIN 2
#define WAVE_CV_PIN 3
#define LENGTH_POT_PIN 4
#define LENGTH_CV_PIN 5
#define TRIGGER_PIN 6

#define MODE_SWITCH_PIN 0

#define CALIBRATED_POT_SIZE 3


class InputTask : public AbstractInputTask {

public:
    InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource);
    void init();
    void execute();

private:
    OctaSource& _octasource;
    Bounce _modeSwitch;

    float rateVoltageToFrequency(float voltage);
    void switchMode();

};

#endif
