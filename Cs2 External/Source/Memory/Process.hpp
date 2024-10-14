#pragma once

#include <Globals/Includes.hpp>

using namespace std;
using Module = const wchar_t*;
using Process = const wchar_t*;

class ProcessManager
{
private:
    inline bool iequals(const wstring& a, const wstring& b) {
        if (a.size() != b.size()) {
            return false;
        }
        return equal(a.begin(), a.end(), b.begin(), b.end(), [](wchar_t a, wchar_t b) {
            return towlower(a) == towlower(b);
            });
    }
public:
    inline DWORD GetProcessID(Process processName)
    {
        DWORD processID = 0;
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32W processEntry; // Use PROCESSENTRY32W for wide characters
            processEntry.dwSize = sizeof(PROCESSENTRY32W);
            if (Process32FirstW(snapshot, &processEntry)) {
                do {
                    if (iequals(processEntry.szExeFile, processName)) {
                        processID = processEntry.th32ProcessID;
                        break;
                    }
                } while (Process32NextW(snapshot, &processEntry));
            }
            CloseHandle(snapshot);
        }
        return processID;
    }

    inline uintptr_t GetModuleBaseAddress(DWORD processId, Module ModuleTarget)
    {
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

    inline bool IsProcessRunning(DWORD processID)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        if (hProcess == NULL) {
            return false; // Process handle couldn't be obtained, possibly not running
        }

        DWORD exitCode;
        if (GetExitCodeProcess(hProcess, &exitCode)) {
            CloseHandle(hProcess);
            return exitCode == STILL_ACTIVE;
        }
        else {
            CloseHandle(hProcess);
            return false; // Could not get exit code, assume process not running
        }
    }

}; inline ProcessManager PM;