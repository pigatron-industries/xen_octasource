#ifndef debug_h
#define debug_h

#include "systems/Vector.h"

inline void print(Vector<2>& vector) {
    Serial.print("(");
    Serial.print(vector[X], 5);
    Serial.print(",");
    Serial.print(vector[Y], 5);
    Serial.print(") ");
}

inline void println(Vector<2>& vector) {
    Serial.print("(");
    Serial.print(vector[X], 5);
    Serial.print(",");
    Serial.print(vector[Y], 5);
    Serial.println(")");
}

#endif