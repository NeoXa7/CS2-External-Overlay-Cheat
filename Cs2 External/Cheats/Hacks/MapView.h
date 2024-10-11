#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>

VOID ENABLE_MAP_VIEW()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A184C8) + 0x40, 1);
	Memory::WriteMemory<int>(CS2::ClientDll + 0x1A27AD0, 256);
	Memory::WriteMemory<float>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A184F8) + 0x40, 25000.f);
}

VOID DISABLE_MAP_VIEW()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A184C8) + 0x40, 0);
	Memory::WriteMemory<float>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A184F8) + 0x40, 2.f);
	Memory::WriteMemory<bool>(CS2::ClientDll + 0x1A18CA8, 0);
}