#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class LocalPlayer
{
private:
	uintptr_t DW_Sensitivity;
public:
	uintptr_t localPlayerPawn;
	int Team;
	int Health;
	Vector3 Position;
	float Sensitivity;
	bool IsScoped;
	uint32_t IsFiring;

	float AimPunchAngle;
	Vector3 VecViewOffset;
	int fFlag;

	void UpdateLocalPlayer() {
		// privates;
		DW_Sensitivity = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::dwSensitivity);

		// publics;
		localPlayerPawn = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::dwLocalPlayerPawn);
		Team = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iTeamNum);
		Health = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iHealth);
		Position = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vOldOrigin);
		Sensitivity = Memory::ReadMemory<float>(DW_Sensitivity + Offsets::dwSensitivity_sensitivity);
		IsScoped = Memory::ReadMemory<bool>(localPlayerPawn + Offsets::m_bIsScoped);
		IsFiring = Memory::ReadMemory<uint32_t>(localPlayerPawn + Offsets::m_iShotsFired);

		AimPunchAngle = Memory::ReadMemory<float>(localPlayerPawn + Offsets::m_aimPunchAngle);	
		VecViewOffset = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vecViewOffset);	
		fFlag = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_fFlags);	
	}
}; extern LocalPlayer player;
