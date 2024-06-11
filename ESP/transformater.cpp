#include "memory.hpp"
#include "transformater.hpp"
#include "offsets.hpp"
#include <iostream>
#include <vector> // Inclure <vector> pour std::vector
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

void print_memory(HANDLE process, uintptr_t address, size_t size) {
    std::vector<uint8_t> buffer(size);
    SIZE_T bytesRead;
    if (ReadProcessMemory(process, reinterpret_cast<LPCVOID>(address), buffer.data(), size, &bytesRead) && bytesRead == size) {
        std::cout << "Memory at address " << std::hex << address << ":\n";
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::hex << static_cast<int>(buffer[i]) << " ";
            if ((i + 1) % 16 == 0) std::cout << "\n";
        }
        std::cout << std::dec << std::endl;
    }
    else {
        std::cerr << "Failed to read memory at address " << std::hex << address << std::dec << std::endl;
    }
}

bool world_to_screen(HANDLE processHandle, uintptr_t gameBaseAddress, const vector3_t& world_coord, vector3_t& screen_coord, HWND hwnd) {
    uintptr_t cameraAddress = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::camera);
    if (cameraAddress == 0) {
        std::cerr << "Invalid camera address: " << std::hex << cameraAddress << std::dec << std::endl;
        return false;
    }

    uintptr_t viewProjectionAddress = cameraAddress + offsets::camera::view_projection;

    // Print raw memory at the view projection matrix address
    print_memory(processHandle, viewProjectionAddress, sizeof(matrix_t));

    matrix_t view_projection = memory::read_memory<matrix_t>(processHandle, viewProjectionAddress);

    // Verify if the matrix is valid
    bool valid = true;
    for (int i = 0; i < 16; ++i) {
        if (isnan(view_projection.m[i]) || isinf(view_projection.m[i])) {
            valid = false;
            std::cerr << "Invalid matrix value at index " << i << ": " << view_projection.m[i] << std::endl;
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

    std::cout << "Transformed Coord: (" << transformed_coord.x << ", " << transformed_coord.y << ", " << transformed_coord.z << ")\n";
    std::cout << "Screen Coord: (" << screen_coord.x << ", " << screen_coord.y << ")\n";

    return transformed_coord.z > 0.1f;
}

