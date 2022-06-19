#ifndef BurstController_h
#define BurstController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "lib/DistortedClock.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class Burst {
    public:
        void start(float frequency, int length) {
            this->length = length;
            counter = 0;
            active = true;
            clock.setFrequency(frequency);
            clock.reset();
        }

        bool process() {
            if(active && clock.process()) {
                counter++;
                if(counter >= length) {
                    active = false;
                }
                return true;
            }
            return false;
        }

        int length;
        int counter;
        bool active;
        Clock clock;
};

class BurstController : public Controller {
    public:

        BurstController() : Controller(7) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogGateInput<AnalogInputPinT> triggerInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        LinearInput<AnalogInputSumPinT> burstRateInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 1, 30);
        IntegerInput<AnalogInputSumPinT> waveInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 8);
        IntegerInput<AnalogInputSumPinT> burstLengthInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 1, 30);
        IntegerInput<AnalogInputSumPinT> slopeInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 1, 30);

        AnalogTriggerOutput<AnalogOutputDeviceT> triggerOutputs[8] = {
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[3]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[7])
        };
        
        Burst bursts[8];
        int outputs = 8;
        int nextOutput = 0;

        
        
};

#endif
