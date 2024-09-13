#pragma once
#include <ImGui/imgui.h>
#include <Menu/ImGuiCustomElements.h> 
#include <Globals/hGlobals.h>
#include <Inputs/keycodes.h>
#include <Hacks/Config.h>
#include <Readers/Player.h>
#include <Readers/Game.h>
#include <Readers/Entity.h>

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
				if(ImGui::CollapsingHeader("Triggerbot Settings"))
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
	private:
		void DrawAimFovCircle()
		{
			if (Config::Aimbot::ShowFovCircle)
			{
				ImDrawList* draw_list = ImGui::GetForegroundDrawList();
				draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2,
					ImGui::GetIO().DisplaySize.y / 2), Config::Aimbot::AimFov,
					ImGui::ColorConvertFloat4ToU32(Config::Aimbot::FovCircleColor), 100, Config::Aimbot::FovCircleThickness
				);
			}
		}

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
				ImGui::SetNextItemWidth(100.0f);
				if (ImGui::BeginCombo("Glow Color", Config::GlowHack::AvailableColors[Config::GlowHack::CurrentColorIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(Config::GlowHack::AvailableColors); n++)
					{
						bool is_selected = (Config::GlowHack::CurrentColorIndex == n);
						if (ImGui::Selectable(Config::GlowHack::AvailableColors[n], is_selected))
							Config::GlowHack::CurrentColorIndex = n;

						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

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
						// trigger bot key configuration;
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

					// aim position combo box configuration;
					ImGui::SetNextItemWidth(100.0f);
					if (ImGui::BeginCombo("Aim Position", Config::Aimbot::AimPositions[Config::Aimbot::CurrentAimPosIndex])) // "Select Item" is the label of the combo box
					{
						for (int n = 0; n < IM_ARRAYSIZE(Config::Aimbot::AimPositions); n++)
						{
							bool is_selected = (Config::Aimbot::CurrentAimPosIndex == n);
							if (ImGui::Selectable(Config::Aimbot::AimPositions[n], is_selected))
								Config::Aimbot::CurrentAimPosIndex = n;

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					// aim fov configuration;
					C_Elements::SliderFloat("Aimbot Fov", &Config::Aimbot::AimFov, 0.00f, 360.00, "%.2f");
					C_Elements::SliderFloat("Smoothness", &Config::Aimbot::AimSmoothness, 0.1f, 1.0f, "%.1f");

					// aim fov circle configuration;
					C_Elements::Checkbox("Show Fov Circle", &Config::Aimbot::ShowFovCircle);
					if (Config::Aimbot::ShowFovCircle)
					{
						C_Elements::ColorEditor("Circle Color", &Config::Aimbot::FovCircleColor);
						C_Elements::SliderFloat("Circle thickness", &Config::Aimbot::FovCircleThickness, 1.0f, 5.0f, "%.1f");
					}
					
					DrawAimFovCircle();
					C_Elements::LeaveLine(1);
				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
					DrawAimFovCircle();
					C_Elements::LeaveLine(1);
				}
			}
		}

		friend void RenderMenu();
	};

	class Visuals
	{
	public:
		void GetVisualElements()
		{
			C_Elements::Checkbox("Enable Esp", &Flags::enableEsp);
			if (Flags::enableEsp)
			{
				C_Elements::Checkbox("Box", &Config::Esp::enableEspBoxes);
				C_Elements::Checkbox("Snap Lines", &Config::Esp::enableEspLines);
				C_Elements::Checkbox("Health Bar", &Config::Esp::enableEspHealthBar);
				C_Elements::Checkbox("Armor", &Config::Esp::enableEspArmorBar);
				C_Elements::Checkbox("Team Check", &Config::Esp::enableTeamCheck);

				C_Elements::BeginCustomizingCollapsingHeader();
				if (ImGui::CollapsingHeader("Esp Settings"))
				{
					C_Elements::EndCustomizingCollapsingHeader();
	
					C_Elements::ColorEditor("Box Color", &Config::Esp::BoxColor);
					C_Elements::ColorEditor("Snap Lines Color", &Config::Esp::LinesColor);
					C_Elements::ColorEditor("Snap Lines End Point Color", &Config::Esp::LineEndPointCircleColor);
					C_Elements::ColorEditor("Name Color", &Config::Esp::NameColor);
				
					C_Elements::SliderFloat("Line Thickness", &Config::Esp::LinesThickness, 0.5f, 5.0f, "%.1f");
					C_Elements::SliderFloat("Box Thickness", &Config::Esp::BoxThickness, 0.5f, 5.0f, "%.1f");
				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
				}

				
			}
		}
		
	};

	class Miscellaneous
	{
	public:
		void GetKeyBindsElements()
		{
			ImGui::TextColored(ImVec4(1, 1, 0, 1), " Cheat Shortcuts");
			C_Elements::LeaveLine(1);
			if (Flags::enableAimbot)
			{
				ImGui::TextColored(ImVec4(0, 183, 0, 255), " F1 : Aimbot Enable/Disable");
			}
			else
			{
				ImGui::Text(" F1 : Aimbot Enable/Disable");
			}

			if (Flags::enableTriggerbot)
			{
				ImGui::TextColored(ImVec4(0, 183, 0, 255), " F2 : Triggerbot Enable/Disable");
			}
			else
			{
				ImGui::Text(" F2 : Triggerbot Enable/Disable");
			} 

			if (Flags::enableEsp)
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
			// local player name;
			ImGui::Text("Username : %s", player.Name);
			ImGui::Text("Mapname : %s", game.MapName);
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
			else if(player.Health <= 0)
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
				if (game.BombSite == 1014910543)
				{
					ImGui::Text("Bomb Site : B");
				}
				else
				{
					ImGui::Text("Bomb Site : A");
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

		void GetSpectatorList()
		{

		}
	};

	friend void RenderMenu();
};


void ProcessMenuInputs()
{
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		Flags::showMenu = !Flags::showMenu; // Hide/Unhide Menu;
	}

	if (GetAsyncKeyState(VK_END) & 1) {
		Flags::isRunning = false; // Close Program;
	}
}

void RenderMenu()
{
	Interfaces::MemoryCheats memorycheats;
	Interfaces::Skills skills;
	Interfaces::Visuals visuals;
	Interfaces::Miscellaneous miscs;

	ProcessMenuInputs();
	if (Flags::showMenu)
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(400, 450), ImVec2(1366, 768));
		C_Elements::CustomizeMenuTitleBar();
		ImGui::Begin("Cs2 External Overlay Menu By NeoXa7", &Flags::isRunning);

		if (ImGui::BeginTabBar("Cheats Type"))
		{
			if (ImGui::BeginTabItem("Info"))
			{
				C_Elements::LeaveLine(1);
				miscs.GetGameInfo();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Visuals"))
			{
				C_Elements::LeaveLine(1);
				ImGui::TextColored(ImVec4(0, 183, 0, 255), "Safe to Use! No Memory Written!");
				visuals.GetVisualElements();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Aim"))
			{
				C_Elements::LeaveLine(1);
				ImGui::TextColored(ImVec4(0, 183, 0, 255), "Safe to Use! No Memory Written!");
				skills.GetTriggerBotElements();
				skills.GetRCSElements();
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not Safe to Use! Memory Written!");
				memorycheats.GetAimbotElements();
				ImGui::EndTabItem();
			}
			else
			{
				memorycheats.DrawAimFovCircle();
			}

			if (ImGui::BeginTabItem("Memory"))
			{
				C_Elements::LeaveLine(1);
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not Safe to Use! Memory Written!");
				memorycheats.GetMiscElements();
				memorycheats.GlowHackElements();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc's"))
			{
				miscs.GetKeyBindsElements();
				ImGui::EndTabItem();
			}


			ImGui::EndTabBar();
		}
		else
		{
			memorycheats.DrawAimFovCircle();
		}

		ImGui::End();
	}
	else
	{
		memorycheats.DrawAimFovCircle();
	}
}

