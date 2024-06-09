#include "CheatFunctions.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include <iostream>

CheatFunctions::CheatFunctions(HANDLE processHandle, uintptr_t gameBaseAddress)
    : processHandle(processHandle), gameBaseAddress(gameBaseAddress) {}

std::vector<Entity> CheatFunctions::GetEntities() {
    std::vector<Entity> entities;

    uintptr_t worldAddress = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::world);
    std::cout << "World Address: " << std::hex << worldAddress << std::endl;

    if (worldAddress == 0) {
        std::cerr << "Invalid world address" << std::endl;
        return entities;
    }

    size_t entityCount = memory::read_memory<size_t>(processHandle, worldAddress + offsets::world::near_entity_table_size);
    std::cout << "Entity Count: " << entityCount << std::endl;

    if (entityCount == 0 || entityCount > 10000) {  // Check for a reasonable entity count
        std::cerr << "Invalid entity count: " << entityCount << std::endl;
        return entities;
    }

    uintptr_t entityListBase = memory::read_memory<uintptr_t>(processHandle, worldAddress + offsets::world::near_entity_table);
    std::cout << "Entity List Base: " << std::hex << entityListBase << std::endl;

    for (int i = 0; i < entityCount; i++) {
        uint64_t entityAddress = memory::read_memory<uint64_t>(processHandle, entityListBase + (i * 0x8));
        std::cout << "Entity address [" << std::hex << i << "]: " << entityAddress << std::endl;

        if (entityAddress == 0) {
            continue; // Skip if address is null
        }

        vector3_t entityPosition = GetCoordinate(entityAddress);
        std::cout << "Position read: (" << entityPosition.x << ", " << entityPosition.y << ", " << entityPosition.z << ")" << std::endl;

        if (entityPosition.x == 0 && entityPosition.y == 0 && entityPosition.z == 0) {
            std::cerr << "Invalid position for entity " << std::hex << entityAddress << std::endl;
            continue; // Skip if position is invalid
        }

        char name[64] = { 0 };
        if (!ReadProcessMemory(processHandle, (LPCVOID)(entityAddress + offsets::human_type::object_name), &name, sizeof(name), NULL)) {
            std::cerr << "Failed to read name for entity " << std::hex << entityAddress << std::endl;
            continue; // Skip if name reading fails
        }
        entities.push_back({ entityAddress, entityPosition, std::string(name) });

        std::cout << "Entity " << std::hex << entityAddress << ": " << name << " at (" << entityPosition.x << ", " << entityPosition.y << ", " << entityPosition.z << ")\n";
    }

    return entities;
}

vector3_t CheatFunctions::GetCoordinate(uint64_t entityAddress) {
    uint64_t visualStateAddress = memory::read_memory<uint64_t>(processHandle, entityAddress + offsets::human::visual_state);
    return memory::read_memory<vector3_t>(processHandle, visualStateAddress + 0x2C);
}
