#ifndef Attractor_h
#define Attractor_h

class Tuple {
    public:
        Tuple(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {};
        float x, y, z, w;
};

class Attractor {
    public:
        virtual void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleRateRecip = 1/sampleRate;
            dt = sampleRateRecip;
            limits.x = 99999;
            limits.y = 99999;
            limits.z = 99999;
            limits.w = 99999;
        }

        void setSpeed(float speed) { dt = sampleRateRecip*speedMult*speed; }
        void setPosition(float x, float y, float z) {}

        float getX() { return (pos.x+xOffset)*xMult; }
        float getY() { return (pos.y+yOffset)*yMult; }
        float getZ() { return (pos.z+zOffset)*zMult; }
        float getDX() { return delta.x; }
        float getDY() { return delta.y; }
        float getDZ() { return delta.z; }

        void process() {
            system();
            pos.x += dt*delta.x;
            pos.y += dt*delta.y;
            pos.z += dt*delta.z;

            if(pos.x > limits.x) {
                pos.x = limits.x;
            } else if(pos.x < -limits.x) {
                pos.x = -limits.x;
            }
        };

        virtual void system() = 0;

    protected:
        float sampleRate, sampleRateRecip;
        float dt;
        Tuple pos;
        Tuple delta;
        float xMult = 1, yMult = 1, zMult = 1, speedMult = 1;
        float xOffset, yOffset, zOffset;
        Tuple limits;
};

#endif
