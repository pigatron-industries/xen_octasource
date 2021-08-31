#ifndef MultipliedController_h
#define MultipliedController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

class MultipliedController : public AbstractOscillatorController {
    public:
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    private:
        void updateRate();
};

#endif
