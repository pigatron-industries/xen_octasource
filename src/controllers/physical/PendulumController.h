#ifndef PendulumController_h
#define PendulumController_h

#include "Controller.h"
#include "Hardware.h"
#include "controllers/clock/ClockedController.h"
#include "systems/continuous/physical/DoublePendulum.h"
#include "systems/continuous/physical/SpringPendulum.h"
#include <eurorack_dsp.h>

#define SAMPLE_RATE_DIVISOR 2

class PendulumController : public ParameterizedController<1>, public ClockedController {
    public:
        PendulumController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual void onClock();

    private:
        enum Parameter {
            MODE
        };
        enum Mode {
            SPRING_PENDULUM,
            DOUBLE_PENDULUM
        };

        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        LinearInput<AnalogInputSumPinT> param1CvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0.1, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> param2CvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0.1, 0.9);
        #endif

        ExpInput<AnalogInputSumPinT> stiffnessCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, 250, 2.2);

        DoublePendulum doublePendulum;
        SpringPendulum springPendulums[4];
        ClockDivider clockDivider = ClockDivider(SAMPLE_RATE_DIVISOR);
        int8_t clockCounter = 0;

        float amp;
        
        void updateRate();
        void updateAmp();
        void updateParams();
};

#endif
