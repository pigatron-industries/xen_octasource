#ifndef EnvelopeController_h
#define EnvelopeController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define ATTRACTOR_COUNT 12

class EnvelopeController : public ParameterizedController<1> {
    public:
        EnvelopeController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        enum Parameter {
            MODE
        };
        enum Mode {
            LATCHED,
            GATED
        };

        Envelope<WaveSequence<2, Line>> envelopeShape;

        EnvelopePlayer<Envelope<WaveSequence<2, Line>>&> envelopes[OUTPUT_CV_COUNT] = {
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape),
            EnvelopePlayer<Envelope<WaveSequence<2, Line>>&>(envelopeShape)
        };

        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        LinearInput<AnalogInputSumPinT> attackTimeCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0.01, 5);
        LinearInput<AnalogInputSumPinT> releaseTimeCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0.01, 5);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> lengthCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 8.99);
        #endif

        GateInput<> rangeInput = GateInput<>(Hardware::hw.rangeSwitchPin, false);
        
        float amp;
        int length;
        uint8_t envelopeIndex;

        void updateAttackReleaseTime();
        void updateLength();
        void updateAmp();
};

#endif
