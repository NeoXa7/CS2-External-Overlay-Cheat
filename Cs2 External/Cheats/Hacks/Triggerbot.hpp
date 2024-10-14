#pragma once
#include <Memory/Memory.hpp>
#include <Inputs/Events.hpp>
#include <Readers/Game.hpp>
#include <Readers/LocalPlayer.hpp>
#include <Utilities/Config.hpp>


VOID TRIGGER_BOT()
{
	if (game.EntityIndex > 0)
	{
		uintptr_t entityListEntry = mem.ReadMemory<uintptr_t>(game.EntityList + 0x8 * (game.EntityIndex >> 9) + 0x10);
		uintptr_t entity = mem.ReadMemory<uintptr_t>(entityListEntry + 120 * (game.EntityIndex & 0x1FF));

		int entityTeam = mem.ReadMemory<int>(entity + Offsets::m_iTeamNum);
		int entityHealth = mem.ReadMemory<int>(entity + Offsets::m_iHealth);

		if (Config::TriggerBot::enableTeamCheck)
		{
			if (entityTeam != player.Team && entityHealth > 0)
			{
				Events::SimulateLMBClick();
				Sleep(100);
			}
		}
		else
		{
			if (entityHealth > 0)
			{
				Events::SimulateLMBClick();
				Sleep(100);
			}
		}
	}
}