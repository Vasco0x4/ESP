#include <windows.h>
#include <iostream>
#include <thread>
#include "memory.hpp"
#include "Graphics.h"
#include "ImGuiSetup.h"
#include "CheatFunctions.hpp"
#include "MiniMap.hpp"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "transformater.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void SetWindowTransparency(HWND hwnd) {
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "w", stderr);

    const wchar_t CLASS_NAME[] = L"ESPOverlayWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        std::cerr << "Failed to register window class.\n";
        return 1;
    }

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
        CLASS_NAME,
        L"DayZ ESP Overlay",
        WS_POPUP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) {
        std::cerr << "Failed to create window.\n";
        return 1;
    }

    SetWindowTransparency(hwnd);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    std::cout << "Starting DayZ ESP Mod...\n";

    if (!InitializeDirectX(hwnd)) {
        std::cerr << "Failed to initialize DirectX.\n";
        return 1;
    }

    std::cout << "DirectX initialized successfully.\n";

    InitializeImGui(hwnd);
    std::cout << "ImGui initialized successfully.\n";

    DWORD processId = memory::get_process_id("DayZ_x64.exe");
    if (processId == 0) {
        std::cerr << "Failed to find DayZ process.\n";
        return 1;
    }

    std::cout << "DayZ process found with PID: " << processId << "\n";

    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);
    if (!processHandle) {
        std::cerr << "Failed to open DayZ process.\n";
        return 1;
    }

    std::cout << "Successfully opened DayZ process.\n";

    uintptr_t gameBaseAddress = memory::get_module_base_address(processId, "DayZ_x64.exe");
    if (gameBaseAddress == 0) {
        std::cerr << "Failed to find the base address of DayZ.\n";
        CloseHandle(processHandle);
        return 1;
    }

    std::cout << "Base address of DayZ found at: " << std::hex << gameBaseAddress << "\n";

    CheatFunctions cheat(processHandle, gameBaseAddress, hwnd);
    MiniMap miniMap(200.0f, 200.0f); // size

    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    bool showEntityDebug = true;

    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (ImGui::Begin("Debug Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse)) {
            ImGui::Text("ESP Overlay Active");
            ImGui::Checkbox("Entity Debug", &showEntityDebug);

            std::vector<Entity> entities = cheat.GetEntities();

            if (!entities.empty()) {
                vector3_t playerPosition = entities[0].position;
                entities.erase(entities.begin()); // Remove the first entity (player) to avoid duplication

                ImGui::Text("Player Position: (%.1f, %.1f, %.1f)", playerPosition.x, playerPosition.y, playerPosition.z);
                ImGui::Text("Entities found: %d", entities.size());
                for (const auto& entity : entities) {
                    ImGui::Text("Entity: %s at (%.1f, %.1f, %.1f)", entity.name.c_str(), entity.position.x, entity.position.y, entity.position.z);
                }

                miniMap.Render(playerPosition, entities);
            }
            else {
                ImGui::Text("No entities found.");
            }

            ImGui::End();
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x, clear_color.y, clear_color.z, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSwapChain->Present(1, 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep between updates
    }

    std::cout << "Cleaning up ImGui and DirectX.\n";
    CleanupImGui();
    CleanupDirectX();
    CloseHandle(processHandle);
    std::cout << "Shutting down DayZ ESP Mod.\n";
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
