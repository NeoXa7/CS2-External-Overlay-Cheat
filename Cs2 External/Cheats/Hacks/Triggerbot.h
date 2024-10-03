#pragma once
#include <Memory/hMemory.h>
#include <Inputs/Events.h>
#include <Readers/Game.h>
#include <Readers/Player.h>
#include <Hacks/Utils/Config.h>


VOID TriggerBot()
{
	if (game.EntityIndex > 0)
	{
		uintptr_t entityListEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * (game.EntityIndex >> 9) + 0x10);
		uintptr_t entity = Memory::ReadMemory<uintptr_t>(entityListEntry + 120 * (game.EntityIndex & 0x1FF));

		int entityTeam = Memory::ReadMemory<int>(entity + Offsets::m_iTeamNum);
		int entityHealth = Memory::ReadMemory<int>(entity + Offsets::m_iHealth);

		if (Config::TriggerBot::enableTeamCheck)
		{
			if (entityTeam != player.Team && entityHealth > 0)
			{
				MouseEvents::SimulateLMBClick();
				Sleep(100);
			}
		}
		else
		{
			if (entityHealth > 0)
			{
				MouseEvents::SimulateLMBClick();
				Sleep(100);
			}
		}
	}
}
