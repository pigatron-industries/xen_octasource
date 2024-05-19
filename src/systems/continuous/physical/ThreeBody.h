#ifndef ThreeBody_h
#define ThreeBody_h

#include <eurorack.h>
#include "../ContinuousSystem.h"
#include "engine/Body.h"

#define BODIES 3
#define G 1

class ThreeBody : public ContinuousSystemN<6> {
    public:

        enum EdgeMode {
            NONE,
            BOUNCE,
            WRAP,
            ANTIGRAV
        };

        void init(float sampleRate);
        void setBodies(const Array<Body, BODIES>& bodies);
        void setLimit(float limit) { this->limit = limit; };
        void setDriftCorrection(bool driftCorrection) { this->driftCorrection = driftCorrection; };
        void setEdgeMode(EdgeMode edgeMode) { this->edgeMode = edgeMode; };
        void setDamp(float damp) { this->damp = damp; }

        Array<Body, BODIES>& getBodies() { return bodies; }

        void process();

        Vector<2> calculateMomentum() { return calculateMomentum(bodies); }

        static Array<Body, BODIES> initEqualInlineSystem(int mult, Vector<2> velocity);

    private:
        Array<Body, BODIES> bodies;
        float limit = 5;
        float damp = 0.25;
        float minDist = 0.01;
        bool driftCorrection;
        EdgeMode edgeMode;

        void calculateAcceleration(int i);
        Vector<2> calculateCentreOfMass(Array<Body, BODIES>& bodies);
        Vector<2> calculateMomentum(Array<Body, BODIES>& bodies);
        void limitBodies();
        void doDriftCorrection();
        void applyAntiGrav(int body);
        void applyAntiGrav(int body, int dimension, int direction);
        void setOutputs();
    
};

#endif
