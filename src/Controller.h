#ifndef Controller_h
#define Controller_h

#include <eurorack.h>
#include "Hardware.h"
#include "common/Controls.h"

class Controller : public AbstractController {
    public:
        Controller(int lastMode = 0) : AbstractController(lastMode) {}
        virtual void init(float sampleRate) { this->sampleRate = sampleRate; }
        void init() {}
        void load() { 
            Config::config.load(config); 
            if(config.data.check == 0 && config.data.mode <= mode.last) {
                mode.value = config.data.mode; 
            }
        }
        void save() { 
            config.data.check = 0;
            config.data.mode = mode.value;
            Config::config.save(config);
        }
        void update() = 0;
        virtual void process() = 0;
        float getSampleRate() { return sampleRate; }
    
    protected: 
        float sampleRate = 0;
        Controls& controls = Controls::controls;

        struct SaveMode {
            uint8_t check = 0;
            uint8_t mode;
        };
        ConfigField<SaveMode> config;
};


template<int N>
class ParameterizedController : public Controller {
    public:
        ParameterizedController() {}
        void configParam(uint8_t param, uint8_t defaultval, uint8_t maxval);
        void load();
        void save();
        int cycleMode(int amount);
        void cycleValue(int amount);

    protected:
        ArraySelector<CycleEnum<int>, N> parameters;

        struct SaveParameters {
            uint8_t check = 0;
            uint8_t parameters[N];
        };
        ConfigField<SaveParameters> config;
};

template<int N>
void ParameterizedController<N>::configParam(uint8_t index, uint8_t defaultval, uint8_t maxval) {
    parameters[index].last = maxval;
    if(config.data.check == 0 && parameters[index].value <= maxval) {
        parameters[index].value = config.data.parameters[index];
    } else {
        parameters[index].value = defaultval;
    }
}

template<int N>
void ParameterizedController<N>::load() {
    Config::config.load(config);
}

template<int N>
void ParameterizedController<N>::save() {
    config.data.check = 0;
    for(int i = 0; i < N; i++) {
        config.data.parameters[i] = parameters[i].value;
    }
    Config::config.save(config);
}

template<int N>
int ParameterizedController<N>::cycleMode(int amount) { 
    parameters.cycle(amount);
    return parameters.getSelectedIndex(); 
}

template<int N>
void ParameterizedController<N>::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    save();
}


#endif
