#ifndef Controller_h
#define Controller_h

#include "eurorack.h"

class Controller {
    public:
        Controller(int lastMode = 0) : mode(0, lastMode) {}
        void init(float sampleRate) { this->sampleRate = sampleRate; this->init(); }
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void process() = 0;
        int cycleMode(int amount) { mode.cycle(amount); return mode.value; }
        void setMode(int value) { mode.setValue(value); }
    
    protected: 
        float sampleRate;
        CycleEnum<int> mode;
};

#endif
