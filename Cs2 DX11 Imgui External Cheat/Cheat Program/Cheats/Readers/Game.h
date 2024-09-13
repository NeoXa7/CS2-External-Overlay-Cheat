#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>
#include <Maths/ViewMatrix.h>

class Game
{
public:
	uintptr_t EntityList;
	uintptr_t Rules;
public:
	char MapName[256] = { 0 };
public:
	bool BombPlanted;
	bool BombDropped;
	int BombSite;
	bool IsBombDefusing;
public:
	float FlashDuration;
public:
	Vector3 ViewAngles;
	view_matrix_t ViewMatrix;
public:
	void UpdateGameVars()
	{
		EntityList = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwEntityList);
		Rules = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwGameRules);

		BombPlanted = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombPlanted);
		BombDropped = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombDropped);
		BombSite = Memory::ReadMemory<int>(Rules + Offsets::m_nBombSite);

		FlashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);

		ViewAngles = Memory::ReadMemory<Vector3>(CS2::ClientDll + Offsets::dwViewAngles);	
		ViewMatrix = Memory::ReadMemory<view_matrix_t>(CS2::ClientDll + Offsets::dwViewMatrix);
	}
}; inline Game game;