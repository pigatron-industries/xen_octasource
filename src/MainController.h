#ifndef MainController_h
#define MainController_h

#include <eurorack.h>
#include <inttypes.h>

#include "Controller.h"
#include "Hardware.h"


class MainController {

public:
    MainController(float sampleRate);
    void init();
    void update();
    void process();

    void registerController(Controller& controller);

private:
    float sampleRate;
    ControllerList<Controller, 16> controllers;
    bool cycled = false;

    void controllerInit();
    void doCalibration();
    void loadCalibration();
    void displayVoltage(float voltage);

    IntervalTimer interruptTimer;
    static MainController* mainController;
    static void interruptHandler();
};

#endif
