#ifndef Hypotrochoid_h
#define Hypotrochoid_h

#include "ParametricSystem.h"
#include "math.h"


class Hypotrochoid : public ParametricSystemN<2> {
    public:
        Hypotrochoid() {}
        void init(float sampleRate) {
            ParametricSystemN<2>::init(sampleRate);
            setFrequency(10);
        };

        void setFrequency(float frequency);
        void setRadiusLarge(float radiusLarge) { this->radiusLarge = radiusLarge; calcCoefficients(); }
        void setRadiusSmall(float radiusSmall) { this->radiusSmall = radiusSmall; calcCoefficients(); }
        void setRadiusLargeSmall(float radiusLarge, float radiusSmall) { this->radiusLarge = radiusLarge; this->radiusSmall = radiusSmall; calcCoefficients(); }
        void setRadiusPoint(float radiusPoint) { this->radiusPoint = radiusPoint; }

        void process();
        
    
    public:
        float radiusLarge = 1;
        float radiusSmall = 0.5;
        float radiusPoint = 0.5;

        float radiusDiff;

        float incrementAngleLarge;
        float incrementAngleSmall;

        float angleLarge;
        float angleSmall;

        void calcCoefficients();
        void system();
        void incrementAngles();
};

inline void Hypotrochoid::setFrequency(float frequency) {
    increment = sampleTime * frequency;
    calcCoefficients();
}

inline void Hypotrochoid::calcCoefficients() {
    radiusDiff = radiusLarge - radiusSmall;
    incrementAngleLarge = increment * 2 * M_PI;
    incrementAngleSmall = incrementAngleLarge * (radiusDiff/radiusSmall);
}


inline void Hypotrochoid::process() {
    system();
    incrementAngles();
}

inline void Hypotrochoid::system() {
    pos[X] = radiusDiff * cosf(angleLarge) + radiusPoint * cosf(angleSmall);
    pos[Y] = radiusDiff * sinf(angleLarge) + radiusPoint * sinf(angleSmall);    
}

inline void Hypotrochoid::incrementAngles() {
    angleLarge += incrementAngleLarge;
    if(angleLarge > 2*M_PI) {
        angleLarge -= 2*M_PI;
    }
    angleSmall += incrementAngleSmall;
    if(angleSmall > 2*M_PI) {
        angleSmall -= 2*M_PI;
    } else if (angleSmall < 0) {
        angleSmall += 2*M_PI;
    }
}



#endif