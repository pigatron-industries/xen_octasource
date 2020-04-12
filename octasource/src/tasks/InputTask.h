#ifndef InputTask_h
#define InputTask_h

#include <Bounce2.h>

#include <inttypes.h>

#include "../lib/io/AbstractInputTask.h"
#include "../lib/io/Timer.h"
#include "../modules/OctaSource.h"

#define CALIBRATED_POT_SIZE 3


class InputTask : public AbstractInputTask {

public:
    InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource);
    void init();
    void execute();

private:
    OctaSource& _octasource;
    Bounce _modeSwitch;
    GateInput _trigger;
    bool _slaveMode;
    Timer _transmitTimer;

    float rateVoltageToFrequency(float voltage);
    void switchMode();
    void switchSlaveMode();

    void sendData(float frequency);
    float receiveData();

};

#endif
