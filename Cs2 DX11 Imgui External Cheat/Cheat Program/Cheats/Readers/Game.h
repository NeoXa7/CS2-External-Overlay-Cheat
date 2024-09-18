#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>
#include <Maths/ViewMatrix.h>
#include <Readers/Entity.h>

class Game
{
public:
	uintptr_t EntityList;
	uintptr_t Rules;
public:
	char MapName[128] = { 0 };
public:
	bool BombPlanted;
	bool BombDropped;
	int BombSite;
	bool IsBombDefusing;
public:
	float FlashDuration;
	int EntityIndex;
public:
	Vector3 ViewAngles;
	view_matrix_t ViewMatrix;
	float DistanceFromLocalPlayerToEntities;
public:
	void UpdateGameVars()
	{
		EntityList = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwEntityList);
		Rules = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwGameRules);

		uintptr_t MapNameAddress = Memory::ReadMemory<uintptr_t>(CS2::MatchMakingDll + Offsets::dwGameTypes + Offsets::dwGameTypes_mapName + 8);
		Memory::ReadArray<char>(MapNameAddress, MapName, sizeof(MapName));

		BombPlanted = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombPlanted);
		BombDropped = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombDropped);
		BombSite = Memory::ReadMemory<int>(Rules + Offsets::m_nBombSite);

		FlashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);
		EntityIndex = Memory::ReadMemory<int>(player.localPlayerPawn + Offsets::m_iIDEntIndex);

		ViewAngles = Memory::ReadMemory<Vector3>(CS2::ClientDll + Offsets::dwViewAngles);	
		ViewMatrix = Memory::ReadMemory<view_matrix_t>(CS2::ClientDll + Offsets::dwViewMatrix);
		DistanceFromLocalPlayerToEntities = (entities->Position - player.Position).Magnitude();
	}
}; inline Game game;