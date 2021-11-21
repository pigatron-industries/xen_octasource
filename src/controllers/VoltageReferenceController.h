#ifndef VoltageReferenceController_h
#define VoltageReferenceController_h

#include "../Controller.h"
#include "../Hardware.h"

class VoltageReferenceController : public Controller {
    public:
        VoltageReferenceController() : Controller(0) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        
};

#endif