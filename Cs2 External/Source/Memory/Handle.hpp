/*This Handle Code just make sure that cs2 is open from steam and if its open from steam then it opens handle directly from the cs2 process . (Dont get confused lol Its never used in the source code)*/
#include <Globals/Includes.hpp>

// Function to find Steam's process handle
HANDLE GetProcessHandle(std::wstring PROCESS_HANDLE_NAME)
{
    HANDLE hProcess = NULL;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcess == INVALID_HANDLE_VALUE)
        return NULL;

    if (Process32First(hProcess, &pe32))
    {
        do
        {
            if (std::wstring(pe32.szExeFile) == PROCESS_HANDLE_NAME)
            {
                CloseHandle(hProcess);
                return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
            }
        } while (Process32Next(hProcess, &pe32));
    }

    CloseHandle(hProcess);
    return NULL;
}

// Function to get the CS2 process handle based on Steam process
HANDLE GetCS2HandleFrom(HANDLE TRUSTED_SOURCE_HANDLE)
{
    HANDLE cs2Handle = NULL;
    DWORD ParentProcID = GetProcessId(TRUSTED_SOURCE_HANDLE);

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcess == INVALID_HANDLE_VALUE)
        return NULL;

    if (Process32First(hProcess, &pe32))
    {
        do
        {
            // Check if the process is CS2 and if its parent is Steam
            if (std::wstring(pe32.szExeFile) == L"cs2.exe")  // Make sure to check the actual CS2 executable name
            {
                // Check the parent process ID (PID) to confirm it's the parent of chosen trusted process
                if (pe32.th32ParentProcessID == ParentProcID)
                {
                    cs2Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
                    break;  // We found CS2, no need to continue searching
                }
            }
        } while (Process32Next(hProcess, &pe32));
    }

    CloseHandle(hProcess);
    return cs2Handle;
}
