#ifndef Controller_h
#define Controller_h

#include <eurorack.h>
#include "Hardware.h"
#include "common/Controls.h"

class Controller : public AbstractController {
    public:
        Controller(int lastMode = 0) : mode(0, lastMode) {}
        virtual void init(float sampleRate) { this->sampleRate = sampleRate; }
        virtual void init() {};
        virtual void update() = 0;
        virtual void process() = 0;
        float getSampleRate() { return sampleRate; }
    
    protected: 
        float sampleRate = 0;
        CycleEnum<int> mode;
        Controls& controls = Controls::controls;
};

template<int N>
class ParameterizedController : public Controller {
    public:
        ParameterizedController() {  }
        virtual int cycleMode(int amount) { 
            parameters.cycle(amount);
            return parameters.getSelectedIndex(); 
        }
        virtual void cycleValue(int amount) {
            parameters.getSelected().cycle(amount);
        }

    protected:
        ArraySelector<CycleEnum<int>, N> parameters;
};

#endif
