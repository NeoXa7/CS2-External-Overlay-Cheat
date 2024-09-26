#pragma once
#include <ImGui/imgui.h>
#include <Menu/ImGuiCustomElements.h> 
#include <Globals/hGlobals.h>
#include <Inputs/keycodes.h>
#include <Hacks/Utils/Config.h>
#include <Readers/Player.h>
#include <Readers/Game.h>
#include <Readers/Entity.h>
#include <Hacks/Hacks.h>
#include <Hacks/Utils/Bomb.h>
#include <Hacks/Utils/DrawUtils.h>

class Interfaces
{
private:
	class Skills
	{
	public:
		void GetTriggerBotElements()
		{
			C_Elements::Checkbox("TriggerBot", &Flags::enableTriggerbot);
			if (Flags::enableTriggerbot)
			{
				C_Elements::BeginCustomizingCollapsingHeader();
				if (ImGui::CollapsingHeader("Triggerbot Settings"))
				{
					C_Elements::Checkbox("Team Check", &Config::TriggerBot::enableTeamCheck);
					C_Elements::Checkbox("Enable Hotkey", &Config::TriggerBot::enableHotKey);
					if (Config::TriggerBot::enableHotKey)
					{
						ImGui::SetNextItemWidth(100.0f);
						C_Elements::InputText(
							"Triggerbot Key Code",
							3.5f,
							Config::TriggerBot::TB_Default_KEYCODE_STR,
							sizeof(Config::TriggerBot::TB_Default_KEYCODE_STR),
							ImGuiInputTextFlags_CharsHexadecimal
						);

						std::stringstream ss(Config::TriggerBot::TB_Default_KEYCODE_STR);
						ss >> std::hex >> Config::TriggerBot::TB_KEYCODE;
						ImGui::Text("Triggerbot Key : %s", KeyCodeToString(Config::TriggerBot::TB_KEYCODE));
						C_Elements::LeaveLine(2);
					}

					C_Elements::EndCustomizingCollapsingHeader();
				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
					C_Elements::LeaveLine(3);
				}


			}
		}

		void GetRCSElements()
		{
			C_Elements::Checkbox("Standalone RCS", &Flags::enableRCS);
		}
	};

	class MemoryCheats
	{
	public:
		void GetMiscElements()
		{
			C_Elements::Checkbox("Bhop", &Flags::enableBhop);
			C_Elements::Checkbox("Antiflash", &Flags::enableAntiflash);
			C_Elements::Checkbox("RadarHack", &Flags::enableRadarHack);
		}

		void GlowHackElements()
		{
			C_Elements::Checkbox("Player Glow", &Flags::enableGlowHack);
			if (Flags::enableGlowHack)
			{
				C_Elements::ComboBox(
					"Glow Color",
					Config::GlowHack::AvailableColors[Config::GlowHack::CurrentColorIndex],
					&Config::GlowHack::CurrentColorIndex,
					Config::GlowHack::AvailableColors,
					IM_ARRAYSIZE(Config::GlowHack::AvailableColors)
				);

				switch (Config::GlowHack::CurrentColorIndex) {
				case 0: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::GREEN; break;
				case 1: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::YELLOW; break;
				case 2: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::BLUE; break;
				case 3: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::RED; break;
				case 4: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::WHITE; break;
				case 5: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::PURPLE; break;
				case 6: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::CYAN; break;
				case 7: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::LIGHTBLUE; break;
				default: break;
				}

				ImGui::SetNextItemWidth(50.0f);
				C_Elements::BeginCustomizingCollapsingHeader();
				if (ImGui::CollapsingHeader("Glow Settings"))
				{
					C_Elements::EndCustomizingCollapsingHeader();
					C_Elements::Checkbox("Team Glow", &Config::GlowHack::GlowSettings::TeamGlow);
					C_Elements::Checkbox("Dead Entity Glow", &Config::GlowHack::GlowSettings::DeadEntityGlow);
					C_Elements::LeaveLine(1);
				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
				}
			}
		}

		void GetAimbotElements()
		{
			C_Elements::Checkbox("Aimbot", &Flags::enableAimbot);
			if (Flags::enableAimbot)
			{
				C_Elements::BeginCustomizingCollapsingHeader();
				if (ImGui::CollapsingHeader("Aimbot Settings"))
				{
					C_Elements::EndCustomizingCollapsingHeader();
					C_Elements::Checkbox("Enable HotKey", &Config::Aimbot::enableHotKey);
					C_Elements::Checkbox("Team check", &Config::Aimbot::TeamCheck);

					if (Config::Aimbot::enableHotKey)
					{
						// Aimbot HotKey Configuration;
						ImGui::SetNextItemWidth(100.0f);
						C_Elements::InputText(
							"Aimbot Key Code",
							3.5f,
							Config::Aimbot::AB_Default_KEYCODE_STR,
							sizeof(Config::Aimbot::AB_Default_KEYCODE_STR),
							ImGuiInputTextFlags_CharsHexadecimal
						);

						std::stringstream ss(Config::Aimbot::AB_Default_KEYCODE_STR);
						ss >> std::hex >> Config::Aimbot::AB_KEYCODE;
						ImGui::Text("Aimbot Key : %s", KeyCodeToString(Config::Aimbot::AB_KEYCODE));
						C_Elements::LeaveLine(1);
					}

					// Aimbot Positions Combo Box Configuration;
					C_Elements::ComboBox(
						"Aim Position",
						Config::Aimbot::AimPositions[Config::Aimbot::CurrentAimPosIndex],
						&Config::Aimbot::CurrentAimPosIndex,
						Config::Aimbot::AimPositions,
						IM_ARRAYSIZE(Config::Aimbot::AimPositions)
					);

				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
					C_Elements::LeaveLine(1);
				}
			}
		}

		friend void RenderMenu();
	};

	class Visuals
	{
	public:
		void GetPlayerEspElements()
		{
			C_Elements::Checkbox("Enable Player Esp", &Flags::enablePlayerEsp);
			if (Flags::enablePlayerEsp)
			{
				C_Elements::Checkbox("Team Check", &Config::Esp::enableTeamCheck);
				C_Elements::Checkbox("Box", &Config::Esp::enableEspBoxes);
				if (Config::Esp::enableEspBoxes)
				{
					C_Elements::ColorEditor("Box Color", &Config::Esp::BoxColor);
				}
				
				C_Elements::Checkbox("Snap Lines", &Config::Esp::enableEspLines);
				if (Config::Esp::enableEspLines)
				{
					C_Elements::ColorEditor("Lines Color", &Config::Esp::LinesColor);
				}

				C_Elements::ComboBox("Line Position",
					Config::Esp::availableSnapLinesPos[Config::Esp::currentlinePosIndex],
					&Config::Esp::currentlinePosIndex, Config::Esp::availableSnapLinesPos,
					IM_ARRAYSIZE(Config::Esp::availableSnapLinesPos)
				);
				C_Elements::LeaveLine(1);

				C_Elements::Checkbox("Entities Name", &Config::Esp::enableEspNames);
				C_Elements::Checkbox("Distance", &Config::Esp::enableDistanceEsp);
				if (Config::Esp::enableEspNames)
				{
					C_Elements::ColorEditor("Name Color", &Config::Esp::NameColor);
					
				}
		
				if (Config::Esp::enableDistanceEsp)
				{
					C_Elements::ColorEditor("Distance Text Color", &Config::Esp::DistanceColor);
				}

				C_Elements::Checkbox("Bones", &Config::Esp::enableEspBones);
				if (Config::Esp::enableEspBones)
				{
					C_Elements::Checkbox("Head Fill", &Config::Esp::HeadFilled);
					C_Elements::Checkbox("Show Bone Joints", &Config::Esp::ShowBoneJoints);
					C_Elements::ColorEditor("Bones Color", &Config::Esp::BonesColor);
					C_Elements::ColorEditor("Head Color", &Config::Esp::HeadColor);
				}
				C_Elements::Checkbox("Health Bar", &Config::Esp::enableEspHealthBar);
				C_Elements::Checkbox("Health Text", &Config::Esp::enableEspHealthPointsText);
				C_Elements::Checkbox("Armor Bar", &Config::Esp::enableEspArmorBar);

				if (Config::Esp::enableEspBoxes)
					C_Elements::SliderFloat("Box Thickness", &Config::Esp::BoxThickness, 0.5f, 5.0f, "%.1f");
				if (Config::Esp::enableEspLines)
					C_Elements::SliderFloat("Lines Thickness", &Config::Esp::LinesThickness, 0.5f, 5.0f, "%.1f");
				if (Config::Esp::enableEspBones)
					C_Elements::SliderFloat("Bones Thickness", &Config::Esp::BonesThickness, 0.5f, 5.0f, "%.1f");
			}
		}

		void GetC4EspElements()
		{
			C_Elements::Checkbox("Enable Bomb Esp", &Flags::enableC4Esp);
			if (Flags::enableC4Esp)
			{			
				C_Elements::Checkbox("Bomb Box Esp", &Config::Esp::enableC4Box);
				if (Config::Esp::enableC4Box)
				{
					C_Elements::ColorEditor("C4 Box Color", &Config::Esp::C4_Box_Color);					
				}

				C_Elements::Checkbox("Bomb Distance", &Config::Esp::enableC4Distance);
				if (Config::Esp::enableC4Distance)
				{
					C_Elements::ColorEditor("Distance Color", &Config::Esp::C4_Distance_Text_Color);
				}

				
				C_Elements::Checkbox("Bomb Status", &Config::Esp::enableC4StatusEsp);
				if (Config::Esp::enableC4StatusEsp)
				{
					C_Elements::ColorEditor("Status Color", &Config::Esp::C4_Status_Text_Color);
				}	
				C_Elements::LeaveLine(1);
				if (Config::Esp::enableC4Box)
					C_Elements::SliderFloat("C4 Box Thickness", &Config::Esp::C4BoxThickness, 0.5f, 5.0f, "%.1f");
				C_Elements::LeaveLine(1);
			}
		}

		void GetWorldEspElements()
		{
			C_Elements::Checkbox("Enable World Esp", &Flags::enableWorldEsp);
			if (Flags::enableWorldEsp)
			{
				C_Elements::Checkbox("Chicken Esp", &Config::Esp::enableChickensEsp);
				if (Config::Esp::enableChickensEsp)
				{
					C_Elements::ColorEditor("Chicken Text Color", &Config::Esp::Chicken_Text_Color);
				}
				
				C_Elements::Checkbox("Hostage Esp", &Config::Esp::enableHostagesEsp);
				if (Config::Esp::enableHostagesEsp)
				{
					C_Elements::ColorEditor("Hostage Esp Box Color", &Config::Esp::World_Entities_BoxColor);		
				}
				
				C_Elements::Checkbox("Dropped Weapon Esp", &Config::Esp::enableDroppedWeaponEsp);
				if (Config::Esp::enableDroppedWeaponEsp)
				{
					C_Elements::ColorEditor("Dropped Weapon Esp Text Color", &Config::Esp::Weapon_Esp_Text_Color);
				}

				C_Elements::Checkbox("Projectiles Esp", &Config::Esp::enableProjectilesEsp);
				if (Config::Esp::enableProjectilesEsp)
				{
					C_Elements::ColorEditor("Projectiles Text Color", &Config::Esp::Projectiles_Text_Color);
				}
			}
		}

		void GetOtherVisualElements()
		{
			C_Elements::Checkbox("Crosshair", &Config::Game::DrawCrosshair);
			C_Elements::ColorEditor("Color", &Config::Game::CrosshairColor);
			C_Elements::SliderFloat("Size", &Config::Game::CrosshairSize, 2.0f, 50.0f, "%.1f");
		}
	};

	class Miscellaneous
	{
	public:
		void GetKeyBindsElements()
		{
			ImGui::TextColored(ImVec4(1, 1, 0, 1), " Cheat Shortcuts");
			C_Elements::LeaveLine(1);

			if (Flags::enableTriggerbot)
			{
				ImGui::TextColored(ImVec4(0, 183, 0, 255), " F2 : Triggerbot Enable/Disable");
			}
			else
			{
				ImGui::Text(" F2 : Triggerbot Enable/Disable");
			}

			if (Flags::enablePlayerEsp)
			{
				ImGui::TextColored(ImVec4(0, 183, 0, 255), " F3 : Esp Enable/Disable");
			}
			else
			{
				ImGui::Text(" F3 : Esp Enable/Disable");
			}

			C_Elements::LeaveLine(1);
			ImGui::TextColored(ImVec4(1, 1, 0, 1), " Menu Shortcuts");
			C_Elements::LeaveLine(1);
			ImGui::Text(" Insert : HIDE/UNHIDE Menu");
			ImGui::Text(" End : Close Program");

		}

		void GetGameInfo() // includes local player;
		{
			ImGui::Text("Local Player : %s", player.Name);
			ImGui::Text("Ping : %d", player.Ping);
			ImGui::Text("Sensitivity : %.2f", player.Sensitivity);
			ImGui::Text("Mapname : %s", game.MapName);
			ImGui::Text("Gamemode: %s", game.GetGameModeName().c_str());

			// local team;
			switch (player.Team)
			{
			case 1: ImGui::TextColored(Config::Game::SpectatorColor, "Team : Spectator "); break;
			case 2: ImGui::TextColored(Config::Game::TerroristColor, "Team : Terrorist "); break;
			case 3: ImGui::TextColored(Config::Game::CounterTerroristColor, "Team : Counter-Terrorist "); break;
			default: ImGui::Text("Team : ~Unknown"); break;
			}

			// local player health;
			ImGui::Text("Health : %d", player.Health);

			if (player.Health > 0)
			{
				ImGui::Text("Status : Alive");
			}
			else if (player.Health <= 0)
			{
				ImGui::Text("Status : Dead");
			}
			else
			{
				ImGui::Text("Status : ~Unknown");
			}

			// bomb info;
			if (game.BombPlanted)
			{
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Bomb Status : Planted");
				if (c4.GetBombSite() == 0)
				{
					ImGui::Text("Bomb Site : A");
				}
				else if (c4.GetBombSite() == 1)

				{
					ImGui::Text("Bomb Site : B");
				}

				if (game.IsBombBeingDefused)
				{
					ImGui::TextColored(ImVec4(0, 183, 0, 255), "Bomb Is Being Defused");
				}
			}
			else
			{
				if (game.BombDropped)
				{
					ImGui::TextColored(ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f), "Bomb Status : Dropped");
				}
				else
				{
					ImGui::TextColored(ImVec4(0, 183, 0, 255), "Bomb Status : Not-Planted");
				}
			}		
		}

		void GetEntityList()
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

				entities->UpdateEntities(currentPawn, currentController);

				if (player.Team == entities->Team)
					continue;

				if (ImGui::TreeNode(entities->Names))
				{
					switch (entities->Team)
					{
					case 1: ImGui::TextColored(Config::Game::SpectatorColor, "Team : Spectator "); break;
					case 2: ImGui::TextColored(Config::Game::TerroristColor, "Team : Terrorist "); break;
					case 3: ImGui::TextColored(Config::Game::CounterTerroristColor, "Team : Counter-Terrorist "); break;
					default: ImGui::Text("Team : ~Unknown"); break;
					}

					ImGui::Text("Health: %d", entities->Health);
					ImGui::Text("Armor: %d", entities->Armor);
					if (entities->Health > 0)
					{
						ImGui::Text("Status : Alive");
					}
					else if (entities->Health <= 0)
					{
						ImGui::Text("Status : Dead");
					}
					else
					{
						ImGui::Text("Status : ~Unknown");
					}
					if (entities->IsFiring)
					{
						ImGui::Text("Firing : True");
					}
					else
					{
						ImGui::Text("Firing : False");
					}

					ImGui::Text("Ping : %d", entities->Ping);
					ImGui::Text("Position (x, y, z) : %.2f, %.2f, %.2f", entities->Position.x, entities->Position.y, entities->Position.z);

					ImGui::TreePop();
				}
			}
		}

	};

	friend void RenderMenu();

	void ProcessMenuInputs()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			Flags::showMenu = !Flags::showMenu; // Hide/Unhide Menu;
		}

		if (GetAsyncKeyState(VK_END) & 1) {
			Flags::isRunning = false; // Close Program;
		}
	}
};

void RenderMenu()
{
	Interfaces interfaces;
	Interfaces::MemoryCheats memorycheats;
	Interfaces::Skills skills;
	Interfaces::Visuals visuals;
	Interfaces::Miscellaneous miscs;

	interfaces.ProcessMenuInputs();
	if (Flags::showMenu)
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(Min_Menu_Width, Min_Menu_Height), ImVec2(1366, 768));
		C_Elements::CustomizeMenuTitleBar();
		ImGui::Begin("Cs2 External Overlay Menu By NeoXa7", &Flags::isRunning);

		if (ImGui::BeginTabBar("Cheats Type"))
		{
			// Game Info Tab
			if (ImGui::BeginTabItem("Game Info"))
			{
				C_Elements::LeaveLine(1);
				miscs.GetGameInfo();
				ImGui::EndTabItem();
			}

			// Visuals Tab
			if (ImGui::BeginTabItem("Visuals"))
			{
				C_Elements::LeaveLine(1);
				ImGui::TextColored(ImVec4(0, 183, 0, 255), "Safe to Use! No Memory Written!");
				C_Elements::BeginCustomizingCollapsingHeader();
				if(ImGui::TreeNode("Player"))
				{
					visuals.GetPlayerEspElements();
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Bomb"))
				{
					visuals.GetC4EspElements();
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("World"))
				{
					visuals.GetWorldEspElements();
					C_Elements::LeaveLine(1);
					ImGui::TreePop();
				}

				C_Elements::LeaveLine(1);
				ImGui::EndTabItem();
			}

			// Aim Tab
			if (ImGui::BeginTabItem("Aim"))
			{
				C_Elements::LeaveLine(1);
				ImGui::TextColored(ImVec4(0, 183, 0, 255), "Safe to Use! No Memory Written!");
				skills.GetTriggerBotElements();
				skills.GetRCSElements();
				memorycheats.GetAimbotElements();
				ImGui::EndTabItem();
			}

			// Memory Tab
			if (ImGui::BeginTabItem("Memory"))
			{
				C_Elements::LeaveLine(1);
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not Safe to Use! Memory Written!");
				memorycheats.GetMiscElements();
				memorycheats.GlowHackElements();
				ImGui::EndTabItem();
			}

			// Misc's Tab
			if (ImGui::BeginTabItem("Misc's"))
			{
				C_Elements::LeaveLine(1);
				visuals.GetOtherVisualElements();
				ImGui::EndTabItem();
			}

			// Entity List Tab
			if (ImGui::BeginTabItem("Entity List"))
			{
				C_Elements::LeaveLine(1);
				miscs.GetEntityList();
				ImGui::EndTabItem();
			}

			// Settings Tab
			if (ImGui::BeginTabItem("Settings"))
			{
				C_Elements::LeaveLine(1);
				miscs.GetKeyBindsElements();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}