#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>

VOID ENABLE_SV_CHEATS()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A173C8) + 0x40, true);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x015DDF18) + 0x40, true);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::Engine2Dll + 0x0059A9A8) + 0x40, true);
}

VOID DISABLE_SV_CHEATS()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A173C8) + 0x40, false);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x015DDF18) + 0x40, false);
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::Engine2Dll + 0x0059A9A8) + 0x40, false);
}

