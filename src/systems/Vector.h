#ifndef Vector_h
#define Vector_h

#include <stdarg.h>
#include <math.h>
#include <Arduino.h>

enum {
    X = 0,
    Y = 1,
    Z = 2,
    W = 3
};

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
        Vector(std::initializer_list<float> list) {
            int i = 0;
            for(float f : list) {
                val[i] = f;
                i++;
            }
        }

        void operator=(std::initializer_list<float> list) {
            int i = 0;
            for(float f : list) {
                val[i] = f;
                i++;
            }
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
            return Vector(*this) += other;
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

        const Vector operator-() const {
            return Vector(*this) *= -1;
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

        Vector& operator*=(const Vector& rhs) { 
            for(int i = 0; i < N; i++) {
                val[i] *= rhs.val[i];
            }
            return *this;
        }

        const Vector operator*(const Vector& other) const {
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


inline float angle2d(Vector<2> vector) {
    return atan2f(vector[Y], vector[X]);
}


inline Vector<2> rotate2d(Vector<2> vector, float radians) {
    Vector<2> rotated;
    float sin1 = sinf(radians);
    float cos1 = cosf(radians);
    rotated[X] = vector[X]*cos1 - vector[Y]*sin1;
    rotated[Y] = vector[X]*sin1 + vector[Y]*cos1;
    return rotated;
}

inline Vector<2> rotate3dAndFlatten(Vector<3> vector, float radians1, float radians2) {
    Vector<2> rotated;
    float sin1 = sinf(radians1);
    float cos1 = cosf(radians1);
    float sin2 = sinf(radians2);
    float cos2 = cosf(radians2);
    rotated[X] = vector[X]*cos1 - vector[Y]*sin1;
    rotated[Y] = vector[X]*sin2*sin1 + vector[Y]*sin2*cos1 + vector[Z]*cos2;
    return rotated;
}

#endif