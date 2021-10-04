#ifndef Attractor_h
#define Attractor_h

class Deltas {
    public:
        float dxdt, dydt, dzdt, dwdt;
};

class Attractor {
    public:
        virtual void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleRateRecip = 1/sampleRate;
            dt = sampleRateRecip;
        }

        void setSpeed(float speed) { dt = sampleRateRecip*speedMult*speed; }

        float getX() { return (x+xOffset)*xMult; }
        float getY() { return (y+yOffset)*yMult; }
        float getZ() { return (z+zOffset)*zMult; }

        void process() {
            Deltas d = system(x, y, z);
            x += dt*d.dxdt;
            y += dt*d.dydt;
            z += dt*d.dzdt;
        };

        virtual Deltas system(float x, float y, float z) = 0;

    protected:
        float sampleRate, sampleRateRecip;
        float dt;
        float x, y, z;
        float xMult = 1, yMult = 1, zMult = 1, speedMult = 1;
        float xOffset, yOffset, zOffset;
};

#endif
