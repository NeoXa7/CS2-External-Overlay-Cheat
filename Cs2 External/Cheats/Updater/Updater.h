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

using json = nlohmann::json;
namespace fileSys = std::filesystem;
using namespace std;

#ifdef _WIN32
std::time_t timegm(std::tm* tm) {
    std::time_t t = _mkgmtime(tm);  // Use _mkgmtime on Windows for UTC time
    return t;
}
#endif _WIN32

class Updater {
private:
    std::vector<std::string> FileName = { "offsets.json", "Client_Dll.json", "buttons.json" };
    string Github_Repo_Api_A2X = "https://api.github.com/repos/a2x/cs2-dumper/commits";
    string Github_Repo_Api_NeoXa7 = "https://api.github.com/repos/NeoXa7/Cpp-Updater-Class-for-CS2-Offsets/commits";

    const std::vector<std::pair<std::string, std::string>> Github_File_Path = {
        {"https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json", "offsets.json"},
        {"https://github.com/NeoXa7/Cpp-Updater-Class-for-CS2-Offsets/raw/main/Client_Dll.json", "Client_Dll.json"},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/buttons.json", "buttons.json"},
        // Add more files here as needed
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
            std::cout << " [Updater] Failed to create local file." << std::endl;
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

public:
    inline bool CheckAndDownload() {
        json A2x_Commit, NeoXa7_Commit;

        // Get the last commit information from GitHub
        if (!GetLastCommitInfo(Github_Repo_Api_A2X, A2x_Commit)) {
            std::cout << " [Updater] Error getting last commit information from GitHub" << std::endl;
            return false;
        }

        if (!GetLastCommitInfo(Github_Repo_Api_NeoXa7, NeoXa7_Commit)) {
            std::cout << " [Updater] Error getting last commit information from GitHub" << std::endl;
            return false;
        }

        // a2x dumper;
        string A2X_Last_Commit_Date = A2x_Commit["date"];
        string A2X_Last_Commit_Author_Name = A2x_Commit["name"];

        std::tm Commit_Date_Buffer_A2X = {};
        std::istringstream ssA2X(A2X_Last_Commit_Date);
        ssA2X >> std::get_time(&Commit_Date_Buffer_A2X, "%Y-%m-%dT%H:%M:%SZ");

        std::time_t commit_time_t_A2X = timegm(&Commit_Date_Buffer_A2X);
        auto CommitTimePoint_A2X = std::chrono::system_clock::from_time_t(commit_time_t_A2X);

        std::tm commit_time_tm_A2X;
        gmtime_s(&commit_time_tm_A2X, &commit_time_t_A2X);

        // neo7 
        string NeoXa7_Last_Commit_Date = NeoXa7_Commit["date"];
        string NeoXa7_Last_Commit_Author_Name = NeoXa7_Commit["name"];

        std::tm Commit_Date_Buffer_NeoXa7 = {};
        std::istringstream ssNeo7(NeoXa7_Last_Commit_Date);
        ssNeo7 >> std::get_time(&Commit_Date_Buffer_NeoXa7, "%Y-%m-%dT%H:%M:%SZ");

        std::time_t commit_time_t_NeoXa7 = timegm(&Commit_Date_Buffer_NeoXa7);
        auto CommitTimePoint_NeoXa7 = std::chrono::system_clock::from_time_t(commit_time_t_NeoXa7);

        std::tm commit_time_tm_NeoXa7;
        gmtime_s(&commit_time_tm_NeoXa7, &commit_time_t_NeoXa7);


        for (const auto& file : Github_File_Path) {
            const auto& url = file.first;
            const auto& localPath = file.second;

            bool fileExists = FileExists(localPath);
            auto lastModifiedTime = fileExists ? fileSys::last_write_time(localPath) : fileSys::file_time_type{};

            auto lastModifiedClockTime = fileExists
                ? std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    lastModifiedTime - fileSys::file_time_type::clock::now() + std::chrono::system_clock::now())
                : std::chrono::system_clock::time_point{};

            if (fileExists) {
                if (lastModifiedClockTime < CommitTimePoint_A2X || lastModifiedClockTime < CommitTimePoint_NeoXa7) {
                    if (localPath == "buttons.json")
                    {
                        if (DownloadFile(url, localPath)) {
                            std::cout << " [Updater] buttons.json : Successfully Updated to latest Offsets\n";
                        }
                        else {
                            std::cout << " [Updater] Failed to Update to the latest Offsets. File Name : " << localPath << " Try downloading manually from " << url << '\n';
                        }
                    }

                    if (localPath == "offsets.json")
                    {
                        if (DownloadFile(url, localPath)) {
                            std::cout << " [Updater] offsets.json : Successfully Updated to latest Offsets\n";
                        }
                        else {
                            std::cout << " [Updater] Failed to Update to the latest Offsets. File Name : " << localPath << " Try downloading manually from " << url << '\n';
                        }
                    }

                    if (localPath == "Client_Dll.json")
                    {

                        if (DownloadFile(url, localPath)) {
                            std::cout << " [Updater] Client_Dll.json : Successfully Updated to latest Offsets\n";
                        }
                        else {
                            std::cout << " [Updater] Failed to Update to the latest Offsets. File Name : " << localPath << " Try downloading manually from " << url << '\n';
                        }
                    }
                }
            }
            else if (!fileExists) {
                if (DownloadFile(url, localPath)) {
                    std::cout << " [Updater] Successfully downloaded the latest " << localPath << "." << std::endl;
                }
                else {
                    std::cout << " [Updater] Error: Failed to download " << localPath << ". Try downloading manually from " << url << std::endl;
                }
            }
            else {
                std::cout << " [Updater] " << localPath << " is Up-to-Date." << std::endl;
            }

        }
        return true;
    }

    inline bool UpdateOffsets() {
        
        json Data;

        for (const auto& FileNames : FileName) {
            if (!FileExists(FileNames)) {
                std::cout << " [Updater] " << FileNames << " not found." << std::endl;
                continue;
            }

            std::ifstream inFile(FileNames);
            if (!inFile) {
                std::cout << " [Updater] Failed to open " << FileNames << "." << std::endl;
                return false;
            }

            try {
                inFile >> Data;
            }
            catch (const std::exception& e) {
                std::cout << " [Updater] Failed to parse JSON from " << FileNames << ": " << e.what() << std::endl;
                return false;
            }

            const auto& Client = Data["client.dll"];
            const auto& Matchmaking = Data["matchmaking.dll"];
            const auto& C_BaseEntity = Data["C_BaseEntity"]["fields"];
            const auto& C_CSPlayerPawn = Data["C_CSPlayerPawn"]["fields"];
            const auto& CCSPlayerController = Data["CCSPlayerController"]["fields"];
            const auto& C_CSPlayerPawnBase = Data["C_CSPlayerPawnBase"]["fields"];
            const auto& C_BasePlayerPawn = Data["C_BasePlayerPawn"]["fields"];
            const auto& C_BaseModelEntity = Data["C_BaseModelEntity"]["fields"];
            const auto& CGlowProperty = Data["CGlowProperty"]["fields"];
            const auto& C_CSGameRules = Data["C_CSGameRules"]["fields"];
            const auto& C_PlantedC4 = Data["C_PlantedC4"]["fields"];
            const auto& CGameSceneNode = Data["CGameSceneNode"]["fields"];
            const auto& EntitySpottedState_t = Data["EntitySpottedState_t"]["fields"];

            if (FileNames == "offsets.json")
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
            else if (FileNames == "Client_Dll.json")
            {
                // C_CSPlayerPawn
                Offsets::m_ArmorValue = C_CSPlayerPawn["m_ArmorValue"];
                Offsets::m_iShotsFired = C_CSPlayerPawn["m_iShotsFired"];
                Offsets::m_aimPunchAngle = C_CSPlayerPawn["m_aimPunchAngle"];
                Offsets::m_bIsScoped = C_CSPlayerPawn["m_bIsScoped"];
                Offsets::m_entitySpottedState = C_CSPlayerPawn["m_entitySpottedState"];

                // C_BaseEntity
                Offsets::m_iTeamNum = C_BaseEntity["m_iTeamNum"];
                Offsets::m_iHealth = C_BaseEntity["m_iHealth"];
                Offsets::m_pGameSceneNode = C_BaseEntity["m_pGameSceneNode"];
                Offsets::m_fFlags = C_BaseEntity["m_fFlags"];
                Offsets::m_vecAbsVelocity = C_BaseEntity["m_vecAbsVelocity"];
                Offsets::m_fFlags = C_BaseEntity["m_fFlags"];
                Offsets::m_hOwnerEntity = C_BaseEntity["m_hOwnerEntity"];

                // CCSPlayerController
                Offsets::m_hPlayerPawn = CCSPlayerController["m_hPlayerPawn"];
                Offsets::m_sSanitizedPlayerName = CCSPlayerController["m_sSanitizedPlayerName"];
                Offsets::m_iPing = CCSPlayerController["m_iPing"];

                // C_CSPlayerPawnBase
                Offsets::m_flFlashBangTime = C_CSPlayerPawnBase["m_flFlashBangTime"];
                Offsets::m_iIDEntIndex = C_CSPlayerPawnBase["m_iIDEntIndex"];

                // C_BasePlayerPawn
                Offsets::m_vOldOrigin = C_BasePlayerPawn["m_vOldOrigin"];

                // C_BaseModelEntity
                Offsets::m_vecViewOffset = C_BaseModelEntity["m_vecViewOffset"];
                Offsets::m_Glow = C_BaseModelEntity["m_Glow"];

                // CGlowProperty
                Offsets::m_glowColorOverride = CGlowProperty["m_glowColorOverride"];
                Offsets::m_bGlowing = CGlowProperty["m_bGlowing"];

                // C_CSGameRules
                Offsets::m_bBombPlanted = C_CSGameRules["m_bBombPlanted"];
                Offsets::m_bBombDropped = C_CSGameRules["m_bBombDropped"];
                Offsets::m_bWarmupPeriod = C_CSGameRules["m_bWarmupPeriod"];
                Offsets::m_totalRoundsPlayed = C_CSGameRules["m_totalRoundsPlayed"];

                // C_PlantedC4
                Offsets::m_nBombSite = C_PlantedC4["m_nBombSite"];
                Offsets::m_bHasExploded = C_PlantedC4["m_bHasExploded"];
                Offsets::m_bBeingDefused = C_PlantedC4["m_bBeingDefused"];
                Offsets::m_flDefuseLength = C_PlantedC4["m_flDefuseLength"];

                // CGameSceneNode
                Offsets::m_vecAbsOrigin = CGameSceneNode["m_vecAbsOrigin"];

                // EntitySpottedState_t
                Offsets::m_bSpotted = EntitySpottedState_t["m_bSpotted"];
            }
            else if (FileNames == "buttons.json")
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