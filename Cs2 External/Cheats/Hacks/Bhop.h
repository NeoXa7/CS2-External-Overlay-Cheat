#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>

VOID Bhop()
{
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		Memory::WriteMemory<int>(CS2::ClientDll + Offsets::dwForceJump, 65537);
		Sleep(10);
		Memory::WriteMemory<int>(CS2::ClientDll + Offsets::dwForceJump, 256);
	}
}