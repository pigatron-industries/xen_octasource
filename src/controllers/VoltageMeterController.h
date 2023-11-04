#ifndef VoltageMeterController_h
#define VoltageMeterController_h

#include "../Controller.h"
#include "../Hardware.h"

class VoltageMeterController : public Controller {
    public:

        VoltageMeterController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        float value;

        void rangePos(int index, float start);
        void rangeNeg(int index, float start);
};

#endif