#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class Entities
{
public:
	int Health;
	bool IsSpotted;
	int EntityIndex;

	void UpdateEntities()
	{
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x10);

		for (int i = 1; i < 64; i++)
		{
			if (listEntry == 0)
				continue;

			uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + i * 0x78);
			if (currentController == 0)
				continue;

			int pawnHandle = Memory::ReadMemory<int>(currentController + Offsets::m_hPlayerPawn);
			if (pawnHandle == 0)
				continue;

			uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
			if (listEntry2 == 0)
				continue;

			uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
			if (currentPawn == 0 || currentPawn == player.localPlayerPawn)
				continue;

			Health = Memory::ReadMemory<int>(currentPawn + Offsets::m_iHealth);
			IsSpotted = Memory::ReadMemory<bool>(currentPawn + Offsets::m_entitySpottedState + Offsets::m_bSpotted);
			EntityIndex = Memory::ReadMemory<int>(player.localPlayerPawn + Offsets::m_iIDEntIndex);
		}
	}

}; extern Entities entities;