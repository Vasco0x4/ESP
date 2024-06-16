#include "CheatFunctions.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include <iostream>

CheatFunctions::CheatFunctions(HANDLE processHandle, uintptr_t gameBaseAddress, HWND hwnd)
    : processHandle(processHandle), gameBaseAddress(gameBaseAddress), hwnd(hwnd) {}

std::vector<Entity> CheatFunctions::GetEntities() {
    std::vector<Entity> entities;

    uintptr_t worldAddress = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::world);

    if (worldAddress == 0) {
        std::cerr << "Failed to read world address." << std::endl;
        return entities;
    }

    uint32_t entityCount = memory::read_memory<uint32_t>(processHandle, worldAddress + offsets::world::near_entity_table_size);

    if (entityCount > 1000) {
        return entities;
    }

    uintptr_t entityListBase = memory::read_memory<uintptr_t>(processHandle, worldAddress + offsets::world::near_entity_table);

    for (size_t i = 0; i < entityCount; i++) {
        uintptr_t entityAddress = memory::read_memory<uintptr_t>(processHandle, entityListBase + i * sizeof(uintptr_t));

        if (entityAddress == 0) {
            continue;
        }

        vector3_t entityPosition = GetCoordinate(entityAddress);

        if (entityPosition.x == 0 && entityPosition.y == 0 && entityPosition.z == 0) {
            continue;
        }

        char name[64];
        if (!ReadProcessMemory(processHandle, (LPCVOID)(entityAddress + offsets::human_type::object_name), &name, sizeof(name), NULL)) {
            std::cerr << "Failed to read entity name for entity " << std::hex << entityAddress << std::dec << std::endl;
            continue;
        }
        name[sizeof(name) - 1] = '\0'; // Ensure null-termination
        entities.push_back({ entityAddress, entityPosition, std::string(name) });
    }

    return entities;
}

vector3_t CheatFunctions::GetCoordinate(uintptr_t entityAddress) {
    uintptr_t visualState = memory::read_memory<uintptr_t>(processHandle, entityAddress + offsets::human::visual_state);
    if (visualState == 0) {
        std::cerr << "Invalid visual state address for entity " << std::hex << entityAddress << std::dec << std::endl;
        return vector3_t(0, 0, 0);
    }
    vector3_t position = memory::read_memory<vector3_t>(processHandle, visualState + 0x2C);
    return position;
}
