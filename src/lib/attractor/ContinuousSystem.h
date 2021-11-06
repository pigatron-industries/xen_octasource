#ifndef ContinuousSystem_h
#define ContinuousSystem_h

#define X 0
#define Y 1
#define Z 2
#define W 3

template<int N>
class Tuple {
    public:
        Tuple() {};
        float& operator[](int i) {return val[i];}
        Tuple& operator+=(const Tuple& rhs) const { 
            for(int i = 0; i < N; i++) {
                this[i] += rhs[i];
            }
        }
        float val[N];
};

class ContinuousSystem {

};

template<int N>
class ContinuousSystemN : public ContinuousSystem {
    public:
        virtual void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleRateRecip = 1/sampleRate;
            dt = sampleRateRecip;
            for(int i = 0; i < N; i++) {
                limits.val[i] = 99999;
            }
        }

        void setSpeed(float speed) { dt = sampleRateRecip*speedMult*speed; }
        void setPosition(Tuple<N> position) { pos = position; }
        void movePosition(Tuple<N> move) {
            pos.x += move.x;
            pos.y += move.y;
            pos.z += move.z;
            pos.w += move.w;
        }

        float getX() { return (pos.x+offset.val[0])*mult.val[0]; }
        float getY() { return (pos.y+offset.val[0])*mult.val[0]; }
        float getZ() { return (pos.z+offset.val[0])*mult.val[0]; }

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
        float speedMult = 1;
        Tuple<N> pos;
        Tuple<N> delta;
        Tuple<N> mult;
        Tuple<N> offset;
        Tuple<N> limits;
};

#endif
