#pragma once
#include <Memory/hMemory.h>
#include <Globals/hGlobals.h>
#include <Hacks/Utils/Config.h>
#include <Readers/Game.h>
#include <Readers/Player.h>

VOID ChangeFoV()
{
	UINT desiredFov = (UINT)Config::Fov::Default;
	UINT currentFov = Memory::ReadMemory<UINT>(game.CameraServices + Offsets::m_iFOV);

	if (!player.IsScoped && currentFov != desiredFov)
	{
		Memory::WriteMemory<UINT>(game.CameraServices + Offsets::m_iFOV, desiredFov);
	}
}


VOID ResetFoV()
{
	Memory::WriteMemory<UINT>(game.CameraServices + Offsets::m_iFOV, Config::Fov::Default);
}