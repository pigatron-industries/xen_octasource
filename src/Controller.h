#ifndef Controller_h
#define Controller_h

class Controller {
    public:
        virtual void init(float sampleRate) {}
        virtual void update() {}
        virtual void process() = 0;
};

#endif
