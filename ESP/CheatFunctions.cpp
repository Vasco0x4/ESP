#include "CheatFunctions.hpp"
#include "memory.hpp"
#include "imgui.h"
#include "offsets.hpp"
#include <iostream>

CheatFunctions::CheatFunctions(HANDLE processHandle, uintptr_t gameBaseAddress)
    : processHandle(processHandle), gameBaseAddress(gameBaseAddress) {}

std::vector<Entity> CheatFunctions::GetEntities() {
    std::vector<Entity> entities;

    uintptr_t worldAddress = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::world);
    std::cout << "World Address: " << std::hex << worldAddress << std::dec << std::endl;

    if (worldAddress == 0) {
        std::cerr << "Failed to read world address." << std::endl;
        return entities;
    }

    uint32_t entityCount = memory::read_memory<uint32_t>(processHandle, worldAddress + offsets::world::near_entity_table_size);
    std::cout << "Entity Count: " << entityCount << std::endl;

    if (entityCount > 1000) {  // check if the count is a reasonable number
        std::cout << "Invalid entity count: " << entityCount << std::endl;
        return entities;
    }

    uintptr_t entityListBase = memory::read_memory<uintptr_t>(processHandle, worldAddress + offsets::world::near_entity_table);
    std::cout << "Near Entity Table Base: " << std::hex << entityListBase << std::dec << std::endl;

    for (size_t i = 0; i < entityCount; i++) {
        uintptr_t entityAddress = memory::read_memory<uintptr_t>(processHandle, entityListBase + i * sizeof(uintptr_t));
        std::cout << "Entity address [" << i << "]: " << std::hex << entityAddress << std::dec << std::endl;

        if (entityAddress == 0) {
            continue;
        }

        vector3_t entityPosition = GetCoordinate(entityAddress);
        std::cout << "Position read: (" << entityPosition.x << ", " << entityPosition.y << ", " << entityPosition.z << ")" << std::endl;

        if (entityPosition.x == 0 && entityPosition.y == 0 && entityPosition.z == 0) {
            std::cout << "Invalid position for entity " << std::hex << entityAddress << std::dec << std::endl;
            continue;
        }

        char name[64] = "Unknown"; // Initialize name to a default value
        ReadProcessMemory(processHandle, (LPCVOID)(entityAddress + offsets::human_type::object_name), &name, sizeof(name), NULL);
        entities.push_back({ entityAddress, entityPosition, std::string(name) });
    }

    return entities;
}

vector3_t CheatFunctions::GetCoordinate(uintptr_t entityAddress) {
    uintptr_t visualState = memory::read_memory<uintptr_t>(processHandle, entityAddress + offsets::human::visual_state);
    vector3_t position = memory::read_memory<vector3_t>(processHandle, visualState + 0x2C);
    return position;
}

void CheatFunctions::RenderEntities(const std::vector<Entity>& entities) {
    for (const auto& entity : entities) {
        // Ensure the entity name is not empty
        std::string entityName = entity.name.empty() ? "Unknown" : entity.name;
        ImGui::SetNextWindowPos(ImVec2(entity.position.x, entity.position.y), ImGuiCond_Always);
        ImGui::Begin(entityName.c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("Player: %s\nPosition: (%.1f, %.1f, %.1f)", entityName.c_str(), entity.position.x, entity.position.y, entity.position.z);
        ImGui::End();
    }
}
