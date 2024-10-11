#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>
#include <Readers/Game.h>
#include <Readers/Player.h>

VOID ANTIFLASH()
{
	if (game.FlashDuration > 0)
	{
		Memory::WriteMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime, 0);
	}
}