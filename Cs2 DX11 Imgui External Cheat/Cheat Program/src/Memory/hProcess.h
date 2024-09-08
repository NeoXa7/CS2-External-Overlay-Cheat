#pragma once

#include "../../src/Globals/hIncludes.h"
#include "hMemory.h"

using Module = const wchar_t*;
using Process = const wchar_t*;

class ProcessManager
{
public:
	// getting process infos; 
	static DWORD GetProcessID(const wchar_t* processName);
	static uintptr_t GetModuleBaseAddress(DWORD processId, const wchar_t* ModuleTarget);

    // checking process infos; 
    static void CheckProcess(DWORD procID, const wchar_t* processName);
    static void CheckBaseAddress(uintptr_t baseAddress);
};


// getting process infos; 
DWORD ProcessManager::GetProcessID(const wchar_t* processName) {
    DWORD processID = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W processEntry; // Use PROCESSENTRY32W for wide characters
        processEntry.dwSize = sizeof(PROCESSENTRY32W);
        if (Process32FirstW(snapshot, &processEntry)) {
            do {
                if (Memory::iequals(processEntry.szExeFile, processName)) {
                    processID = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snapshot, &processEntry));
        }
        CloseHandle(snapshot);
    }
    return processID;
}

uintptr_t ProcessManager::GetModuleBaseAddress(DWORD processId, const wchar_t* ModuleTarget) {
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshotHandle == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    MODULEENTRY32W moduleEntry = { };
    moduleEntry.dwSize = sizeof(MODULEENTRY32W);

    if (Module32FirstW(snapshotHandle, &moduleEntry)) {

        do {

            if (_wcsicmp(moduleEntry.szModule, ModuleTarget) == 0) {
                CloseHandle(snapshotHandle);
                return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
        } while (Module32NextW(snapshotHandle, &moduleEntry));
    }
    CloseHandle(snapshotHandle);
    return NULL;
}


// checking process info; 
void ProcessManager::CheckProcess(DWORD procID, const wchar_t* processName)
{
    if (procID == 0)
    {
        wcerr << "Process " << processName << " Not Found\n";
        Sleep(400);
    }
    else if (procID > 0)
    {
        wcout << "Process " << processName << " Found " << "With ProcessID : " << procID << '\n';
        Sleep(400);
    }
}

void ProcessManager::CheckBaseAddress(uintptr_t baseAddress)
{
    if (baseAddress == 0)
    {
        wcerr << "Process Base Address : " << baseAddress << '\n';
        Sleep(400);
    }
    else if (baseAddress > 0)
    {
        wcout << "Process Base Address : " << baseAddress << '\n';
        Sleep(400);
    }
    system("cls");
}