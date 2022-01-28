#ifndef AudioFrequencyController_h
#define AudioFrequencyController_h

#include "FrequencyController.h"
#include <eurorack_dsp.h>

class AudioFrequencyController : public FrequencyController {
    public:

        AudioFrequencyController() : FrequencyController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        void updateRate();
};

#endif
