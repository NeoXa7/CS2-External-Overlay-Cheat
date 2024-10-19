#pragma once
#include <fstream>
#include <Json/Json.hpp>
#include <Utilities/Config.hpp>
#include <Globals/Globals.hpp>
#include <filesystem>

using json = nlohmann::json;
std::string ConfigFileName = "config";
namespace fs = std::filesystem;
std::vector<std::string> jsonFiles;

inline bool FileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void ScanDirectoryForJsonFiles(const std::string& path)
{
    jsonFiles.clear(); // Clear previous results
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".json")
        {
            jsonFiles.push_back(entry.path().filename().string());
        }
    }
}

void SaveConfig(const std::string& filename)
{
    json jsonConfig;
    ImColor BoxColor = Config::Esp::BonesColor; // Default white;
    ImColor LinesColor = Config::Esp::LinesColor; // Default white;
    ImColor NameColor = Config::Esp::NameColor; // Default white;
    ImColor BonesColor = Config::Esp::BonesColor; // Default white;
    ImColor HeadColor = Config::Esp::HeadColor; // Default white;
    ImColor DistanceColor = Config::Esp::DistanceColor; // Default white;
    ImColor C4_Box_Color = Config::Esp::C4_Planted_Box_Color; // Default white;
    ImColor C4_Distance_Text_Color = Config::Esp::C4_Distance_Text_Color; // Default white;

    ImColor Weapon_Esp_Text_Color = Config::Esp::Weapon_Esp_Text_Color; // Default Yellow;
    ImColor Projectiles_Text_Color = Config::Esp::Projectiles_Text_Color; // Default Red;
    ImColor Chicken_Text_Color = Config::Esp::Chicken_Text_Color; // Default white;
    ImColor World_Entities_BoxColor = Config::Esp::World_Entities_BoxColor; // Default white;

    auto colorToJson = [](const ImColor& color) {
        return json{ color.Value.x, color.Value.y, color.Value.z, color.Value.w };
        };
    

    // Aimbot
    jsonConfig["Aimbot"]["enableAimbot"] = Flags::enableAimbot;
    jsonConfig["Aimbot"]["enableHotKey"] = Config::Aimbot::enableHotKey;
    jsonConfig["Aimbot"]["CurrentAimPosIndex"] = Config::Aimbot::CurrentAimPosIndex;
    jsonConfig["Aimbot"]["CurrentHotKeyIndex"] = Config::Aimbot::CurrentHotkeyIndex;
    jsonConfig["Aimbot"]["TeamCheck"] = Config::Aimbot::TeamCheck;

    // TriggerBot
    jsonConfig["TriggerBot"]["enableTriggerbot"] = Flags::enableTriggerbot;
    jsonConfig["TriggerBot"]["enableHotKey"] = Config::TriggerBot::enableHotKey;
    jsonConfig["TriggerBot"]["enableTeamCheck"] = Config::TriggerBot::enableTeamCheck;
    jsonConfig["TriggerBot"]["CurrentHotkeyIndex"] = Config::TriggerBot::CurrentHotkeyIndex;

    // RCS
    jsonConfig["RCS"]["enableRCS"] = Flags::enableRCS;

    // Esp
    jsonConfig["Esp"]["enablePlayerEsp"] = Flags::enablePlayerEsp;
    jsonConfig["Esp"]["enableBombEsp"] = Flags::enableC4Esp;
    jsonConfig["Esp"]["enableWorldEsp"] = Flags::enableWorldEsp;
    jsonConfig["Esp"]["enableEspBoxes"] = Config::Esp::enableEspBoxes;
    jsonConfig["Esp"]["enableEspLines"] = Config::Esp::enableEspLines;
    jsonConfig["Esp"]["enableEspHealthBar"] = Config::Esp::enableEspHealthBar;
    jsonConfig["Esp"]["enableEspArmorBar"] = Config::Esp::enableEspArmorBar;
    jsonConfig["Esp"]["enableEspNames"] = Config::Esp::enableEspNames;
    jsonConfig["Esp"]["enableDistanceEsp"] = Config::Esp::enableDistanceEsp;
    jsonConfig["Esp"]["enableEspBones"] = Config::Esp::enableEspBones;
    jsonConfig["Esp"]["enableEspHealthPointsText"] = Config::Esp::enableEspHealthPointsText;
    jsonConfig["Esp"]["enableTeamCheck"] = Config::Esp::enableTeamCheck;
    jsonConfig["Esp"]["HeadFilled"] = Config::Esp::HeadFilled;
    jsonConfig["Esp"]["ShowBoneJoints"] = Config::Esp::ShowBoneJoints;
    jsonConfig["Esp"]["enableC4Box"] = Config::Esp::enableC4Box;
    jsonConfig["Esp"]["enableC4StatusEsp"] = Config::Esp::enableC4StatusEsp;
    jsonConfig["Esp"]["enableC4Distance"] = Config::Esp::enableC4Distance;
    jsonConfig["Esp"]["enableChickensEsp"] = Config::Esp::enableChickensEsp;
    jsonConfig["Esp"]["enableHostagesEsp"] = Config::Esp::enableHostagesEsp;
    jsonConfig["Esp"]["enableDroppedWeaponEsp"] = Config::Esp::enableDroppedWeaponEsp;
    jsonConfig["Esp"]["enableProjectilesEsp"] = Config::Esp::enableProjectilesEsp;
    jsonConfig["Esp"]["BoxThickness"] = Config::Esp::BoxThickness;
    jsonConfig["Esp"]["BonesThickness"] = Config::Esp::BonesThickness;
    jsonConfig["Esp"]["C4BoxThickness"] = Config::Esp::C4BoxThickness;
    jsonConfig["Esp"]["LinesThickness"] = Config::Esp::LinesThickness;
    jsonConfig["Esp"]["currentBoxDimensionIndex"] = Config::Esp::currentBoxDimensionIndex;
    jsonConfig["Esp"]["currentlinePosIndex"] = Config::Esp::currentlinePosIndex;
    // Esp colors
    jsonConfig["Esp"]["BoxColor"] = colorToJson(Config::Esp::BoxColorNotFilled);
    jsonConfig["Esp"]["BonesColor"] = colorToJson(Config::Esp::BonesColor);
    jsonConfig["Esp"]["LinesColor"] = colorToJson(Config::Esp::LinesColor);
    jsonConfig["Esp"]["NameColor"] = colorToJson(Config::Esp::NameColor);
    jsonConfig["Esp"]["HeadColor"] = colorToJson(Config::Esp::HeadColor);
    jsonConfig["Esp"]["DistanceColor"] = colorToJson(Config::Esp::DistanceColor);
    jsonConfig["Esp"]["C4_Box_Color"] = colorToJson(Config::Esp::C4_Planted_Box_Color);
    jsonConfig["Esp"]["C4_Distance_Text_Color"] = colorToJson(Config::Esp::C4_Distance_Text_Color);
    jsonConfig["Esp"]["Weapon_Esp_Text_Color"] = colorToJson(Config::Esp::Weapon_Esp_Text_Color);
    jsonConfig["Esp"]["Projectiles_Text_Color"] = colorToJson(Config::Esp::Projectiles_Text_Color);
    jsonConfig["Esp"]["Chicken_Text_Color"] = colorToJson(Config::Esp::Chicken_Text_Color);
    jsonConfig["Esp"]["World_Entities_BoxColor"] = colorToJson(Config::Esp::World_Entities_BoxColor);
    
    string filenameExtJson = filename + ".json";

    std::ofstream file(filenameExtJson);
    if (file.is_open())
    {
        file << jsonConfig.dump(4); // Save with 4-space indentation
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to save config to " << filename << std::endl;
    }
}

void LoadConfig(const std::string& filename)
{
    json Data;

    if (!FileExists(filename)) {
       // std::cout << filename << " not found." << std::endl;
        return;
    }

    std::ifstream inFile(filename);
    if (!inFile) {
       // std::cout << "    Failed to open " << filename << "." << std::endl;
        return;
    }

    try {
        inFile >> Data;
    }
    catch (const std::exception& e) {
       // std::cout << "  Failed to parse JSON from " << filename << ": " << e.what() << std::endl;
        return;
    }

    auto jsonToColor = [](const json& colorJson) -> ImColor {
        if (colorJson.is_array() && colorJson.size() == 4) {
            return ImColor(colorJson[0].get<float>(), colorJson[1].get<float>(), colorJson[2].get<float>(), colorJson[3].get<float>());
        }
        return ImColor(1.0f, 1.0f, 1.0f, 1.0f); // Default to white if not found
        };


    // Aimbot
    if (Data.contains("Aimbot")) {
        const auto& Aimbot = Data["Aimbot"];
        Flags::enableAimbot = Aimbot.value("enableAimbot", false);
        Config::Aimbot::enableHotKey = Aimbot.value("enableHotKey", true);
        Config::Aimbot::CurrentAimPosIndex = Aimbot.value("CurrentAimPosIndex", 0);
        Config::Aimbot::CurrentHotkeyIndex = Aimbot.value("CurrentHotKeyIndex", 0);
        Config::Aimbot::TeamCheck = Aimbot.value("TeamCheck", false);
    }

    // Triggerbot
    if (Data.contains("TriggerBot")) {
        const auto& TriggerBot = Data["TriggerBot"];
        Flags::enableTriggerbot = TriggerBot.value("enableTriggerbot", false);
        Config::TriggerBot::enableHotKey = TriggerBot.value("enableHotKey", false);
        Config::TriggerBot::enableTeamCheck = TriggerBot.value("enableTeamCheck", false);
        Config::TriggerBot::CurrentHotkeyIndex = TriggerBot.value("CurrentHotkeyIndex", 0);
    }

    // Esp
    if (Data.contains("Esp")) {
        const auto& Esp = Data["Esp"];
        Flags::enablePlayerEsp = Esp.value("enablePlayerEsp", false);
        Flags::enableC4Esp = Esp.value("enableC4Esp", false);
        Flags::enableWorldEsp = Esp.value("enableWorldEsp", false);
        Config::Esp::enableEspBoxes = Esp.value("enableEspBoxes", false);
        Config::Esp::enableEspLines = Esp.value("enableEspLines", false);
        Config::Esp::enableEspHealthBar = Esp.value("enableEspHealthBar", false);
        Config::Esp::enableEspArmorBar = Esp.value("enableEspArmorBar", false);
        Config::Esp::enableEspNames = Esp.value("enableEspNames", false);
        Config::Esp::enableDistanceEsp = Esp.value("enableDistanceEsp", false);
        Config::Esp::enableEspBones = Esp.value("enableEspBones", false);
        Config::Esp::enableEspHealthPointsText = Esp.value("enableEspHealthPointsText", false);
        Config::Esp::enableTeamCheck = Esp.value("enableTeamCheck", false);
        Config::Esp::HeadFilled = Esp.value("HeadFilled", false);
        Config::Esp::ShowBoneJoints = Esp.value("ShowBoneJoints", false);
        Config::Esp::enableC4Box = Esp.value("enableC4Box", false);
        Config::Esp::enableC4StatusEsp = Esp.value("enableC4StatusEsp", false);
        Config::Esp::enableC4Distance = Esp.value("enableC4Distance", false);
        Config::Esp::enableChickensEsp = Esp.value("enableChickensEsp", false);
        Config::Esp::enableHostagesEsp = Esp.value("enableHostagesEsp", false);
        Config::Esp::enableDroppedWeaponEsp = Esp.value("enableDroppedWeaponEsp", false);
        Config::Esp::enableProjectilesEsp = Esp.value("enableProjectilesEsp", false);
        Config::Esp::BoxThickness = Esp.value("BoxThickness", 1.0f);
        Config::Esp::BonesThickness = Esp.value("BonesThickness", 0.5f);
        Config::Esp::C4BoxThickness = Esp.value("C4BoxThickness", 2.5f);
        Config::Esp::LinesThickness = Esp.value("LinesThickness", 1.5f);
        Config::Esp::currentBoxDimensionIndex = Esp.value("currentBoxDimensionIndex", 0);
        Config::Esp::currentlinePosIndex = Esp.value("currentlinePosIndex", 0);

        // Colors
        Config::Esp::BonesColor = jsonToColor(Esp["BonesColor"]);
        Config::Esp::BoxColorNotFilled = jsonToColor(Esp["BoxColor"]);
        Config::Esp::LinesColor = jsonToColor(Esp["LinesColor"]);
        Config::Esp::NameColor = jsonToColor(Esp["NameColor"]);
        Config::Esp::HeadColor = jsonToColor(Esp["HeadColor"]);
        Config::Esp::DistanceColor = jsonToColor(Esp["DistanceColor"]);
        Config::Esp::C4_Planted_Box_Color = jsonToColor(Esp["C4_Box_Color"]);
        Config::Esp::C4_Distance_Text_Color = jsonToColor(Esp["C4_Distance_Text_Color"]);
        Config::Esp::Weapon_Esp_Text_Color = jsonToColor(Esp["Weapon_Esp_Text_Color"]);
        Config::Esp::Projectiles_Text_Color = jsonToColor(Esp["Projectiles_Text_Color"]);
        Config::Esp::Chicken_Text_Color = jsonToColor(Esp["Chicken_Text_Color"]);
        Config::Esp::World_Entities_BoxColor = jsonToColor(Esp["World_Entities_BoxColor"]);
    }    

    if (Data.contains("RCS"))
    {
        const auto& RCS = Data["RCS"];
        Flags::enableRCS = RCS.value("enableRCS", false);
    }
}