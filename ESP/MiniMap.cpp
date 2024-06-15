#include "MiniMap.hpp"
#include "CheatFunctions.hpp"
#include "imgui.h"
#include <iostream>

MiniMap::MiniMap(float width, float height) : width(width), height(height), range(250.0f) {} 

void MiniMap::Render(const vector3_t& playerPosition, const std::vector<Entity>& entities) {
    // Setup mini-map position and size
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always); 
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::Begin("MiniMap", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings);

    // Draw the circle representing the mini-map range
    float centerX = width / 2;
    float centerY = height / 2;
    float radius = width / 2 - 5;
    ImU32 mapColor = IM_COL32(255, 255, 255, 255); // White for the map border
    ImU32 playerColor = IM_COL32(0, 255, 0, 255); // Green for player
    ImU32 entityColor = IM_COL32(255, 0, 0, 255); // Red for entities

    // Draw the map circle
    DrawCircle(centerX, centerY, radius, mapColor);

    // Draw player at the center
    DrawPoint(centerX, centerY, playerColor);

    // Draw entities within the range
    for (const auto& entity : entities) {
        float distX = entity.position.x - playerPosition.x;
        float distY = entity.position.z - playerPosition.z;
        if (sqrt(distX * distX + distY * distY) <= range) { // Check if entity is within range
            float relativeX = centerX + (distX / range) * radius;
            float relativeY = centerY + (distY / range) * radius;
            DrawPoint(relativeX, relativeY, entityColor);
        }
    }

    ImGui::End();
}

void DrawRectangle(float x, float y, float width, float height, ImU32 color) {
    ImGui::GetWindowDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), color);
}

void DrawLine(float x1, float y1, float x2, float y2, ImU32 color) {
    ImGui::GetWindowDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color);
}

void DrawCircle(float x, float y, float radius, ImU32 color) {
    ImGui::GetWindowDrawList()->AddCircle(ImVec2(x, y), radius, color);
}

void DrawPoint(float x, float y, ImU32 color) {
    ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(x, y), 3, color);
}
