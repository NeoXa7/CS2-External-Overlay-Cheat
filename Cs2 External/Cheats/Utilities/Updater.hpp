#pragma once
#include <Windows.h>
#include <WinINet.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <Json/Json.hpp>
#include <Globals/Globals.hpp>

using json = nlohmann::json;
namespace fileSys = std::filesystem;
using namespace std;

#ifdef _WIN32
std::time_t timegm(std::tm* tm) {
    std::time_t t = _mkgmtime(tm);
    return t;
}
#endif _WIN32

class Updater {
private:
    std::vector<std::string> Files = { "offsets.json", "client_dll.json", "buttons.json" };
    string a2x_dumper_api = "https://api.github.com/repos/a2x/cs2-dumper/commits";

    const std::vector<std::pair<std::string, std::string>> file_paths_github = {
        {"https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json", "offsets.json"},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/client_dll.json", "client_dll.json"},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/buttons.json", "buttons.json"},
    };

    inline bool FileExists(const std::string& name) {
        std::ifstream f(name.c_str());
        return f.good();
    }

    inline bool DownloadFile(const std::string& url, const std::string& fileName) {
        HINTERNET hInternet, hConnect;

        hInternet = InternetOpen(L"Updater", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) {
            std::cout << " [Updater] InternetOpen failed." << std::endl;
            return false;
        }

        hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (!hConnect) {
            std::cout << " [Updater] InternetOpenUrlA failed." << std::endl;
            InternetCloseHandle(hInternet);
            return false;
        }

        std::ofstream outFile(fileName, std::ios::binary);
        if (!outFile) {
            std::cout << " [Updater] Failed to create local file: " << fileName << std::endl;
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return false;
        }

        char buffer[4096];
        DWORD bytesRead;

        while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
            outFile.write(buffer, bytesRead);
        }

        outFile.close();
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);

        return true;
    }


    inline bool GetLastCommitInfo(string api, json& commit) {
        HINTERNET hInternet, hConnect;

        hInternet = InternetOpen(L"Updater", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) {
            return false;
        }

        hConnect = InternetOpenUrlA(hInternet, api.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (!hConnect) {
            InternetCloseHandle(hInternet);
            return false;
        }

        char buffer[4096];
        DWORD bytesRead;
        std::string commitData;

        while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
            commitData.append(buffer, bytesRead);
        }

        json data;
        try {
            data = json::parse(commitData);
        }
        catch (const std::exception& e) {
            std::cout << " [Updater] Failed to parse JSON response from GitHub" << std::endl;
            return false;
        }

        if (data.empty())
            return false;

        if (data.is_array()) {
            json last_commit = data[0];
            json last_commit_author = last_commit["commit"]["author"];
            commit = last_commit_author;
        }

        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);

        return true;
    }

    inline bool ParseJsonFromFile(const std::string& fileName, json& outJson) {
        std::ifstream inFile(fileName, std::ios::binary);
        if (!inFile) {
            std::cerr << " [Updater] Failed to open " << fileName << "." << std::endl;
            return false;
        }

        std::string fileContent((std::istreambuf_iterator<char>(inFile)),
            std::istreambuf_iterator<char>());
        inFile.close();

        try {
            outJson = json::parse(fileContent);
        }
        catch (const json::parse_error& e) {
            std::cerr << " [Updater] JSON parse error in " << fileName
                << " at byte " << e.byte << ": " << e.what() << std::endl;
            return false;
        }

        return true;
    }

public:
    inline bool CheckAndDownload() {
        // Ensure the directory exists
        std::string directory = "offsets";
        if (!std::filesystem::exists(directory)) {
            std::filesystem::create_directory(directory);
        }

        json a2x_dumper_commit;

        // Get the last commit information from GitHub
        if (!GetLastCommitInfo(a2x_dumper_api, a2x_dumper_commit)) {
            std::cout << " [Updater] Error getting last commit information from GitHub" << std::endl;
            return false;
        }

        string A2X_Last_Commit_Date = a2x_dumper_commit["date"];
        std::tm Commit_Date_Buffer_A2X = {};
        std::istringstream ssA2X(A2X_Last_Commit_Date);
        ssA2X >> std::get_time(&Commit_Date_Buffer_A2X, "%Y-%m-%dT%H:%M:%SZ");
        std::time_t commit_time_t_A2X = timegm(&Commit_Date_Buffer_A2X);
        auto CommitTimePoint_A2X = std::chrono::system_clock::from_time_t(commit_time_t_A2X);

        for (const auto& file : file_paths_github) {
            const auto& url = file.first;
            std::string localPath = directory + "/" + file.second; // Store files in the offsets directory

            bool fileExists = FileExists(localPath);
            auto lastModifiedTime = fileExists ? fileSys::last_write_time(localPath) : fileSys::file_time_type{};

            auto lastModifiedClockTime = fileExists
                ? std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    lastModifiedTime - fileSys::file_time_type::clock::now() + std::chrono::system_clock::now())
                : std::chrono::system_clock::time_point{};

            if (fileExists && lastModifiedClockTime >= CommitTimePoint_A2X) {
                std::cout << " [Updater] " << localPath << " is Up-to-Date." << std::endl;
            }
            else {
                if (Updater::DownloadFile(url, localPath)) {
                    std::cout << " [Updater] Successfully downloaded or updated " << localPath << "." << std::endl;
                }
                else {
                    std::cout << " [Updater] Error: Failed to download " << localPath << ". Try downloading manually from " << url << std::endl;
                }
            }
        }
        return true;
    }

    inline bool UpdateOffsets() {
        std::string directory = "offsets";
        for (const auto& file : Files) {
            std::string filePath = directory + "/" + file;
            json Data;
            if (!FileExists(filePath)) {
                std::cerr << " [Updater] " << filePath << " not found." << std::endl;
                continue;
            }

            if (!ParseJsonFromFile(filePath, Data)) {
                return false;
            }

            const auto& Client = Data["client.dll"];
            const auto& Matchmaking = Data["matchmaking.dll"];

            if (file == "offsets.json")
            {
                Offsets::dwEntityList = Client["dwEntityList"];
                Offsets::dwLocalPlayerPawn = Client["dwLocalPlayerPawn"];
                Offsets::dwLocalPlayerController = Client["dwLocalPlayerController"];
                Offsets::dwViewAngles = Client["dwViewAngles"];
                Offsets::dwViewMatrix = Client["dwViewMatrix"];
                Offsets::dwSensitivity = Client["dwSensitivity"];
                Offsets::dwSensitivity_sensitivity = Client["dwSensitivity_sensitivity"];
                Offsets::dwGameRules = Client["dwGameRules"];
                Offsets::dwPlantedC4 = Client["dwPlantedC4"];
                Offsets::dwGlobalVars = Client["dwGlobalVars"];
                Offsets::dwWeaponC4 = Client["dwWeaponC4"];
                Offsets::dwGameTypes = Matchmaking["dwGameTypes"];
                Offsets::dwGameTypes_mapName = Matchmaking["dwGameTypes_mapName"];
            }
            else if (file == "client_dll.json")
            {
                json client = Data.contains("client.dll");

                if (Data.contains("client.dll") && Data["client.dll"].contains("classes")) {
                    auto& classes = Data["client.dll"]["classes"];

                    if (classes.contains("C_CSPlayerPawn")) {
                        auto& C_CSPlayerPawn = classes["C_CSPlayerPawn"]["fields"];
                        Offsets::m_ArmorValue = C_CSPlayerPawn["m_ArmorValue"];
                        Offsets::m_iShotsFired = C_CSPlayerPawn["m_iShotsFired"];
                        Offsets::m_aimPunchAngle = C_CSPlayerPawn["m_aimPunchAngle"];
                        Offsets::m_bIsScoped = C_CSPlayerPawn["m_bIsScoped"];
                    }

                    if (classes.contains("C_BaseEntity")) {
                        auto& C_BaseEntity = classes["C_BaseEntity"]["fields"];
                        Offsets::m_iTeamNum = C_BaseEntity["m_iTeamNum"];
                        Offsets::m_iHealth = C_BaseEntity["m_iHealth"];
                        Offsets::m_pGameSceneNode = C_BaseEntity["m_pGameSceneNode"];
                        Offsets::m_fFlags = C_BaseEntity["m_fFlags"];
                        Offsets::m_vecAbsVelocity = C_BaseEntity["m_vecAbsVelocity"];
                        Offsets::m_hOwnerEntity = C_BaseEntity["m_hOwnerEntity"];
                    }

                    if (classes.contains("CCSPlayerController")) {
                        auto& CCSPlayerController = classes["CCSPlayerController"]["fields"];
                        Offsets::m_hPlayerPawn = CCSPlayerController["m_hPlayerPawn"];
                        Offsets::m_sSanitizedPlayerName = CCSPlayerController["m_sSanitizedPlayerName"];
                        Offsets::m_iPing = CCSPlayerController["m_iPing"];
                    }

                    if (classes.contains("C_CSPlayerPawnBase")) {
                        auto& C_CSPlayerPawnBase = classes["C_CSPlayerPawnBase"]["fields"];
                        Offsets::m_flFlashBangTime = C_CSPlayerPawnBase["m_flFlashBangTime"];
                        Offsets::m_iIDEntIndex = C_CSPlayerPawnBase["m_iIDEntIndex"];
                    }

                    if (classes.contains("C_BasePlayerPawn")) {
                        auto& C_BasePlayerPawn = classes["C_BasePlayerPawn"]["fields"];
                        Offsets::m_vOldOrigin = C_BasePlayerPawn["m_vOldOrigin"];
                    }

                    if (classes.contains("C_BaseModelEntity")) {
                        auto& C_BaseModelEntity = classes["C_BaseModelEntity"]["fields"];
                        Offsets::m_vecViewOffset = C_BaseModelEntity["m_vecViewOffset"];
                    }

                    if (classes.contains("C_CSGameRules")) {
                        auto& C_CSGameRules = classes["C_CSGameRules"]["fields"];
                        Offsets::m_bBombPlanted = C_CSGameRules["m_bBombPlanted"];
                        Offsets::m_bBombDropped = C_CSGameRules["m_bBombDropped"];
                        Offsets::m_bWarmupPeriod = C_CSGameRules["m_bWarmupPeriod"];
                    }


                    if (classes.contains("C_PlantedC4")) {
                        auto& C_PlantedC4 = classes["C_PlantedC4"]["fields"];
                        Offsets::m_nBombSite = C_PlantedC4["m_nBombSite"];
                        Offsets::m_bHasExploded = C_PlantedC4["m_bHasExploded"];
                        Offsets::m_bBeingDefused = C_PlantedC4["m_bBeingDefused"];
                        Offsets::m_flDefuseLength = C_PlantedC4["m_flDefuseLength"];
                    }

                    if (classes.contains("CGameSceneNode")) {
                        auto& CGameSceneNode = classes["CGameSceneNode"]["fields"];
                        Offsets::m_vecAbsOrigin = CGameSceneNode["m_vecAbsOrigin"];
                    }
                }
            }
            else if (file == "buttons.json")
            {
                Offsets::dwForceAttack = Client["attack"];
                Offsets::dwForceAttack2 = Client["attack2"];
                Offsets::dwForceJump = Client["jump"];
            }
        }
        return true;
    }
};

inline Updater updater;