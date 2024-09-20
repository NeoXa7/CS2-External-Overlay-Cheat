#pragma once
#include <Memory/hMemory.h>
#include <Inputs/Events.h>
#include <Readers/Game.h>
#include <Readers/Player.h>
#include <Hacks/Config.h>
#include "Esp.h"
#include <Maths/WorldToScreen.h>
#include <Hacks/Bomb.h>

namespace CHEATS
{
	namespace SAFE_CHEATS // This namespace Includes cheats that doesn't writes to memory which is ban free;
	{
		void TriggerBot();
		void StandaloneRCS();
		void PlayerEsp();
		void C4_Esp();
	}

	namespace MEMORY_CHEATS // This namespace Includes cheats that writes memory which may lead to game ban;
	{
		void Bhop();
		void Antiflash();
		void GlowHack(DWORD64 COLOR);
	}

	void ProcessCheatInputs();
	void InitializeBasicCheats();
}

// Safe Hacks;

void CHEATS::SAFE_CHEATS::TriggerBot()
{
	if (game.EntityIndex > 0)
	{
		uintptr_t entityListEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * (game.EntityIndex >> 9) + 0x10);
		uintptr_t entity = Memory::ReadMemory<uintptr_t>(entityListEntry + 120 * (game.EntityIndex & 0x1FF));

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

void CHEATS::SAFE_CHEATS::StandaloneRCS()
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

void CHEATS::SAFE_CHEATS::PlayerEsp() // Main Loop
{
	for (int i = 1; i < 64; i++)
	{		
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!listEntry)
			continue;

		uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
		if (!currentController)
			continue;

		uint32_t pawnHandle = Memory::ReadMemory<uint32_t>(currentController + Offsets::m_hPlayerPawn);
		if (!pawnHandle)
			continue;

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
		if (!listEntry2)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (!currentPawn)
			continue;

		if (currentPawn == player.localPlayerPawn)
			continue;

		entities->UpdateEntities(currentPawn, currentController);
		game.UpdateGameVars();

		if (entities->Health <= 0 || entities->Health > 100)
			continue;
	
		if (Config::Esp::enableTeamCheck)
		{
			if (player.Team == entities->Team)
				continue;
		}

		Vector3 HeadPosition = entities->Position + Vector3{ 0.0f, 0.0f, 72.0f }; // Box Height 72 Units;

		Vector2 screenPos, headScreenPos;
		Vector2 screenTop(Screen_WIDTH / 2.0f, 0.0f);
		Vector2 screenCenter(Screen_WIDTH / 2.0f, Screen_HEIGHT / 2.0f);
		Vector2 screenBottom(Screen_WIDTH / 2.0f, Screen_HEIGHT);

		if (WorldToScreen(entities->Position, screenPos, game.ViewMatrix) &&  // Entities W2S Position;
			WorldToScreen(HeadPosition, headScreenPos, game.ViewMatrix)) // Entities W2S Head Position;
		{
			float boxHeight = std::fabs(headScreenPos.y - screenPos.y);
			float boxWidth = boxHeight * 0.6f;

			Vector2 topLeft(screenPos.x - boxWidth / 2, headScreenPos.y);
			Vector2 topRight(screenPos.x + boxWidth / 2 + 12.0f, headScreenPos.y);
			Vector2 bottomRight(screenPos.x + boxWidth / 2, screenPos.y);

			// Draw the Box
			if (Config::Esp::enableEspBoxes)
			{
				ESP::DrawBox
				(
					topLeft, 
					bottomRight, 
					Config::Esp::BoxColor, 
					Config::Esp::BoxThickness
				);
			}

			// Draw the Health Bar
			if (Config::Esp::enableEspHealthBar)
			{
				if (entities->Health >= 100)
				{
					Config::Esp::HealthBarColor = ImColor(0, 255, 0, 255); // Green for full health
				}
				else if (entities->Health >= 60)
				{
					Config::Esp::HealthBarColor = ImColor(255, 255, 0, 255); // Yellow for medium health
				}
				else if (entities->Health >= 30)
				{
					Config::Esp::HealthBarColor = ImColor(255, 165, 0, 255); // Orange for low health
				}
				else
				{
					Config::Esp::HealthBarColor = ImColor(255, 0, 0, 255); // Red for critical health
				}

				ESP::DrawHealthBar
				(
					topLeft, 
					bottomRight, 
					entities->Health,
					Config::Esp::HealthBarColor, 
					2.0f, 
					6.0f
				);				
			}

			// Draw the Health Text
			if (Config::Esp::enableEspHealthPointsText)
			{
				char healthText[16];
				snprintf(healthText, sizeof(healthText), "[HP %d]", entities->Health);

				// Calculate the position for the health text to be just above the health bar
				Vector2 healthBarTopLeft(topLeft.x - 6.0f - 5.0f, bottomRight.y - (bottomRight.y - topLeft.y));
				Vector2 healthTextPos(healthBarTopLeft.x - 1.0f, healthBarTopLeft.y - 20.0f);

				ESP::DrawTextW
				(
					healthText,
					healthTextPos,
					Config::Esp::HealthBarColor, 
					false
				);
			}

			// Draw the Armor Bar
			if (Config::Esp::enableEspArmorBar)
			{
				if (entities->Team == 1)
				{
					Config::Esp::ArmorBarColor = Config::Game::SpectatorColor;
				}
				else if (entities->Team == 2)
				{
					Config::Esp::ArmorBarColor = Config::Game::TerroristColor;
				}
				else if (entities->Team == 3)
				{
					Config::Esp::ArmorBarColor = Config::Game::CounterTerroristColor;
				}

				ESP::DrawHealthBar
				(
					topRight, 
					bottomRight,
					entities->Armor,
					Config::Esp::ArmorBarColor, 
					2.0f, 
					6.0f
				);		
			}

			// Draw the Snap Lines
			if (Config::Esp::enableEspLines)
			{
				switch (Config::Esp::currentlinePosIndex) {
				case 0: Config::Esp::currentlinePos = screenTop; break; // Top
				case 1: Config::Esp::currentlinePos = screenCenter; break; // Center
				case 2: Config::Esp::currentlinePos = screenBottom; break; // Bottom
				default: Config::Esp::currentlinePos = screenBottom; break; // Default
				}

				if (game.Distance_From_LocalPlayer_To_Entities < Config::Esp::SLEndPointDisplayDistance)
				{
					ESP::DrawLine
					(
						Config::Esp::currentlinePos,
						screenPos,
						Config::Esp::LinesColor,
						Config::Esp::LinesThickness,
						true,
						3.5f,
						Config::Esp::LinesColor
					);
				}
				else
				{
					ESP::DrawLine
					(
						Config::Esp::currentlinePos,
						screenPos,
						Config::Esp::LinesColor,
						Config::Esp::LinesThickness
					);
				}

				
			}

			// Draw the Entity Name Text
			if (Config::Esp::enableEspNames)
			{
				Vector2 namePos(screenPos.x - 20.0f, screenPos.y);
				ESP::DrawTextW
				(
					entities->Names, 
					namePos, 
					Config::Esp::NameColor, 
					true
				);
			}
			
			// Draw the Bones
			if (Config::Esp::enableEspBones)
			{
				ESP::DrawBones(currentPawn);
			}
			
			// Draw the Distance Text
			if (Config::Esp::enableDistanceEsp)
			{
				char DistTextArray[128];
				float EntitiesDistanceInMeters = game.Distance_From_LocalPlayer_To_Entities / GAME_METRIC_UNITS;

				snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", EntitiesDistanceInMeters);

				ESP::DrawTextW(DistTextArray, topRight, Config::Esp::DistanceColor);
			}
		}
	}
}

void CHEATS::SAFE_CHEATS::C4_Esp()
{
	// Bomb Esp
	Vector3 PlantedC4Pos3D = c4.GetPlantedC4Position();
	Vector3 DroppedC4Pos3D = c4.GetDroppedC4Position();
	float C4Width = 30.0f;
	float C4Height = 20.0f;

	if (game.BombPlanted)
	{
		Vector2 Planted_C4_ScreenPos, PlantedC4Height;
		Vector3 PlantedC4HeightPos = PlantedC4Pos3D + Vector3{ 0.0f, 0.0f, C4Height }; // Box height based on bomb size

		if (WorldToScreen(PlantedC4Pos3D, Planted_C4_ScreenPos, game.ViewMatrix) &&
			WorldToScreen(PlantedC4HeightPos, PlantedC4Height, game.ViewMatrix))
		{
			float BoxHeight = std::fabs(PlantedC4Height.y - Planted_C4_ScreenPos.y);
			float boxWidth = BoxHeight * (C4Width / C4Height); // Adjust box width based on actual C4 size

			Vector2 topLeftPBP(Planted_C4_ScreenPos.x - boxWidth / 2.0f, Planted_C4_ScreenPos.y - BoxHeight / 2.0f);
			Vector2 bottomRightPBP(Planted_C4_ScreenPos.x + boxWidth / 2.0f, Planted_C4_ScreenPos.y + BoxHeight / 2.0f);

			if (Config::Esp::enableC4Box)
			{
				ESP::DrawBox(topLeftPBP, bottomRightPBP, Config::Esp::C4_Box_Color, Config::Esp::C4BoxThickness);
			}
			
			if (Config::Esp::enableC4StatusEsp)
			{
				ESP::DrawTextW("C4_Planted", topLeftPBP, Config::Esp::C4_Status_Text_Color);
			}
			
			if (Config::Esp::enableC4Distance)
			{
				char DistTextArray[128];
				float PlantedC4_DistanceInMeters = c4.Get_Distance_From_PlantedC4_To_LocalPlayer() / GAME_METRIC_UNITS;
				snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", PlantedC4_DistanceInMeters);

				ESP::DrawTextW(DistTextArray, bottomRightPBP, Config::Esp::C4_Distance_Text_Color);
			}		
		}
	}

	if (game.BombDropped)
	{
		Vector2 Dropped_C4_ScreenPos, Dropped_C4_Height;	
		Vector3 DroppedC4HeightPos = DroppedC4Pos3D + Vector3{ 0.0f, 0.0f, C4Height };

		if (WorldToScreen(DroppedC4Pos3D, Dropped_C4_ScreenPos, game.ViewMatrix) &&
			WorldToScreen(DroppedC4HeightPos, Dropped_C4_Height, game.ViewMatrix))
		{
			float BoxHeight = std::fabs(Dropped_C4_Height.y - Dropped_C4_ScreenPos.y);
			float boxWidth = BoxHeight * (C4Width / C4Height);

			Vector2 topLeftDBP(Dropped_C4_ScreenPos.x - boxWidth / 2.0f, Dropped_C4_ScreenPos.y - BoxHeight / 2.0f);
			Vector2 bottomRightDBP(Dropped_C4_ScreenPos.x + boxWidth / 2.0f, Dropped_C4_ScreenPos.y + BoxHeight / 2.0f);

			if (Config::Esp::enableC4Box)
			{
				ESP::DrawBox(topLeftDBP, bottomRightDBP, Config::Esp::C4_Box_Color, Config::Esp::C4BoxThickness);
			}
			
			if (Config::Esp::enableC4StatusEsp)
			{
				ESP::DrawTextW("C4_Dropped", topLeftDBP, Config::Esp::C4_Status_Text_Color);
			}

			if (Config::Esp::enableC4Distance)
			{
				char DistTextArray[128];
				float DroppedC4_DistanceInMeters = c4.Get_Distance_From_DroppedC4_To_LocalPlayer() / GAME_METRIC_UNITS;
				snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", DroppedC4_DistanceInMeters);

				ESP::DrawTextW(DistTextArray, bottomRightDBP, Config::Esp::C4_Distance_Text_Color);
			}		
		}
	}
}

// Risky Hacks;

void CHEATS::MEMORY_CHEATS::Bhop()
{
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		Memory::WriteMemory<int>(CS2::ClientDll + Offsets::dwForceJump, 65537);
		Sleep(10);
		Memory::WriteMemory<int>(CS2::ClientDll + Offsets::dwForceJump, 256);
	}
}

void CHEATS::MEMORY_CHEATS::Antiflash()
{
	if (game.FlashDuration > 0)
	{
		Memory::WriteMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime, 0);
	}
}

void CHEATS::MEMORY_CHEATS::GlowHack(DWORD64 COLOR)
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

// shits;

void CHEATS::ProcessCheatInputs()
{
	/*if (GetAsyncKeyState(VK_F1) & 1) {
		Flags::enableAimbot = !Flags::enableAimbot;
	}*/

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
	if (Flags::enableTriggerbot && Config::TriggerBot::enableHotKey)
	{
		if (GetAsyncKeyState(Config::TriggerBot::TB_KEYCODE))
			CHEATS::SAFE_CHEATS::TriggerBot();
	}
	else if (Flags::enableTriggerbot)
	{
		CHEATS::SAFE_CHEATS::TriggerBot();
	}

	if (Flags::enableRCS)
	{
		CHEATS::SAFE_CHEATS::StandaloneRCS();
	}

	if (Flags::enableAntiflash)
	{
		CHEATS::MEMORY_CHEATS::Antiflash();
	}

	if (Flags::enableBhop)
	{
		CHEATS::MEMORY_CHEATS::Bhop();
	}	

	if (Flags::enablePlayerEsp)
	{
		CHEATS::SAFE_CHEATS::PlayerEsp();
	}

	if (Flags::enableC4Esp)
	{
		CHEATS::SAFE_CHEATS::C4_Esp();
	}
}