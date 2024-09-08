#pragma once
#include "../../src/Globals/hIncludes.h"

#define WIN32_LEAN_AND_MEAN

using namespace std;

using Process = const wchar_t*;
using dwVector = vector<DWORD>;

class Memory
{
public:
	static HANDLE processHandle;

	// comparing method;
	static bool iequals(const wstring& a, const wstring& b);

	// reading and writing memory to the process;
	template <typename type>
	static type ReadMemory(uintptr_t address);

	template <typename type>
	static bool WriteMemory(uintptr_t address, const type& value);

	// finding and getting dynamic addresses and value of a pointer;
	static uintptr_t GetDynamic(uintptr_t initialAddress, const vector<DWORD>& offsets);

	static DWORD ReadMultiLevelPointer(uintptr_t gameBaseAddr, DWORD address, vector<DWORD> offsets);

	// some more memory functions;
	template <typename type>
	static type IncrementValue(uintptr_t address, const type& incrementValue);

	template <typename type>
	static type DecrementValue(uintptr_t address, const type& decrementValue);
};

// reading and writing memory to the process;

template <typename type>
type Memory::ReadMemory(uintptr_t address) {
	type value = {};
	SIZE_T bytesRead;
	if (!ReadProcessMemory(processHandle, (LPCVOID)(address), &value, sizeof(type), &bytesRead)) {
		cerr << "Could not read memory at address " << hex << address << ". Error: " << GetLastError() << endl;
		return value;  // Return the default value instead of false
	}

	if (bytesRead != sizeof(type)) {
		cerr << "Unexpected number of bytes read. Expected: " << sizeof(type) << ", Actual: " << bytesRead << endl;
		return value;  // Return the default value instead of false
	}

	return value;
}

template <typename type>
bool Memory::WriteMemory(uintptr_t address, const type& value) {
	SIZE_T bytesWritten;
	if (!WriteProcessMemory(processHandle, (LPVOID)(address), &value, sizeof(type), &bytesWritten)) {
		cerr << "Could not write memory at address " << hex << address << ". Error: " << GetLastError() << endl;
		return false;
	}

	if (bytesWritten != sizeof(type)) {
		cerr << "Unexpected number of bytes written. Expected: " << sizeof(type) << ", Actual: " << bytesWritten << endl;
		return false;
	}
}

// some more memory functions;

template <typename type>
type Memory::IncrementValue(uintptr_t address, const type& incrementValue)
{
	type currentValue = Memory::ReadMemory<type>(address);
	return Memory::WriteMemory<type>(address, currentValue + incrementValue);
}

template <typename type>
type Memory::DecrementValue(uintptr_t address, const type& decrementValue)
{
	type currentValue = Memory::ReadMemory<type>(address);
	return Memory::WriteMemory<type>(address, currentValue - decrementValue);
}
