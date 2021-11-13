#ifndef Vector_h
#define Vector_h

#include <stdarg.h>
#include <math.h>

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

        // void print() {
        //     Serial.print("(");
        //     Serial.print(val[0], 5);
        //     Serial.print(",");
        //     Serial.print(val[1], 5);
        //     Serial.print(") ");
        // }

        float val[N];
};

#endif