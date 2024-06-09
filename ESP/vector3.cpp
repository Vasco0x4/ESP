#include "memory.hpp"
#include "vector3.hpp"
#include "offsets.hpp"
#include <iostream>

vector3_t get_entity_position(HANDLE process, uintptr_t entityBase) {
    uintptr_t positionAddress = entityBase + offsets::visual_state::transform;
    std::cout << "Reading position from address: " << std::hex << positionAddress << "\n";

    if (positionAddress == 0) {
        std::cerr << "Invalid position address\n";
        return vector3_t(0, 0, 0);
    }

    float x = memory::read_memory<float>(process, positionAddress);
    float y = memory::read_memory<float>(process, positionAddress + sizeof(float));
    float z = memory::read_memory<float>(process, positionAddress + 2 * sizeof(float));

    std::cout << "Position read: (" << x << ", " << y << ", " << z << ")\n";

    if (x == 0 && y == 0 && z == 0) {
        std::cerr << "Invalid position read\n";
    }

    return vector3_t(x, y, z);
}
