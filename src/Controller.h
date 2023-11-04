#ifndef Controller_h
#define Controller_h

#include <eurorack.h>
#include "Hardware.h"
#include "common/Controls.h"

class Controller : public AbstractController {
    public:
        Controller() : AbstractController() {}
        virtual void init(float sampleRate) { this->sampleRate = sampleRate; }
        virtual void init() {};
        virtual void update() = 0;
        virtual void process() = 0;
        float getSampleRate() { return sampleRate; }
    
    protected: 
        float sampleRate = 0;
        Controls& controls = Controls::controls;
};


template<int N>
class ParameterizedController : public Controller, public AbstractParameterizedController<N> {
    public:
        void load() { AbstractParameterizedController<N>::load(); }
        void save() { AbstractParameterizedController<N>::save(); }
};

#endif
