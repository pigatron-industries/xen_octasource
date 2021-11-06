#ifndef PhysicalModelController_h
#define PhysicalModelController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "lib/attractor/ContinuousSystem.h"

#define MODEL_COUNT 1

class PhysicalModelController : public Controller {
    public:
        PhysicalModelController() : Controller(MODEL_COUNT-1) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 1);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        //LinearInput<OctasourceInputDevice> cCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);

        //ContinuousSystem model;

        // Attractor* models[MODEL_COUNT] = {
        //     &model,
        // };

        float amp;
        
        void updateRate();
        void updateAmp();
};

#endif
