#ifndef Force_h
#define Force_h

#include "Body.h"

class Force {
    public:
        virtual void apply(Body& body) = 0;
};

#endif