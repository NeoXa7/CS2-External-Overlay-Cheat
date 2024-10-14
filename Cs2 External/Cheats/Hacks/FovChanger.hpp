#pragma once
#include <Memory/Memory.hpp>
#include <Globals/Globals.hpp>
#include <Utilities/Config.hpp>
#include <Readers/Game.hpp>
#include <Readers/LocalPlayer.hpp>

VOID ChangeFoV()
{
	UINT desiredFov = (UINT)Config::Fov::Default;
	UINT currentFov = mem.ReadMemory<UINT>(game.CameraServices + Offsets::m_iFOV);

	if (!player.IsScoped && currentFov != desiredFov)
	{
		mem.WriteMemory<UINT>(game.CameraServices + Offsets::m_iFOV, desiredFov);
	}
}


VOID ResetFoV()
{
	mem.WriteMemory<UINT>(game.CameraServices + Offsets::m_iFOV, Config::Fov::Default);
}