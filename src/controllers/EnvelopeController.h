#ifndef EnvelopeController_h
#define EnvelopeController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define ATTRACTOR_COUNT 12

class EnvelopeController : public Controller {
    public:
        enum Mode {
            LATCHED,
            GATED
        };

        EnvelopeController() : Controller(Mode::GATED) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
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

        LinearInput<AnalogInputPinT> attackTimeCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.waveCvPin, -5, 5, 0.01, 5);
        LinearInput<AnalogInputPinT> releaseTimeCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.rateCvPin, -5, 5, 0.01, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputPinT> lengthCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.phaseCvPin, -5, 5, 0, 8.99);
        #endif
        
        float amp;
        int length;
        uint8_t envelopeIndex;

        void updateAttackReleaseTime();
        void updateLength();
        void updateAmp();
};

#endif
