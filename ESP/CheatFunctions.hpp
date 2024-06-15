#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "vector3.hpp"

struct Entity {
    uintptr_t address;
    vector3_t position;
    std::string name;
};

class CheatFunctions {
public:
    CheatFunctions(HANDLE processHandle, uintptr_t gameBaseAddress, HWND hwnd);
    std::vector<Entity> GetEntities();
    float GetPlayerYaw();

private:
    HANDLE processHandle;
    uintptr_t gameBaseAddress;
    HWND hwnd;

    vector3_t GetCoordinate(uintptr_t entityAddress);
};
