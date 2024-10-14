#pragma once
#include <Memory/Memory.hpp>
#include <Maths/Vector.hpp>
#include <Globals/Globals.hpp>
#include <Maths/ViewMatrix.hpp>
#include <Readers/Entity.hpp>
#include <Readers/LocalPlayer.hpp>

class Game
{
public:

	uintptr_t EntityList;
	uintptr_t Rules;
	uintptr_t GlobalVars;
	uintptr_t Planted_C4;
	uintptr_t Weapon_C4;
	uintptr_t CameraServices;
	uintptr_t GameModeServer;
	uintptr_t GameMode;

public:

	char MapName[128] = { 0 };
	float FlashDuration;
	float Dist_ETLP;
	int EntityIndex;
	Vector3 ViewAngles;
	view_matrix_t ViewMatrix;
public:

	bool BombPlanted;
	bool BombDropped;
	bool IsBombBeingDefused;
	bool IsWarmupPeriod;
	bool IsTerroristTimeOutActive;
	bool IsCT_TimeOutActive;

public:
	void UpdateGameVars()
	{
		EntityList = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwEntityList);
		Rules = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwGameRules);
		GlobalVars = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwGlobalVars);
		Planted_C4 = mem.ReadMemory<uintptr_t>
			(Planted_C4 = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwPlantedC4)); // Derefrencing Memory;

		Weapon_C4 = mem.ReadMemory<uintptr_t>
			(Weapon_C4 = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwWeaponC4)); // Derefrencing Memory;

		CameraServices = mem.ReadMemory<uintptr_t>(player.localPlayerPawn + Offsets::m_pCameraServices);

		uintptr_t MapNameAddress = mem.ReadMemory<uintptr_t>(CS2::MatchMakingDll + Offsets::dwGameTypes + Offsets::dwGameTypes_mapName + 8);
		mem.ReadArray<char>(MapNameAddress, MapName, sizeof(MapName));

		GameModeServer = mem.ReadMemory<uintptr_t>(CS2::ServerDll + 0x1597E50);
		//GameMode = mem.ReadMemory<uintptr_t>(CS2::MatchMakingDll + Offsets::dwGameTypes + 20);

		IsWarmupPeriod = mem.ReadMemory<bool>(Rules + Offsets::m_bWarmupPeriod);

		BombPlanted = mem.ReadMemory<bool>(Rules + Offsets::m_bBombPlanted);
		BombDropped = mem.ReadMemory<bool>(Rules + Offsets::m_bBombDropped);
		IsBombBeingDefused = mem.ReadMemory<bool>(Planted_C4 + Offsets::m_bBeingDefused);

		FlashDuration = mem.ReadMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);
		EntityIndex = mem.ReadMemory<int>(player.localPlayerPawn + Offsets::m_iIDEntIndex);

		ViewAngles = mem.ReadMemory<Vector3>(CS2::ClientDll + Offsets::dwViewAngles);
		ViewMatrix = mem.ReadMemory<view_matrix_t>(CS2::ClientDll + Offsets::dwViewMatrix);
		Dist_ETLP = (entities->Position - player.Position).Magnitude(); // In Units;
		IsTerroristTimeOutActive = mem.ReadMemory<bool>(Rules + Offsets::m_bTerroristTimeOutActive);
		IsCT_TimeOutActive = mem.ReadMemory<bool>(Rules + Offsets::m_bCTTimeOutActive);
	}
}; inline Game game;