#pragma once
#include "vector3.hpp"

struct matrix_t {
    float m[16];

    bool is_valid() const {
        for (int i = 0; i < 16; ++i) {
            if (m[i] != 0.0f) {
                return true;
            }
        }
        return false;
    }
};

// Function declarations
vector3_t transform_coordinate(const vector3_t& coord, const matrix_t& matrix);
bool world_to_screen(HANDLE processHandle, uintptr_t gameBaseAddress, const vector3_t& world_coord, vector3_t& screen_coord, HWND hwnd);
