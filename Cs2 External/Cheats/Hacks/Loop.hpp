#pragma once
#include <Hacks/Aimbot.hpp>
#include <Hacks/Esp.hpp>
#include "Antiflash.hpp"
#include "Rcs.hpp"
#include "Bhop.hpp"
#include "FovChanger.hpp"
#include <Hacks/SensiChanger.hpp>

namespace CHEATS
{
	void ProcessCheatInputs();
	void InitializeBasicCheats();
}

void CHEATS::ProcessCheatInputs()
{
	if (GetAsyncKeyState(VK_F1) & 1) {
		Flags::enableAimbot = !Flags::enableAimbot;
	}

	if (GetAsyncKeyState(VK_F2) & 1) {
		Flags::enableTriggerbot = !Flags::enableTriggerbot;
	}

	if (GetAsyncKeyState(VK_F3) & 1) {
		Flags::enablePlayerEsp = !Flags::enablePlayerEsp;
		Flags::enableC4Esp = !Flags::enableC4Esp;
	}

	if (GetAsyncKeyState(0x56) & 1) {
		Flags::enableTPV = !Flags::enableTPV;
	}
}

void CHEATS::InitializeBasicCheats()
{
	// RCS
	if (Flags::enableRCS)
	{
		STANDALONE_RCS();
	}

	// Antiflash
	if (Flags::enableAntiflash)
	{
		ANTIFLASH();
	}

	// Bunny-Hop
	if (Flags::enableBhop)
	{
		BHOP();
	}

	// Player-Esp
	if (Flags::enablePlayerEsp)
	{
		PLAYER_ESP();
	}

	// Bomb-Esp
	if (Flags::enableC4Esp)
	{
		C4_ESP();
	}

	// World_Esp
	if (Flags::enableWorldEsp)
	{
		ITEM_ESP();
	}

	// Fov-Changer
	if (Flags::enableFovChanger)
	{
		ChangeFoV();
	}

	// Aimbot
	if (Flags::enableAimbot && Config::Aimbot::enableHotKey) // if hotkey set to true
	{
		if (GetAsyncKeyState(Config::Aimbot::currentKey))
			aimbot.RUN();
	}
	else if (Flags::enableAimbot) // if not set to true;
	{
		aimbot.RUN();
	}

	if (Flags::enableSensiChanger)
	{
		player.UpdateLocalPlayer();
		ChangeSensi();
	}


	//// NoSky
	//if (Flags::enableNoSky)
	//{
	//	ENABLE_NO_SKY();
	//}
	//else
	//{
	//	DISABLE_NO_SKY();
	//}

	//// NoSpread
	//if (Flags::enableNoSpread)
	//{
	//	ENABLE_SV_CHEATS();
	//	ENABLE_NO_SPREAD();
	//}
	//else
	//{
	//	DISABLE_NO_SPREAD();
	//}

	//// Third-Person-Perspective
	//if (Flags::enableTPV)
	//{
	//	ENABLE_SV_CHEATS();
	//	GET_THIRD_PERSON_PERSPECTIVE();
	//}
	//else
	//{
	//	DELETE_TPP();
	//}
	//	

	//// Map-View
	//if (Flags::enableMapView)
	//{
	//	ENABLE_MAP_VIEW();
	//}
	//else
	//{
	//	DISABLE_MAP_VIEW();
	//}
}