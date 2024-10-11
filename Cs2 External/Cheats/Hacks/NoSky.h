#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>

VOID ENABLE_NO_SKY()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A12408) + 0xFA0, true);
}

VOID DISABLE_NO_SKY()
{
	Memory::WriteMemory<bool>(Memory::ReadMemory<uintptr_t>(CS2::ClientDll + 0x01A12408) + 0xFA0, false);
}