#include "ImGuiRenderer.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

void RenderImGui(CheatFunctions& cheat, MiniMap& miniMap, bool& showDebugWindow, bool& showMiniMap) {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs)) {
        ImGui::Text("ESP Overlay Active");
        ImGui::Checkbox("Show Debug Window", &showDebugWindow);
        ImGui::Checkbox("Show Mini Map", &showMiniMap);
        ImGui::End();
    }

    if (showDebugWindow) {
        ImGui::Begin("Debug Menu", &showDebugWindow, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);
        std::vector<Entity> entities = cheat.GetEntities();

        if (!entities.empty()) {
            vector3_t playerPosition = entities[0].position;
            entities.erase(entities.begin()); // Remove the first entity (player) to avoid duplication

            ImGui::Text("Player Position: (%.1f, %.1f, %.1f)", playerPosition.x, playerPosition.y, playerPosition.z);
            ImGui::Text("Entities found: %d", entities.size());
            for (const auto& entity : entities) {
                ImGui::Text("Entity: %s at (%.1f, %.1f, %.1f)", entity.name.c_str(), entity.position.x, entity.position.y, entity.position.z);
            }
        }
        else {
            ImGui::Text("No entities found.");
        }
        ImGui::End();
    }

    if (showMiniMap) {
        std::vector<Entity> entities = cheat.GetEntities();
        if (!entities.empty()) {
            vector3_t playerPosition = entities[0].position;
            entities.erase(entities.begin());
            miniMap.Render(playerPosition, entities);
        }
    }

    ImGui::Render();
}
