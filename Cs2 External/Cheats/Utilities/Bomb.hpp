#pragma once
#include <Globals/Globals.hpp>
#include <Memory/Memory.hpp>
#include <Maths/Vector.hpp>
#include <Readers/Game.hpp>
#include <Readers/LocalPlayer.hpp>

class C4
{
public:
	Vector3 GetPlantedC4Position()
	{
		uintptr_t Planted_C4_Node = mem.ReadMemory<uintptr_t>(game.Planted_C4 + Offsets::m_pGameSceneNode);
		return mem.ReadMemory<Vector3>(Planted_C4_Node + Offsets::m_vecAbsOrigin);// C4 Position
	}

	Vector3 GetDroppedC4Position()
	{
		uintptr_t Dropped_C4_Node = mem.ReadMemory<uintptr_t>(game.Weapon_C4 + Offsets::m_pGameSceneNode);
		return mem.ReadMemory<Vector3>(Dropped_C4_Node + Offsets::m_vecAbsOrigin);// C4 Position
	}

	int GetBombSite()
	{
		return mem.ReadMemory<int>(game.Planted_C4 + Offsets::m_nBombSite);
	}

	float Get_Distance_From_PlantedC4_To_LocalPlayer()
	{
		return (GetPlantedC4Position() - player.Position).Magnitude(); // In Units;
	}

	float Get_Distance_From_DroppedC4_To_LocalPlayer()
	{
		return (GetDroppedC4Position() - player.Position).Magnitude(); // In Units;
	}

}; inline C4 c4;