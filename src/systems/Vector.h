#ifndef Vector_h
#define Vector_h

#include <stdarg.h>

template<int N>
class Vector {
    public:
        Vector() {}

        Vector(float first, ...) {
            va_list args;
            va_start(args, first);
            val[0] = first;
            for(int i = 1; i < N; i++) {
                val[i] = va_arg(args, double);
            }
            va_end(args);
        };

        float& operator[](int i) { return val[i]; }

        Vector& operator+=(const Vector& rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] += rhs.val[i];
            }
            return *this;
        }

        const Vector operator+(const Vector& other) const {
            return Tuple(*this) += other;
        }

        Vector& operator*=(float rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] *= rhs;
            }
            return *this;
        }

        const Vector operator*(float other) const {
            return Vector(*this) *= other;
        }

        float val[N];
};

#endif