#ifndef ShapeController_h
#define ShapeController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/continuous/shapes/ShapeRenderer.h"
#include "systems/continuous/shapes/2d/Shapes.h"

class ShapeController : public ParameterizedController<1> {
    public:
        ShapeController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        enum Parameter {
            MODE
        };
        enum Mode {
            EXAMPLE
        };

        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);

        ShapeRenderer renderer;

        //example
        Square2D square = Square2D();
        Triangle2D triangle1 = Triangle2D();
        Triangle2D triangle2 = Triangle2D();
        PathLine<2> line = PathLine<2>({-1, -1}, {1, 1});

        WaveOscillator<Pulse> oscillator;
        
        void updateRate();
};

#endif
