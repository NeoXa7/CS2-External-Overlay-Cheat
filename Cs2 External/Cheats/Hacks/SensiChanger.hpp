#pragma once
#include <Memory/Memory.hpp>
#include <Globals/Globals.hpp>
#include <Utilities/Config.hpp>

VOID ChangeSensi()
{
	uintptr_t DW_Sensitivity = mem.ReadMemory<uintptr_t>(CS2::ClientDll + Offsets::dwSensitivity);
	mem.WriteMemory<float>(DW_Sensitivity + Offsets::dwSensitivity_sensitivity, Config::Game::Sensitivity);
}