#ifndef Vector_h
#define Vector_h

#include <stdarg.h>
#include <math.h>
#include <Arduino.h>

#define X 0
#define Y 1
#define Z 2
#define W 3

template<int N>
class Vector {
    public:
        Vector() {}
        Vector(float x, float y) {
            val[0] = x;
            val[1] = y;
        }
        Vector(float x, float y, float z) {
            val[0] = x;
            val[1] = y;
            val[2] = z;
        }

        float& operator[](int i) { return val[i]; }
        const float& operator[](int i) const { return val[i]; }

        Vector& operator+=(const Vector& rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] += rhs.val[i];
            }
            return *this;
        }

        const Vector operator+(const Vector& other) const {
            return Tuple(*this) += other;
        }

        Vector& operator-=(const Vector& rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] -= rhs.val[i];
            }
            return *this;
        }

        const Vector operator-(const Vector& other) const {
            return Vector(*this) -= other;
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

        Vector& operator/=(float rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] /= rhs;
            }
            return *this;
        }

        const Vector operator/(float other) const {
            return Vector(*this) /= other;
        }

        float length() {
            float l = 0;
            for(int i = 0; i < N; i++) {
                l += val[i]*val[i];
            }
            return sqrtf(l);
        }

        float val[N];
};

inline Vector<2> rotate(Vector<2> vector, float radians) {
    Vector<2> rotated;
    rotated[X] = vector[X]*cosf(radians) + vector[Y]*sinf(radians);
    rotated[Y] = vector[X]*sinf(radians) + vector[Y]*cosf(radians);
    return rotated;
}

#endif