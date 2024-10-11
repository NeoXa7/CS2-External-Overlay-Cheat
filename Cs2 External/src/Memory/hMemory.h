#pragma once
#include "../../src/Globals/hIncludes.h"

#define WIN32_LEAN_AND_MEAN

using namespace std;

class Memory
{
public:
	static HANDLE ProcessHandle;

	// comparing method;
	static bool iequals(const wstring& a, const wstring& b);

	// reading and writing memory to the process;
	template <typename type>
	static type ReadMemory(uintptr_t address);

	template <typename type>
	static bool WriteMemory(uintptr_t address, const type& value);

	// finding and getting dynamic addresses and value of a pointer;
	template <typename type>
	static type GetDynamic(type initialAddress, const vector<DWORD>& offsets);

	template <typename type>
	static type ReadMultiLevelPointer(type gameBaseAddr, type address, vector<type> offsets);

	// some more memory functions;
	template <typename type>
	static type IncrementValue(uintptr_t address, const type& incrementValue);

	template <typename type>
	static type DecrementValue(uintptr_t address, const type& decrementValue);

	template <typename type>
	static bool ReadArray(uintptr_t address, type* buffer, size_t size);

};

// reading and writing memory to the process;

template <typename type>
type Memory::ReadMemory(uintptr_t address) {
	type value = {};
	SIZE_T bytesRead;
	if (!ReadProcessMemory(ProcessHandle, (LPCVOID)(address), &value, sizeof(type), &bytesRead)) {
		//cerr << "Could not read memory at address " << hex << address << ". Error: " << GetLastError() << endl;
		return value;
	}

	if (bytesRead != sizeof(type)) {
		//cerr << "Unexpected number of bytes read. Expected: " << sizeof(type) << ", Actual: " << bytesRead << endl;
		return value;  // Return the default value instead of false
	}

	return value;
}

template <typename type>
bool Memory::WriteMemory(uintptr_t address, const type& value) {
	SIZE_T bytesWritten;
	if (!WriteProcessMemory(ProcessHandle, (LPVOID)(address), &value, sizeof(type), &bytesWritten)) {
		//cerr << "Could not write memory at address " << hex << address << ". Error: " << GetLastError() << endl;
		return false;
	}

	if (bytesWritten != sizeof(type)) {
		//cerr << "Unexpected number of bytes written. Expected: " << sizeof(type) << ", Actual: " << bytesWritten << endl;
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

template <typename type>
bool Memory::ReadArray(uintptr_t address, type* buffer, size_t size) {
	SIZE_T bytesRead;
	if (!ReadProcessMemory(ProcessHandle, (LPCVOID)(address), buffer, size, &bytesRead)) {
		//cerr << "Could not read array at address " << hex << address << ". Error: " << GetLastError() << endl;
		return false;
	}
	return bytesRead == size;
}

