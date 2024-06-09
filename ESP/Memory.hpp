#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <windows.h>
#include <string>

namespace memory {
    std::wstring string_to_wstring(const std::string& str);
    DWORD get_process_id(const std::string& processName);
    uintptr_t get_module_base_address(DWORD procId, const std::string& modName);

    template<typename T>
    T read_memory(HANDLE process, uintptr_t address) {
        T buffer;
        ReadProcessMemory(process, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), nullptr);
        return buffer;
    }

    template<typename T>
    void write_memory(HANDLE process, uintptr_t address, T value) {
        WriteProcessMemory(process, reinterpret_cast<LPVOID>(address), &value, sizeof(T), nullptr);
    }
}

#endif // MEMORY_HPP