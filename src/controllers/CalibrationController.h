#ifndef CalibrationController_h
#define CalibrationController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "display/ParameterPage.h"
#include "lib/io/AnalogPinCalibration.h"


#define CALIBRATE_VOLTAGE_MAX 5
#define CALIBRATE_VOLTAGE_MIN -5

class CalibrationController : public ParameterizedController<8> {
    public:
        CalibrationController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual int cycleMode(int amount);
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();

    private:
        IntegerInput<AnalogInputPinT> octaveInput = IntegerInput<AnalogInputPinT>(Hardware::hw.ratePotPin, -5, 5, -4, 4);

        int currentVoltage = 0;

        AnalogPinCalibration calibration;

        ParameterPage page;

        void startCalibrate();
        void saveCalibration();
        void updateOutput();
};

#endif