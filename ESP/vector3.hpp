#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>

struct vector3_t {
    float x, y, z;

    vector3_t() : x(0), y(0), z(0) {}
    vector3_t(float x, float y, float z) : x(x), y(y), z(z) {}

    vector3_t operator+(const vector3_t& other) const {
        return vector3_t(x + other.x, y + other.y, z + other.z);
    }

    vector3_t operator-(const vector3_t& other) const {
        return vector3_t(x - other.x, y - other.y, z - other.z);
    }

    vector3_t operator*(float scalar) const {
        return vector3_t(x * scalar, y * scalar, z * scalar);
    }

    float dot(const vector3_t& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    vector3_t& normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
            z /= len;
        }
        return *this;
    }
};

#endif // VECTOR3_HPP
