#pragma once
#include <Hacks/Antiflash.h>
#include <Hacks/Aimbot.h>
#include <Hacks/Bhop.h>
#include <Hacks/Esp.h>
#include <Hacks/Glow.h>
#include <Hacks/Rcs.h>
#include <Hacks/Triggerbot.h>

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
}

void CHEATS::InitializeBasicCheats()
{
	if (Flags::enableRCS)
	{
		StandaloneRCS();
	}

	if (Flags::enableAntiflash)
	{
		Antiflash();
	}

	if (Flags::enableBhop)
	{
		Bhop();
	}	

	if (Flags::enablePlayerEsp)
	{
		PlayerEsp();
	}

	if (Flags::enableC4Esp)
	{
		C4_Esp();
	}

	if (Flags::enableWorldEsp)
	{
		Item_Esp();
	}
	
	if (Flags::enableAimbot && Config::Aimbot::ShowFovCircle)
	{
		DrawUtils::DrawAimFovCircle();
	}

	if (Config::Game::DrawCrosshair)
	{
		DrawUtils::DrawCrosshair(Config::Game::CrosshairSize, Config::Game::CrosshairColor);
	}

	if (Flags::enableAimbot && Config::Aimbot::enableHotKey) // if hotkey set to true
	{
		if(GetAsyncKeyState(Config::Aimbot::AB_KEYCODE))
			aimbot.BeginAimbot();
	}
	else if(Flags::enableAimbot) // if not set to true;
	{
		aimbot.BeginAimbot();
	}
}