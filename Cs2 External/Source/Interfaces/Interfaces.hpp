#include <ImGui/imgui.h>
#include <Globals/Globals.hpp>
#include <Interfaces/Elements.hpp>
#include <Utilities/Config.hpp>
#include "Loader.hpp"
#include "LSConfigSystem.hpp"
#include <Readers/LocalPlayer.hpp>
#include <Readers/Game.hpp>
#include <Utilities/Bomb.hpp>
#include <Utilities/Updater.hpp>
#include <Overlay/ExeConfig.hpp>
#include <Overlay/Message.hpp>

enum class MenuOption
{
    None,
    GameInfo,
    Aim,
    Player_Esp,
    World_Esp,
    Bomb_Esp,
    Movement,
    Memory,
    EntityList,
    Misc,
    Configs
};

MenuOption currentOption = MenuOption::GameInfo; // Track the currently selected option

class Interfaces
{
private:
    class Aim
    {
    public:
        VOID GetAimbotWidgets()
        {
            ImGui::Text("Aimbot");                   
            ImGui::BeginChild("Aimbot Container", ImVec2(0, 210), true);

            Checkbox("Enable", &Flags::enableAimbot);
            Checkbox("Team Check", &Config::Aimbot::TeamCheck);
            Checkbox("Dormant Check", &Config::Aimbot::DormantCheck);
            Checkbox("Enable Hotkey", &Config::Aimbot::enableHotKey);
            ComboBox(
                "Aimbot Key",
                Config::Aimbot::HotkeyOptions[Config::Aimbot::CurrentHotkeyIndex],
                &Config::Aimbot::CurrentHotkeyIndex,
                Config::Aimbot::HotkeyOptions,
                IM_ARRAYSIZE(Config::Aimbot::HotkeyOptions),
                2.0f,
                150.0f
            );

            switch (Config::Aimbot::CurrentHotkeyIndex)
            {
            case 0: Config::Aimbot::currentKey = 0x06; break;
            case 1: Config::Aimbot::currentKey = 0x05; break;
            case 2: Config::Aimbot::currentKey = 0x02; break;
            case 3: Config::Aimbot::currentKey = 0xA0; break;
            case 4: Config::Aimbot::currentKey = 0xA2; break;
            case 5: Config::Aimbot::currentKey = 0xA4; break;
            }

            ComboBox(
                "Aim Position",
                Config::Aimbot::AimPositions[Config::Aimbot::CurrentAimPosIndex],
                &Config::Aimbot::CurrentAimPosIndex,
                Config::Aimbot::AimPositions,
                IM_ARRAYSIZE(Config::Aimbot::AimPositions),
                2.0f,
                150.0f
            );

            ImGui::EndChild();
        }

        VOID GetTriggerBotWidgets()
        {
            ImGui::Text("Triggerbot");
            ImGui::BeginChild("Triggerbot Container", ImVec2(0, 155), true);
            Checkbox("Enable", &Flags::enableTriggerbot);
            Checkbox("Team Check", &Config::TriggerBot::enableTeamCheck);
            Checkbox("Enable Hotkey", &Config::TriggerBot::enableHotKey);

            ComboBox(
                "Triggerbot Key",
                Config::TriggerBot::HotkeyOptions[Config::TriggerBot::CurrentHotkeyIndex],
                &Config::TriggerBot::CurrentHotkeyIndex,
                Config::TriggerBot::HotkeyOptions,
                IM_ARRAYSIZE(Config::TriggerBot::HotkeyOptions),
                2.0f,
                150.0f
            );

            switch (Config::TriggerBot::CurrentHotkeyIndex)
            {
            case 0: Config::TriggerBot::currentKey = 0xA0; break;
            case 1: Config::TriggerBot::currentKey = 0xA2; break;
            case 2: Config::TriggerBot::currentKey = 0xA4; break;
            case 3: Config::TriggerBot::currentKey = 0x06; break;
            case 4: Config::TriggerBot::currentKey = 0x05; break;
            default:Config::TriggerBot::currentKey = 0xA0; break;
            }
            ImGui::EndChild();
        }

        VOID GetRCSWidgets()
        {
            ImGui::Text("Standalone Recoil Control System");
            ImGui::BeginChild("RCS Container", ImVec2(0, 80), true);
            ImGui::Text("Current Sensitivity : %.2f", player.Sensitivity);
            Checkbox("Enable", &Flags::enableRCS);
            ImGui::EndChild();
        }       
    };

    class Visuals
    {
    public:
        VOID GetPlayerEspWidgets()
        {
            ImGui::Text("Player Esp");
            ImGui::BeginChild("VisualsContainer", ImVec2(0, 520), true);
            Checkbox("Enable Player Esp", &Flags::enablePlayerEsp);
            Checkbox("Team Check", &Config::Esp::enableTeamCheck);
            Checkbox("Box", &Config::Esp::enableEspBoxes);
            Checkbox("Filled", &Config::Esp::enableEspBoxesFilled);
            ColorEditor("Fill Color", &Config::Esp::BoxColorFilled);
            ComboBox("Box Dimension",
                Config::Esp::availableBoxDimensions[Config::Esp::currentBoxDimensionIndex],
                &Config::Esp::currentBoxDimensionIndex, Config::Esp::availableBoxDimensions,
                IM_ARRAYSIZE(Config::Esp::availableBoxDimensions)
            );
            LeaveLine(1);
            ColorEditor("Box Color", &Config::Esp::BoxColorNotFilled);
            Checkbox("Snap Lines", &Config::Esp::enableEspLines);
            ColorEditor("Lines Color", &Config::Esp::LinesColor);
            ComboBox("Line Position",
                Config::Esp::availableSnapLinesPos[Config::Esp::currentlinePosIndex],
                &Config::Esp::currentlinePosIndex, Config::Esp::availableSnapLinesPos,
                IM_ARRAYSIZE(Config::Esp::availableSnapLinesPos)
            );
            LeaveLine(1);
            Checkbox("Entities Name", &Config::Esp::enableEspNames);
            Checkbox("Distance", &Config::Esp::enableDistanceEsp);
            ColorEditor("Name Color", &Config::Esp::NameColor);
            ColorEditor("Distance Text Color", &Config::Esp::DistanceColor);
            Checkbox("Bones", &Config::Esp::enableEspBones);
            Checkbox("Head Fill", &Config::Esp::HeadFilled);
            Checkbox("Show Bone Joints", &Config::Esp::ShowBoneJoints);
            ColorEditor("Bones Color", &Config::Esp::BonesColor);
            ColorEditor("Bone joints Color", &Config::Esp::BoneJointsColor);
            ColorEditor("Head Color", &Config::Esp::HeadColor);
            Checkbox("Health Bar", &Config::Esp::enableEspHealthBar);
            Checkbox("Health Text", &Config::Esp::enableEspHealthPointsText);
            Checkbox("Armor Bar", &Config::Esp::enableEspArmorBar);
            SliderFloat("Box Thickness", &Config::Esp::BoxThickness, 0.5f, 5.0f, "%.1f");
            SliderFloat("Lines Thickness", &Config::Esp::LinesThickness, 0.5f, 5.0f, "%.1f");
            SliderFloat("Bones Thickness", &Config::Esp::BonesThickness, 0.5f, 5.0f, "%.1f");
            SliderFloat("Bone Joints Radius", &Config::Esp::JointRadius, 2.0f, 6.0f, "%.1f");
            ImGui::EndChild();
        }

        VOID GetC4EspWidgets()
        {
            ImGui::Text("Bomb Esp");
            ImGui::BeginChild("Bomb Esp Container", ImVec2(0, 520), true);
            Checkbox("Enable Bomb Esp", &Flags::enableC4Esp);
            ColorEditor("Planted Box Color", &Config::Esp::C4_Planted_Box_Color);
            ColorEditor("Dropped Box Color", &Config::Esp::C4_Dropped_Box_Color);
            Checkbox("Bomb Distance", &Config::Esp::enableC4Distance);
            ColorEditor("Distance Color", &Config::Esp::C4_Distance_Text_Color);
            SliderFloat("C4 Box Thickness", &Config::Esp::C4BoxThickness, 0.5f, 5.0f, "%.1f");               
            LeaveLine(1);
            ImGui::EndChild();
        }

        VOID GetWorldEspWidgets()
        {
            ImGui::Text("World Esp");
            ImGui::BeginChild("World Esp Container", ImVec2(0, 520), true);
            Checkbox("Enable World Esp", &Flags::enableWorldEsp);
            Checkbox("Chicken Esp", &Config::Esp::enableChickensEsp);
            Checkbox("Hostage Esp", &Config::Esp::enableHostagesEsp);
            Checkbox("Weapon Esp", &Config::Esp::enableDroppedWeaponEsp);
            Checkbox("Projectiles Esp", &Config::Esp::enableProjectilesEsp);
            ColorEditor("Chicken Text Color", &Config::Esp::Chicken_Text_Color);
            ColorEditor("Hostage Esp Box Color", &Config::Esp::World_Entities_BoxColor);
            ColorEditor("Weapon Esp Text Color", &Config::Esp::Weapon_Esp_Text_Color);
            ColorEditor("Projectiles Text Color", &Config::Esp::Projectiles_Text_Color);
            ImGui::EndChild();
        }


        //void GetOtherVisualElements()
        //{
        //    Checkbox("Crosshair", &Config::Game::DrawCrosshair);
        //    ColorEditor("Color", &Config::Game::CrosshairColor);
        //    SliderFloat("Size", &Config::Game::CrosshairSize, 2.0f, 50.0f, "%.1f");
        //}

    };

    class Memory
    {
    public:
        VOID GetMovementsWidget()
        {
            ImGui::Text("Movement");
            ImGui::BeginChild("Movement Container", ImVec2(0, 520), true);
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not Safe to Use! Memory Written!");
            Checkbox("Enable Bunny Hop", &Flags::enableBhop);
            ImGui::EndChild();
        }

        VOID GetMemoryWidgets()
        {
            ImGui::Text("Memory Cheats");
            ImGui::BeginChild("Memory Cheats Container", ImVec2(0, 520), true);
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not Safe to Use! Memory Written!");
            Checkbox("Antiflash", &Flags::enableAntiflash);
            //Checkbox("No Sky", &Flags::enableNoSky);
            //Checkbox("No Spread", &Flags::enableNoSpread);
            //Checkbox("Enable Third-Person-Perspective", &Flags::enableTPV);
            //Checkbox("Enable Map-View", &Flags::enableMapView);
            Checkbox("Fov Changer", &Flags::enableFovChanger);
            SliderInt("Field-of-View", &Config::Fov::Default, 58, 140);
            Checkbox("Sensitivity Changer", &Flags::enableSensiChanger);
            SliderFloat("Sensitivity", &Config::Game::Sensitivity, 0.10f, 2000.0f, "%.2f");
            ImGui::EndChild();
        }
    };

    class Misc
    {
    public:
        VOID GetKeyInfoWidgets()
        {
            ImGui::Text("Keybind Info");
            ImGui::BeginChild("Game Info Container", ImVec2(0, 235), true);
            ImGui::TextColored(ImVec4(1, 1, 0, 1), " Cheat Shortcuts");
            LeaveLine(1);

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

            if (Flags::enablePlayerEsp)
            {
                ImGui::TextColored(ImVec4(0, 183, 0, 255), " F3 : Esp Enable/Disable");
            }
            else
            {
                ImGui::Text(" F3 : Esp Enable/Disable");
            }

            //if (Flags::enableTPV)
            //{
            //    ImGui::TextColored(ImVec4(0, 183, 0, 255), " V : Tpp Enable/Disable");
            //}
            //else
            //{
            //    ImGui::Text(" V : Tpp Enable/Disable");
            //}

            LeaveLine(1);
            ImGui::TextColored(ImVec4(1, 1, 0, 1), " Menu Shortcuts");
            LeaveLine(1);
            ImGui::Text(" Insert : HIDE/UNHIDE Menu");
            ImGui::Text(" End : Close Program");
            ImGui::EndChild();
        }

        VOID GetOffsetsDownloaderWidgets()
        {
            ImGui::Text("Offsets Downloader");
            ImGui::BeginChild("Offsets Downloader Container", ImVec2(0, 200), true);

            if (CustomButton("Download Latest Offsets", ImVec2(200.0, 40.0)))
            {
                if (updater.CheckAndDownload())
                {
                    ShowMessage(L"Offsets successfully fetched and downloaded");
                }
                else
                {
                    ShowMessage(L"Failed to fetch and download offsets");
                }
                
            }

            PlainText("If you're unable to download offsets using the button above, try downloading them");
            PlainText("manually from the provided links.");
            const char* Offsets_Json = "https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json";
            const char* Client_Dll_Json = "https://github.com/NeoXa7/Cpp-Updater-Class-for-CS2-Offsets/raw/main/Client_Dll.json";
            const char* Buttons_Json = "https://github.com/a2x/cs2-dumper/raw/main/output/buttons.json";
            ImGui::TextLinkOpenURL("Offsets.json", Offsets_Json);
            ImGui::TextLinkOpenURL("Client_Dll.json", Client_Dll_Json);
            ImGui::TextLinkOpenURL("Buttons.json", Buttons_Json);

            ImGui::EndChild();
        }

        VOID GetOtherSettingsWidget()
        {
            PlainText("Other Settings");
            ImGui::BeginChild("Other Settings Container", ImVec2(0, 120), true);

            Checkbox("Show Console", &Flags::g_showConsole);
            Checkbox("Show Warning", &Flags::g_showWarningBox);

            if(ImGui::Button("Save Settings"))
            {
                SaveSettings("settings.json");
            }

            ImGui::EndChild();
        }

        VOID GetGameInfoWidgets()
        {
            ImGui::Text("Game Info");
            ImGui::BeginChild("Game Info Container", ImVec2(0, 520), true);

            ImGui::Text("Local Player : %s", player.Name);
            ImGui::Text("Ping : %d", player.Ping);
            ImGui::Text("Sensitivity : %.2f", player.Sensitivity);
            ImGui::Text("Mapname : %s", game.MapName);
           // ImGui::Text("Gamemode: %s", game.GetGameModeName().c_str());

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

            ImGui::EndChild();
        }

        VOID GetEntityListWidgets()
        {
            ImGui::Text("Entity List");
            ImGui::BeginChild("Entity List Container", ImVec2(0, 520), true);

            for (int i = 1; i < 64; i++)
            {
                uintptr_t listEntry = mem.ReadMemory<uintptr_t>(game.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
                if (!listEntry)
                    continue;

                uintptr_t currentController = mem.ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
                if (!currentController)
                    continue;

                uint32_t pawnHandle = mem.ReadMemory<uint32_t>(currentController + Offsets::m_hPlayerPawn);
                if (!pawnHandle)
                    continue;

                uintptr_t listEntry2 = mem.ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
                if (!listEntry2)
                    continue;

                uintptr_t currentPawn = mem.ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
                if (!currentPawn)
                    continue;

                entities->UpdateEntities(currentPawn, currentController);

                /*if (player.Team == entities->Team)
                    continue;*/

                if (ImGui::TreeNode(entities->Names))
                {
                    // Team Info
                    switch (entities->Team)
                    {
                    case 1: ImGui::TextColored(Config::Game::SpectatorColor, "Team : Spectator "); break;
                    case 2: ImGui::TextColored(Config::Game::TerroristColor, "Team : Terrorist "); break;
                    case 3: ImGui::TextColored(Config::Game::CounterTerroristColor, "Team : Counter-Terrorist "); break;
                    default: ImGui::Text("Team : ~Unknown"); break;
                    }

                    // Health and Armor Info
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

                    // Fire State and isScoped Info
                    if (entities->IsFiring)
                    {
                        ImGui::Text("IsFiring : True");
                    }
                    else
                    {
                        ImGui::Text("IsFiring : False");
                    }

                    if (entities->IsScoped)
                    {
                        ImGui::Text("IsScoped : True");
                    }
                    else
                    {
                        ImGui::Text("IsScoped : False");
                    }

                    // Ping and Position Info;
                    ImGui::Text("Ping : %d", entities->Ping);
                    ImGui::Text("Position (x, y, z) : %.2f, %.2f, %.2f", entities->Position.x, entities->Position.y, entities->Position.z);

                    ImGui::TreePop();
                }
            }

            ImGui::EndChild();
        }

        VOID GetConfigWidgets()
        {
            ImGui::Text("Config");

            ImGui::BeginChild("Config Container", ImVec2(0, 520), true);

            static char configFileNameBuffer[128] = "config";

            if (ImGui::Button("Refresh JSON Files"))
            {
                ScanDirectoryForJsonFiles(".");
            }

            if (!jsonFiles.empty())
            {
                static int selectedFileIndex = 0;
                std::vector<const char*> items;
                for (size_t i = 0; i < jsonFiles.size(); ++i)
                {
                    items.push_back(jsonFiles[i].c_str());
                }

                const char* selectedFileName = items[selectedFileIndex];
                if (ComboBox("Available Config Files", selectedFileName, &selectedFileIndex, items.data(), items.size()))
                {
                    ConfigFileName = jsonFiles[selectedFileIndex];
                }
            }
            else
            {
                ImGui::Text("No JSON files found.");
            }

            if (ImGui::InputText("Config File Name", configFileNameBuffer, sizeof(configFileNameBuffer)))
            {
                ConfigFileName = std::string(configFileNameBuffer);
            }

            // Save Config Button
            if (ImGui::Button("Save Config"))
            {
                SaveConfig(ConfigFileName);
            }

            // Load Config Button
            if (ImGui::Button("Load Config"))
            {
                LoadConfig(ConfigFileName);
            }

            ImGui::EndChild();
        }
    };

    VOID ProcessInputs()
    {
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            Flags::IsVisible = !Flags::IsVisible; // Hide/Unhide Menu;
        }

        if (GetAsyncKeyState(VK_END) & 1) {
            Flags::IsRunning = false; // Close Program;
        }
    }

    friend VOID RenderMenu();
};

VOID RenderMenu()
{
    Interfaces interfaces;
    Interfaces::Aim aim;
    Interfaces::Visuals visuals;
    Interfaces::Memory memory;
    Interfaces::Misc misc;

    interfaces.ProcessInputs();
    SetCustomStyle();
    if (Flags::IsVisible)
    {
        ImGui::Begin("Cs2 External Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowSize(ImVec2(MIN_MENU_WIDTH, MIN_MENU_HEIGHT));

        ImGui::PushFont(ImGui_Loader::Font_Size_17);
        LeaveLine(1);
        PlainText("     Ins To Show/Hide Menu", ImVec4(0, 183, 0, 255));
        ImGui::PopFont();
        
        CenterText("Cs2 External v4.8. Last Updated 19th October 2024");
        LeaveLine(1);

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, 180);

        ImGui::BeginChild("Buttons Tab Container", ImVec2(0, 475), true);
        if (CustomButton("Game Info"))
        {
            currentOption = MenuOption::GameInfo;
        }
        if (CustomButton("Aim"))
        {
            currentOption = MenuOption::Aim;
        }
        if (CustomButton("Player Esp"))
        {
            currentOption = MenuOption::Player_Esp;
        }
        if (CustomButton("World Esp"))
        {
            currentOption = MenuOption::World_Esp;
        }
        if (CustomButton("Bomb Esp"))
        {
            currentOption = MenuOption::Bomb_Esp;
        }
        if (CustomButton("Movement"))
        {
            currentOption = MenuOption::Movement;
        }
        if (CustomButton("Memory"))
        {
            currentOption = MenuOption::Memory;
        }
        if (CustomButton("Entity List"))
        {
            currentOption = MenuOption::EntityList;
        }
        if (CustomButton("Misc"))
        {
            currentOption = MenuOption::Misc;
        }
        if (CustomButton("Configs"))
        {
            currentOption = MenuOption::Configs;
        }
        ImGui::EndChild();

        ImGui::PushFont(ImGui_Loader::Font_Size_17);
        ImGui::BeginChild("Bottom Text Container", ImVec2(0, 65), true);
        CenterText("Developer : NeoXa7");
        LeaveLine();
        CenterText("UI Version : 2.0");
        ImGui::EndChild();
        ImGui::PopFont();

        ImGui::NextColumn();

        switch (currentOption)
        {
        case MenuOption::GameInfo:
            misc.GetGameInfoWidgets();
            break;
        case MenuOption::Aim:
            ImGui::PushFont(ImGui_Loader::Font_Size_17);
            aim.GetAimbotWidgets();
            aim.GetTriggerBotWidgets();
            ImGui::PopFont();
            aim.GetRCSWidgets();
            break;
        case MenuOption::Player_Esp:
            ImGui::PushFont(ImGui_Loader::Font_Size_17);
            visuals.GetPlayerEspWidgets();
            ImGui::PopFont();
            break;
        case MenuOption::World_Esp:
            visuals.GetWorldEspWidgets();
            break;
        case MenuOption::Bomb_Esp:
            visuals.GetC4EspWidgets();
            break;
        case MenuOption::Movement:
            memory.GetMovementsWidget();
            break;
        case MenuOption::Memory:
            memory.GetMemoryWidgets();
            break;
        case MenuOption::EntityList:
            misc.GetEntityListWidgets();
            break;
        case MenuOption::Misc:
            misc.GetKeyInfoWidgets();
            misc.GetOffsetsDownloaderWidgets();
            misc.GetOtherSettingsWidget();
            break;
        case MenuOption::Configs:
            misc.GetConfigWidgets();
            break;
        default:
            ImGui::Text("Select an option from the left.");
            break;
        }

        ImGui::Columns(1); // Reset columns
        ImGui::End(); // End the window
    } 
}
