#ifndef BouncingBall_h
#define BouncingBall_h

#include "../ContinuousSystem.h"
#include <eurorack.h>


class BouncingBall : public ContinuousSystemN<1> {
    public:

        enum FloorMode {
            BOUNCE,
            INVERT
        };

        void init(float sampleRate);
        void trigger();
        void setParam(int param, float value);
        void setFloorMode(FloorMode floorMode) { this->floorMode = floorMode; };
        void setDamp(float damp) { this->damp = damp; }

        void process();

    private:
        float damp = 0.9;
        float startVelocity = 3;
        FloorMode floorMode = FloorMode::INVERT;
    
        float velocity;
        float acceleration = 1;
};

#endif
