#pragma once
#include <Memory/hMemory.h>
#include <Inputs/Events.h>
#include <Readers/Game.h>
#include <Readers/Player.h>
#include <Hacks/Config.h>
#include "Esp.h"
#include <Maths/WorldToScreen.h>

Game game;
LocalPlayer player;
Entities entities;

namespace Cheats
{
	namespace Safe_Cheats // This namespace Includes cheats that doesn't writes to memory which is ban free;
	{
		void TriggerBot();
		void StandaloneRCS();
		void Esp();
	}

	namespace Risky_Cheats // This namespace Includes cheats that writes memory which may lead to game ban;
	{
		void Bhop();
		void Antiflash();
		void RadarHack();
		void GlowHack(DWORD64 COLOR);
		void Aimbot();
	}

	void ProcessCheatInputs();
	void InitializeBasicCheats();
}

// Safe Hacks;

void Cheats::Safe_Cheats::TriggerBot()
{
	if (entities.EntityIndex > 0)
	{
		uintptr_t entityListEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * (entities.EntityIndex >> 9) + 0x10);
		uintptr_t entity = Memory::ReadMemory<uintptr_t>(entityListEntry + 120 * (entities.EntityIndex & 0x1FF));

		int entityTeam = Memory::ReadMemory<int>(entity + Offsets::m_iTeamNum);
		int entityHealth = Memory::ReadMemory<int>(entity + Offsets::m_iHealth);

		if (Config::TriggerBot::enableTeamCheck)
		{
			if (entityTeam != player.Team && entityHealth > 0)
			{
				MouseEvents::SimulateLMBClick();
				Sleep(100);
			}
		}
		else
		{
			if (entityHealth > 0)
			{
				MouseEvents::SimulateLMBClick();
				Sleep(100);
			}
		}
	}
}

void Cheats::Safe_Cheats::StandaloneRCS()
{
	float aimPunch_x = player.AimPunchAngle;
	float aimPunch_y = Memory::ReadMemory<float>(player.localPlayerPawn + player.AimPunchAngle + 0x4);
	if (player.IsFiring > 1)
	{
		auto delta_x = (aimPunch_x - Config::RCS::oldPunch_x) * -1.0;
		auto delta_y = (aimPunch_y - Config::RCS::oldPunch_y) * -1.0;
		auto mouse_x = int((delta_y * 2.0 / player.Sensitivity) / -0.022);
		auto mouse_y = int((delta_x * 2.0 / player.Sensitivity) / 0.022);

		MouseEvents::SimulateMouseMove(mouse_x, mouse_y);
		Config::RCS::oldPunch_x = aimPunch_x;
		Config::RCS::oldPunch_y = aimPunch_y;
	}
	else
	{
		Config::RCS::oldPunch_x = aimPunch_x; // 0
		Config::RCS::oldPunch_y = aimPunch_y; // 0
	}
}

void Cheats::Safe_Cheats::Esp()
{
	for (int i = 0; i < 64; i++)
	{
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!listEntry)
			continue;

		uintptr_t c_player = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
		if (!c_player)
			continue;

		uint32_t playerPawn = Memory::ReadMemory<uint32_t>(c_player + Offsets::m_hPlayerPawn);

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
		if (!listEntry2)
			continue;

		uintptr_t pCSPlayerPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (playerPawn & 0x1FF));
		if (!pCSPlayerPawn)
			continue;

		int health = Memory::ReadMemory<int>(pCSPlayerPawn + Offsets::m_iHealth);
		if (health <= 0 || health > 100)
			continue;

		if (pCSPlayerPawn == player.localPlayerPawn)
			continue;

		if (!Config::Esp::enableEspTeam)
		{
			if (player.Team == Memory::ReadMemory<int>(pCSPlayerPawn + Offsets::m_iTeamNum))
				continue;
		}

		Vector3 playerPosition = Memory::ReadMemory<Vector3>(pCSPlayerPawn + Offsets::m_vOldOrigin);
		Vector3 headPosition = playerPosition + Vector3{ 0.0f, 0.0f, 72.0f }; // Assuming the player's height is 72 units

		Vector2 screenPos, headScreenPos;

		Vector2 screenCenter(Screen_WIDTH / 2.0f, Screen_HEIGHT / 2.0f);
		Vector2 screenBottom(Screen_WIDTH / 2.0f, Screen_HEIGHT);



		if (WorldToScreen(playerPosition, screenPos, game.ViewMatrix, Screen_WIDTH, Screen_HEIGHT) &&
			WorldToScreen(headPosition, headScreenPos, game.ViewMatrix, Screen_WIDTH, Screen_HEIGHT))
		{
			float boxHeight = std::fabs(headScreenPos.y - screenPos.y);
			float boxWidth = boxHeight * 0.6f;

			Vector2 topLeft(screenPos.x - boxWidth / 2, headScreenPos.y);
			Vector2 bottomRight(screenPos.x + boxWidth / 2, screenPos.y);


			// Draw the box
			if (Config::Esp::enableEspBoxes)
			{
				ESP::DrawBox(topLeft, bottomRight, Config::Esp::BoxColor, Config::Esp::BoxThickness);
			}

			if (Config::Esp::enableEspHealthBar)
			{
				if (health >= 100)
				{
					Config::Esp::HealthBarColor = ImColor(0, 255, 0, 255); // Green for full health
				}
				else if (health >= 60)
				{
					Config::Esp::HealthBarColor = ImColor(255, 255, 0, 255); // Yellow for medium health
				}
				else if (health >= 30)
				{
					Config::Esp::HealthBarColor = ImColor(255, 165, 0, 255); // Orange for low health
				}
				else
				{
					Config::Esp::HealthBarColor = ImColor(255, 0, 0, 255); // Red for critical health
				}
				ESP::DrawHealthBar(topLeft, bottomRight, health, Config::Esp::HealthBarColor, 2.0f, 6.0f);

				char healthText[16];
				snprintf(healthText, sizeof(healthText), "%d", health);

				// Calculate the position for the health text to be just above the health bar
				ImVec2 healthBarTopLeft(topLeft.x - 6.0f - 5.0f, bottomRight.y - (bottomRight.y - topLeft.y));
				Vector2 healthTextPos(healthBarTopLeft.x - 1.0f, healthBarTopLeft.y - 20.0f); // Increase this value to move it above the health bar


				ESP::DrawText(healthText, healthTextPos, Config::Esp::HealthBarColor, true);
			}

			if (Config::Esp::enableEspLines)
			{
				ESP::DrawLine(screenBottom, screenPos, Config::Esp::LinesColor, Config::Esp::LinesThickness);
			}

			if (Config::Esp::enableEspNames)
			{
				//Vector2 namePos(screenPos.x, headScreenPos.y - 15.0f);
			}
		}
	}
}

// Risky Hacks;

void Cheats::Risky_Cheats::Bhop()
{
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		Memory::WriteMemory<int>(CS2::clientAddress + Offsets::dwForceJump, 65537);
		Sleep(10);
		Memory::WriteMemory<int>(CS2::clientAddress + Offsets::dwForceJump, 256);
	}
}

void Cheats::Risky_Cheats::Antiflash()
{
	float flashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);
	if (flashDuration > 0)
	{
		Memory::WriteMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime, 0);
	}
}

void Cheats::Risky_Cheats::RadarHack()
{
	uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x10);

	for (int i = 1; i < 64; i++)
	{
		if (listEntry == 0)
			continue;

		uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + i * 0x78);
		if (currentController == 0)
			continue;

		int pawnHandle = Memory::ReadMemory<int>(currentController + Offsets::m_hPlayerPawn);
		if (pawnHandle == 0)
			continue;

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
		if (listEntry2 == 0)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (currentPawn == player.localPlayerPawn || currentPawn == 0)
			continue;

		bool isRadarHacked = Memory::ReadMemory<bool>(currentPawn + Offsets::m_entitySpottedState + Offsets::m_bSpotted);

		if (!isRadarHacked)
		{
			Memory::WriteMemory<bool>(currentPawn + Offsets::m_entitySpottedState + Offsets::m_bSpotted, true);
		}
	}
}

void Cheats::Risky_Cheats::GlowHack(DWORD64 COLOR)
{
	uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x10);
	for (int i = 1; i < 64; i++)
	{
		if (listEntry == 0)
			continue;

		uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + i * 0x78);
		if (currentController == 0)
			continue;

		int pawnHandle = Memory::ReadMemory<int>(currentController + Offsets::m_hPlayerPawn);
		if (pawnHandle == 0)
			continue;

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
		if (listEntry2 == 0)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (currentPawn == player.localPlayerPawn || currentPawn == 0)
			continue;

		if (Config::GlowHack::GlowSettings::TeamGlow == false)
		{
			if (player.Team == Memory::ReadMemory<int>(currentPawn + Offsets::m_iTeamNum))
				continue;
		}

		if (Config::GlowHack::GlowSettings::DeadEntityGlow == false)
		{
			if (Memory::ReadMemory<int>(currentPawn + Offsets::m_iHealth) <= 0)
				continue;
		}

		DWORD64 GlowColorOverride = currentPawn + Offsets::m_Glow + Offsets::m_glowColorOverride;
		DWORD64 GlowFunction = currentPawn + Offsets::m_Glow + Offsets::m_bGlowing;

		Memory::WriteMemory<DWORD64>(GlowColorOverride, COLOR); // 0x800000FF <- RED; 0xFDE484FF <- PINK; 
		Memory::WriteMemory<DWORD64>(GlowFunction, 1);
	}
}

void Cheats::Risky_Cheats::Aimbot()
{
	if (!game.EntityList)
		return;

	Vector3 localEyePos = player.Position + player.VecViewOffset;
	Vector3 currentAngles = game.ViewAngles;

	float closestDistance = -1;
	Vector3 enemyPos;


	for (int i = 0; i < 64; i++)
	{
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + ((8 * (i & 0x7FF) >> 9) + 16));
		if (!listEntry)
			continue;

		uintptr_t entityController = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
		if (!entityController)
			continue;

		int entityControllerPawn = Memory::ReadMemory<int>(entityController + Offsets::m_hPlayerPawn);
		if (!entityControllerPawn)
			continue;

		uintptr_t entityPawn = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (entityControllerPawn & 0x1FF));
		if (!entityPawn)
			continue;

		if (Config::Aimbot::TeamCheck)
		{
			if (player.Team == Memory::ReadMemory<int>(entityPawn + Offsets::m_iTeamNum))
				continue;
		}

		if (Memory::ReadMemory<int>(entityPawn + Offsets::m_iHealth) <= 0)
			continue;

		Vector3 entityPos = Memory::ReadMemory<Vector3>(entityPawn + Offsets::m_vOldOrigin);

		Vector3 EntitiesPenisPosition = Config::Aimbot::SetPenisCoordinates(entityPos, entityPawn);
		Vector3 EntityEyePositions = Config::Aimbot::SetHeadCoordinates(entityPos, entityPawn);

		Vector3 aimPosition = EntityEyePositions;

		if (Config::Aimbot::CurrentAimPosIndex == 0)
		{
			aimPosition = EntityEyePositions;
		}
		else if (Config::Aimbot::CurrentAimPosIndex == 1)
		{
			aimPosition = EntitiesPenisPosition;
		}

		float currentDistance = distance(localEyePos, aimPosition);

		Vector3 targetAngle = (aimPosition - localEyePos).RelativeAngle();

		float angleDiff = targetAngle.AngleDifference(currentAngles);

		if (angleDiff > Config::Aimbot::AimFov / 2)
			continue;

		if (closestDistance == 0) continue;

		if (closestDistance < 0 || currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			enemyPos = aimPosition;
		}
	}

	if (closestDistance >= 0)
	{
		Vector3 relativeAngle = (enemyPos - localEyePos).RelativeAngle();

		Vector3 smoothedAngle = currentAngles + (relativeAngle - currentAngles) * Config::Aimbot::AimSmoothness;

		Memory::WriteMemory<Vector3>(CS2::clientAddress + Offsets::dwViewAngles, smoothedAngle);
	}
}

// shits;

void Cheats::ProcessCheatInputs()
{
	if (GetAsyncKeyState(VK_F1) & 1) {
		Flags::enableAimbot = !Flags::enableAimbot;
	}

	if (GetAsyncKeyState(VK_F2) & 1) {
		Flags::enableTriggerbot = !Flags::enableTriggerbot;
	}

	if (GetAsyncKeyState(VK_F3) & 1) {
		Flags::enableEsp = !Flags::enableEsp;
	}
}

void Cheats::InitializeBasicCheats()
{
	if (Flags::enableTriggerbot && Config::TriggerBot::enableHotKey)
	{
		if (GetAsyncKeyState(Config::TriggerBot::TB_KEYCODE))
			Cheats::Safe_Cheats::TriggerBot();
	}
	else if (Flags::enableTriggerbot)
	{
		Cheats::Safe_Cheats::TriggerBot();
	}

	if (Flags::enableRCS)
	{
		Cheats::Safe_Cheats::StandaloneRCS();
	}

	if (Flags::enableAntiflash)
	{
		Cheats::Risky_Cheats::Antiflash();
	}

	if (Flags::enableRadarHack)
	{
		Cheats::Risky_Cheats::RadarHack();
	}

	if (Flags::enableBhop)
	{
		Cheats::Risky_Cheats::Bhop();
	}

	if (Flags::enableEsp)
	{
		Cheats::Safe_Cheats::Esp();
	}
}