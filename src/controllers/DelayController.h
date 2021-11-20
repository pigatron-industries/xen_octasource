#ifndef DelayController_h
#define DelayController_h

#include "../Controller.h"
#include "../Hardware.h"

class DelayController : public Controller {
    public:

        DelayController() : Controller(0) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 2);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        LinearInput<OctasourceInputDevice> param1CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.syncCvPin, -5, 5, -5, 5);
        
        void updateRate();
        void updateAmp();
        void updateParams();
};

#endif