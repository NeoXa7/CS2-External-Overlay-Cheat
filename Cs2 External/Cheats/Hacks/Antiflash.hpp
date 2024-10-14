#pragma once
#include <Memory/Memory.hpp>
#include <Globals/Globals.hpp>
#include <Readers/Game.hpp>
#include <Readers/LocalPlayer.hpp>

VOID ANTIFLASH()
{
	if (game.FlashDuration > 0)
	{
		mem.WriteMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime, 0);
	}
}