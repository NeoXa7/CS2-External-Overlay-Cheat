#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>
#include <Maths/ViewMatrix.h>
#include <Readers/Entity.h>
#include <Hacks/Utils/GameModes.h>

class Game
{
public:
	uintptr_t EntityList;
	uintptr_t Rules;
	uintptr_t GlobalVars;
	uintptr_t Planted_C4;
	uintptr_t Weapon_C4;
public:
	char MapName[128] = { 0 };
public:
	bool BombPlanted;
	bool BombDropped;
	bool IsBombBeingDefused;
public:
	float FlashDuration;
	int EntityIndex;
public:
	Vector3 ViewAngles;
	view_matrix_t ViewMatrix;
	float Distance_From_LocalPlayer_To_Entities;
public:
	uintptr_t GameServer;
	uintptr_t GameMode;
public:
	bool IsWarmupPeriod;
public:
	void UpdateGameVars()
	{
		EntityList = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwEntityList);
		Rules = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwGameRules);
		GlobalVars = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwGlobalVars);
		Planted_C4 = Memory::ReadMemory<uintptr_t>
			(Planted_C4 = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwPlantedC4)); // Derefrencing Memory;

		Weapon_C4 = Memory::ReadMemory<uintptr_t>
			(Weapon_C4 = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwWeaponC4)); // Derefrencing Memory;

		uintptr_t MapNamePtr = Memory::ReadMemory<uintptr_t>(GlobalVars + 0x1B8);
		Memory::ReadArray<char>(MapNamePtr, MapName, sizeof(MapName));

		GameServer = Memory::ReadMemory<uintptr_t>(CS2::ServerDll + 0x0149E150);
		GameMode = Memory::ReadMemory<uintptr_t>(GameServer + 0x7B8);

		IsWarmupPeriod = Memory::ReadMemory<bool>(Rules + Offsets::m_bWarmupPeriod);

		BombPlanted = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombPlanted);
		BombDropped = Memory::ReadMemory<bool>(Rules + Offsets::m_bBombDropped);
		IsBombBeingDefused = Memory::ReadMemory<bool>(Planted_C4 + Offsets::m_bBeingDefused);

		FlashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);
		EntityIndex = Memory::ReadMemory<int>(player.localPlayerPawn + Offsets::m_iIDEntIndex);

		ViewAngles = Memory::ReadMemory<Vector3>(CS2::ClientDll + Offsets::dwViewAngles);	
		ViewMatrix = Memory::ReadMemory<view_matrix_t>(CS2::ClientDll + Offsets::dwViewMatrix);
		Distance_From_LocalPlayer_To_Entities = (entities->Position - player.Position).Magnitude(); // In Units;
	}

	std::string GetGameModeName() const
	{
		auto it = GameModeNames.find(GameMode);
		if (it != GameModeNames.end())
			return it->second;
		return "<empty>";
	}


}; inline Game game;