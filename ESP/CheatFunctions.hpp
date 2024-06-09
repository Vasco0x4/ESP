#ifndef CHEAT_FUNCTIONS_HPP
#define CHEAT_FUNCTIONS_HPP

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
    CheatFunctions(HANDLE processHandle, uintptr_t gameBaseAddress);
    std::vector<Entity> GetEntities();
    vector3_t GetCoordinate(uint64_t entityAddress);

private:
    HANDLE processHandle;
    uintptr_t gameBaseAddress;
};

#endif // CHEAT_FUNCTIONS_HPP
