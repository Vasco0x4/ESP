#pragma once
#include <ostream>
#include <Windows.h> // Include Windows.h for HANDLE and uintptr_t
#include <cmath> // Include cmath for sqrt

struct vector3_t {
    float x, y, z;

    vector3_t() : x(0), y(0), z(0) {}
    vector3_t(float x, float y, float z) : x(x), y(y), z(z) {}

    // Overload the + operator to add two vectors
    vector3_t operator+(const vector3_t& other) const {
        return vector3_t(x + other.x, y + other.y, z + other.z);
    }

    // Overload the - operator to subtract two vectors
    vector3_t operator-(const vector3_t& other) const {
        return vector3_t(x - other.x, y - other.y, z - other.z);
    }

    // Overload the * operator for scalar multiplication
    vector3_t operator*(float scalar) const {
        return vector3_t(x * scalar, y * scalar, z * scalar);
    }

    // Dot product of two vectors
    float dot(const vector3_t& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Length of the vector
    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    vector3_t& normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
            z /= len;
        }
        return *this;
    }

    // Print the vector for debugging purposes
    friend std::ostream& operator<<(std::ostream& os, const vector3_t& vec) {
        os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};

// Function declaration for reading an entity's position
vector3_t get_entity_position(HANDLE process, uintptr_t entityBase);
