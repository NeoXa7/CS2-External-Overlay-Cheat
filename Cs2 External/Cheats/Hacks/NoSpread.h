#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>

VOID ENABLE_NO_SPREAD()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x019BEE48) + 0x40, true);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x015A2690) + 0x40, true);

	auto seed = 0.0f;
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x019BEE58) + 0x40, seed);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x015A26A0) + 0x40, seed);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x019BEE38) + 0x40, seed);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x015A2680) + 0x40, seed);
}

VOID DISABLE_NO_SPREAD()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x019BEE48) + 0x40, false);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x015A2690) + 0x40, false);
}