#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class LocalPlayer
{
public: // Pawn Address and Controller
	uintptr_t localPlayerPawn;
	uintptr_t LocalPlayerController;
private:
	uintptr_t DW_Sensitivity;
	uintptr_t NameAddress;
public:
	int Team;
	int Health;
	int Armor;
	char Name[128] = { 0 };
public:
	float Sensitivity;
	Vector3 Velocity;
	bool IsScoped;
	uint32_t IsFiring;
	bool IsCrouched;
public:
	Vector3 Position;
	float AimPunchAngle;
	Vector3 VecViewOffset;
public:

	void UpdateLocalPlayer() {
		localPlayerPawn = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwLocalPlayerPawn);
		LocalPlayerController = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwLocalPlayerController);

		DW_Sensitivity = Memory::ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwSensitivity); // private
		NameAddress = Memory::ReadMemory<uintptr_t>(LocalPlayerController + Offsets::m_sSanitizedPlayerName); // private

		Team = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iTeamNum);
		Health = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iHealth);
		Armor = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_ArmorValue);
		Memory::ReadArray<char>(NameAddress, Name, sizeof(Name)); // Name

		Sensitivity = Memory::ReadMemory<float>(DW_Sensitivity + Offsets::dwSensitivity_sensitivity);
		Velocity = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vecAbsVelocity);
		IsScoped = Memory::ReadMemory<bool>(localPlayerPawn + Offsets::m_bIsScoped);
		IsFiring = Memory::ReadMemory<uint32_t>(localPlayerPawn + Offsets::m_iShotsFired);	

		Position = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vOldOrigin);
		AimPunchAngle = Memory::ReadMemory<float>(localPlayerPawn + Offsets::m_aimPunchAngle);	
		VecViewOffset = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vecViewOffset);		
	}

}; inline LocalPlayer player;
