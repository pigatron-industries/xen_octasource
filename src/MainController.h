#ifndef MainController_h
#define MainController_h

#include <Bounce2.h>
#include <Encoder.h>

#include <inttypes.h>

#include "lib/io/AbstractInputTask.h"
#include "lib/io/Timer.h"
#include "modules/OctaSource.h"

#define CALIBRATED_POT_SIZE 3


class MainController : public AbstractInputTask {

public:
    MainController(OctaSource& octasource);
    void init();
    void execute();

private:
    OctaSource& _octasource;

    Bounce _modeSwitch;
    Encoder _modeEncoder;
    long _encoderMovement;

    GateInput _trigger;
    bool _slaveMode;
    Timer _transmitTimer;
    Timer _triggerTimer;

    float rateVoltageToFrequency(float voltage);
    void switchMode();
    void switchSlaveMode();
    void printMode();

    void sendData();
    float receiveData();

};

#endif
