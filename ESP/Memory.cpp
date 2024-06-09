#include "memory.hpp"
#include <codecvt>
#include <locale>
#include <tlhelp32.h> 
#pragma comment(lib, "Kernel32.lib") 

namespace memory {
    std::wstring string_to_wstring(const std::string& str) {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), nullptr, 0);
        std::wstring wstr(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), &wstr[0], size_needed);
        return wstr;
    }

    DWORD get_process_id(const std::string& processName) {
        std::wstring wProcessName = string_to_wstring(processName);
        DWORD processId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(hSnap, &pe32)) {
                do {
                    if (wProcessName == pe32.szExeFile) {
                        processId = pe32.th32ProcessID;
                        break;
                    }
                } while (Process32Next(hSnap, &pe32));
            }
            CloseHandle(hSnap);
        }
        return processId;
    }

    uintptr_t get_module_base_address(DWORD procId, const std::string& modName) {
        std::wstring wModName = string_to_wstring(modName);
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 me32;
            me32.dwSize = sizeof(MODULEENTRY32);
            if (Module32First(hSnap, &me32)) {
                do {
                    if (wModName == me32.szModule) {
                        modBaseAddr = reinterpret_cast<uintptr_t>(me32.modBaseAddr);
                        break;
                    }
                } while (Module32Next(hSnap, &me32));
            }
            CloseHandle(hSnap);
        }
        return modBaseAddr;
    }


}