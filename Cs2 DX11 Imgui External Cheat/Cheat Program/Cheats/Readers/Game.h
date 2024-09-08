#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>
#include <Maths/ViewMatrix.h>

class Game
{
public:
	uintptr_t EntityList;
	Vector3 ViewAngles;
	uintptr_t Rules;
	bool BombPlanted;
	bool BombDropped;
	int BombSite;
	float FlashDuration;
	view_matrix_t ViewMatrix;

	void UpdateGameVars()
	{
		EntityList = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::dwEntityList);
		ViewAngles = Memory::ReadMemory<Vector3>(CS2::clientAddress + Offsets::dwViewAngles);
		Rules = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::dwGameRules);
		BombPlanted = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombPlanted);
		BombDropped = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombDropped);
		BombSite = Memory::ReadMemory<int>(Rules + Offsets::m_nBombSite);
		FlashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);
		ViewMatrix = Memory::ReadMemory<view_matrix_t>(CS2::clientAddress + Offsets::dwViewMatrix);
	}
}; extern Game game;