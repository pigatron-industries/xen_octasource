#ifndef Tuple_h
#define Tuple_h

#include <stdarg.h>

template<int N>
class Tuple {
    public:
        Tuple() {}

        Tuple(float first, ...) {
            va_list args;
            va_start(args, first);
            val[0] = first;
            for(int i = 1; i < N; i++) {
                val[i] = va_arg(args, double);
            }
            va_end(args);
        };

        float& operator[](int i) { return val[i]; }

        Tuple& operator+=(const Tuple& rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] += rhs.val[i];
            }
            return *this;
        }

        const Tuple operator+(const Tuple& other) const {
            return Tuple(*this) += other;
        }

        Tuple& operator*=(float rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] *= rhs;
            }
            return *this;
        }

        const Tuple operator*(float other) const {
            return Tuple(*this) *= other;
        }

        float val[N];
};

#endif