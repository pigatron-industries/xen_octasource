#ifndef WaveShapes_h
#define WaveShapes_h

#include <eurorack_dsp.h>

class WaveShapes {
    public:
        static Sine sine;
        static Triangle triangle;
        static Saw saw;
        static Pulse pulse;

        static WaveShape* waveShapes[4];
};

#endif
