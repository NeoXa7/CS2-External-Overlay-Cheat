#include "hMemory.h"

// comparing method;
bool Memory::iequals(const wstring& a, const wstring& b) {
    if (a.size() != b.size()) {
        return false;
    }
    return equal(a.begin(), a.end(), b.begin(), b.end(), [](wchar_t a, wchar_t b) {
        return towlower(a) == towlower(b);
        });
}


// finding and getting dynamic addresses and value of a pointer;

template <typename type>
type Memory::GetDynamic(type initialAddress, const vector<DWORD>& offsets) {
    uintptr_t addr = initialAddress;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        if (!ReadProcessMemory(processHandle, (BYTE*)addr, &addr, sizeof(addr), 0)) {
            cerr << "Failed to read memory at address " << hex << addr << ". Error: " << GetLastError() << dec << endl;
            return 0; // Return 0 on failure
        }
        addr += offsets[i];
    }
    return addr;
}


// Read Multi Level Pointer;
template <typename type>
type Memory::ReadMultiLevelPointer(type gameBaseAddr, type address, vector<type> offsets)
{

    if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL) {
        // Handle error opening process
    }

    DWORD offset_null = 0;
    ReadProcessMemory(processHandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null; // the address we need

    for (size_t i = 0; i < offsets.size() - 1; i++) {
        ReadProcessMemory(processHandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }

    CloseHandle(processHandle); // Close process handle when done
    return pointeraddress + offsets.at(offsets.size() - 1); // adding the last offset
}