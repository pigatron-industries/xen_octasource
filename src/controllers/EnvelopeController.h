#ifndef EnvelopeController_h
#define EnvelopeController_h

#include "Controller.h"
#include <eurorack_dsp.h>

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
        //TODO use line segments
        Envelope envelopes[OUTPUT_CV_COUNT];

        LinearInput<OctasourceInputDevice> attackTimeCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0.01, 5);
        LinearInput<OctasourceInputDevice> releaseTimeCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, -5, 5, 0.01, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> lengthCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0, 8.99);
        #endif
        
        float amp;
        int length;
        uint8_t envelopeIndex;

        void updateAttackReleaseTime();
        void updateLength();
        void updateAmp();
};

#endif
