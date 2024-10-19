#pragma once
#include <Globals/Includes.hpp>

#define WIN32_LEAN_AND_MEAN

using namespace std;
class Memory
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
	static HANDLE ProcessHandle;

	template <typename type>
	inline type ReadMemory(uintptr_t address) {
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
	inline bool WriteMemory(uintptr_t address, const type& value) {
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

	template <typename type>
	inline bool ReadArray(uintptr_t address, type* buffer, size_t size) {
		SIZE_T bytesRead;
		if (!ReadProcessMemory(ProcessHandle, (LPCVOID)(address), buffer, size, &bytesRead)) {
			//cerr << "Could not read array at address " << hex << address << ". Error: " << GetLastError() << endl;
			return false;
		}
		return bytesRead == size;
	}

	template <typename type>
	inline type GetDynamic(type initialAddress, const vector<DWORD>& offsets) {
		uintptr_t addr = initialAddress;
		for (unsigned int i = 0; i < offsets.size(); ++i) {
			if (!ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, sizeof(addr), 0)) {
				//   cerr << "Failed to read memory at address " << hex << addr << ". Error: " << GetLastError() << dec << endl;
				return 0; // Return 0 on failure
			}
			addr += offsets[i];
		}
		return addr;
	}

	template <typename type>
	inline type ReadMultiLevelPointer(type gameBaseAddr, type address, vector<type> offsets)
	{

		if (ProcessHandle == INVALID_HANDLE_VALUE || ProcessHandle == NULL) {
			// Handle error opening process
		}

		DWORD offset_null = 0;
		ReadProcessMemory(ProcessHandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
		DWORD pointeraddress = offset_null; // the address we need

		for (size_t i = 0; i < offsets.size() - 1; i++) {
			ReadProcessMemory(ProcessHandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
		}

		CloseHandle(ProcessHandle); // Close process handle when done
		return pointeraddress + offsets.at(offsets.size() - 1); // adding the last offset
	}

	template <typename type>
	inline type IncrementValue(uintptr_t address, const type& incrementValue)
	{
		type currentValue = Memory::ReadMemory<type>(address);
		return Memory::WriteMemory<type>(address, currentValue + incrementValue);
	}

	template <typename type>
	inline type DecrementValue(uintptr_t address, const type& decrementValue)
	{
		type currentValue = Memory::ReadMemory<type>(address);
		return Memory::WriteMemory<type>(address, currentValue - decrementValue);
	}
}; inline Memory mem;