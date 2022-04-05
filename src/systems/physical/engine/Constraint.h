#ifndef Constraint_h
#define Constraint_h

#include "Body.h"

class Constraint {
    public:
        virtual void apply() = 0;
};

#endif