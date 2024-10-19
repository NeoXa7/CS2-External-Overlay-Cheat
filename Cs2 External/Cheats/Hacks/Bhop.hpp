#pragma once
#include <Memory/Memory.hpp>
#include <Globals/Globals.hpp>

VOID BHOP()
{
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		mem.WriteMemory<int>(CS2::ClientDll + Offsets::dwForceJump, 65537);
		Sleep(10);
		mem.WriteMemory<int>(CS2::ClientDll + Offsets::dwForceJump, 256);
	}
}