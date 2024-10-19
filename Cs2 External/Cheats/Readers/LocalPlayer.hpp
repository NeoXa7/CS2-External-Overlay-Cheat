#pragma once
#include <Memory/Memory.hpp>
#include <Maths/Vector.hpp>
#include <Globals/Globals.hpp>

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
	uint32_t Ping;
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
		localPlayerPawn = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwLocalPlayerPawn);
		LocalPlayerController = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwLocalPlayerController);

		DW_Sensitivity = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwSensitivity); // private
		NameAddress = mem.ReadMemory<uintptr_t>(LocalPlayerController + Offsets::m_sSanitizedPlayerName); // private

		Team = mem.ReadMemory<int>(localPlayerPawn + Offsets::m_iTeamNum);
		Health = mem.ReadMemory<int>(localPlayerPawn + Offsets::m_iHealth);
		Armor = mem.ReadMemory<int>(localPlayerPawn + Offsets::m_ArmorValue);
		mem.ReadArray<char>(NameAddress, Name, sizeof(Name)); // Name
		Ping = mem.ReadMemory<uint32_t>(LocalPlayerController + Offsets::m_iPing);

		Sensitivity = mem.ReadMemory<float>(DW_Sensitivity + Offsets::dwSensitivity_sensitivity);
		Velocity = mem.ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vecAbsVelocity);
		IsScoped = mem.ReadMemory<bool>(localPlayerPawn + Offsets::m_bIsScoped);
		IsFiring = mem.ReadMemory<uint32_t>(localPlayerPawn + Offsets::m_iShotsFired);

		Position = mem.ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vOldOrigin);
		AimPunchAngle = mem.ReadMemory<float>(localPlayerPawn + Offsets::m_aimPunchAngle);
		VecViewOffset = mem.ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vecViewOffset);
	}

}; inline LocalPlayer player;