#pragma once
#include <fstream>
#include <Json/Json.hpp>
#include <Globals/Globals.hpp>
#include <filesystem>
#include <Interfaces/LSConfigSystem.hpp>

using json = nlohmann::json;

void SaveSettings(const std::string& filename)
{
    json ExeJsonConfig;

    ExeJsonConfig["Settings"]["g_showWarningBox"] = Flags::g_showWarningBox;
    ExeJsonConfig["Settings"]["g_showConsole"] = Flags::g_showConsole;

    std::ofstream file(filename);
    if (file.is_open())
    {
        file << ExeJsonConfig.dump(4); // Save with 4-space indentation
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to save settings to " << filename << std::endl;
    }
}

void LoadSettings(const std::string& filename)
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

    if (Data.contains("Settings"))
    {
        const auto& Settings = Data["Settings"];
        Flags::g_showWarningBox = Settings.value("g_showWarningBox", true);
        Flags::g_showConsole = Settings.value("g_showConsole", true);
    }
}