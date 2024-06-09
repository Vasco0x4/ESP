#include "memory.hpp"
#include "transformater.hpp"
#include "offsets.hpp"
#include <iostream>
#include <windows.h>

vector3_t transform_coordinate(const vector3_t& coord, const matrix_t& matrix) {
    vector3_t transformed_coord;

    transformed_coord.x = coord.x * matrix.m[0] + coord.y * matrix.m[4] + coord.z * matrix.m[8] + matrix.m[12];
    transformed_coord.y = coord.x * matrix.m[1] + coord.y * matrix.m[5] + coord.z * matrix.m[9] + matrix.m[13];
    transformed_coord.z = coord.x * matrix.m[2] + coord.y * matrix.m[6] + coord.z * matrix.m[10] + matrix.m[14];

    float w = coord.x * matrix.m[3] + coord.y * matrix.m[7] + coord.z * matrix.m[11] + matrix.m[15];

    if (w != 0.0f) {
        transformed_coord.x /= w;
        transformed_coord.y /= w;
        transformed_coord.z /= w;
    }

    return transformed_coord;
}

bool world_to_screen(HANDLE processHandle, uintptr_t gameBaseAddress, const vector3_t& world_coord, vector3_t& screen_coord, HWND hwnd) {
    uintptr_t cameraAddress = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::camera);
    uintptr_t viewProjectionAddress = cameraAddress + offsets::camera::view_projection;
    matrix_t view_projection = memory::read_memory<matrix_t>(processHandle, viewProjectionAddress);

    // Vérifier si la matrice est valide
    bool valid = true;
    for (int i = 0; i < 16; ++i) {
        if (isnan(view_projection.m[i]) || isinf(view_projection.m[i])) {
            valid = false;
            break;
        }
    }

    if (!valid) {
        std::cerr << "Invalid view projection matrix.\n";
        return false;
    }

    std::cout << "View Projection Matrix:\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << view_projection.m[i] << " ";
        if (i % 4 == 3) std::cout << "\n";
    }

    vector3_t transformed_coord = transform_coordinate(world_coord, view_projection);

    RECT rect;
    GetWindowRect(hwnd, &rect);

    screen_coord.x = rect.left + (rect.right - rect.left) / 2 * (1 + transformed_coord.x);
    screen_coord.y = rect.top + (rect.bottom - rect.top) / 2 * (1 - transformed_coord.y);

    return transformed_coord.z > 0.1f;
}
