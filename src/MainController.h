#ifndef MainController_h
#define MainController_h

#include <eurorack.h>
#include <inttypes.h>

#include "Controller.h"
#include "Hardware.h"


class MainController : AbstractMainController<Controller, 16> {

public:
    MainController(float sampleRate);
    void init();
    void update();
    void process();

    void registerController(Controller& controller);

private:
    float sampleRate;

    void controllerInit();
    void doCalibration();
    void loadCalibration();
    void displayVoltage(float voltage);

    IntervalTimer interruptTimer;
    static MainController* mainController;
    static void interruptHandler();
};

#endif
