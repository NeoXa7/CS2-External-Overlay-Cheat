#pragma once
#include <Globals/hGlobals.h>
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Readers/Game.h>
#include <Readers/Player.h>

class Bomb
{
public:
	class C4
	{
	public:
		Vector3 GetPlantedC4Position()
		{
			uintptr_t Planted_C4_Node = Memory::ReadMemory<uintptr_t>(game.Planted_C4 + Offsets::m_pGameSceneNode);
			return Memory::ReadMemory<Vector3>(Planted_C4_Node + Offsets::m_vecAbsOrigin);// C4 Position
		}

		Vector3 GetDroppedC4Position()
		{
			uintptr_t Dropped_C4_Node = Memory::ReadMemory<uintptr_t>(game.Weapon_C4 + Offsets::m_pGameSceneNode);
			return Memory::ReadMemory<Vector3>(Dropped_C4_Node + Offsets::m_vecAbsOrigin);// C4 Position
		}

		int GetBombSite()
		{
			return Memory::ReadMemory<int>(game.Planted_C4 + Offsets::m_nBombSite);
		}

		float Get_Distance_From_PlantedC4_To_LocalPlayer()
		{
			return (GetPlantedC4Position() - player.Position).Magnitude(); // In Units;
		}
		
		float Get_Distance_From_DroppedC4_To_LocalPlayer()
		{
			return (GetDroppedC4Position() - player.Position).Magnitude(); // In Units;
		}

	};
	
}; inline Bomb bomb; inline Bomb::C4 c4;
