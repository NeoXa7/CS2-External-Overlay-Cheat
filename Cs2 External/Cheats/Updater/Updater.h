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
#endif

class Updater {
private:
    string Github_Repo_Api_A2X = "https://api.github.com/repos/a2x/cs2-dumper/commits";
    string Github_Repo_Api_NeoXa7 = "https://api.github.com/repos/NeoXa7/Cpp-Updater-Class-for-CS2-Offsets/commits";

    const std::vector<std::pair<std::string, std::string>> Github_File_Path = {
        {"https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json", "Offsets.json"},
        {"https://github.com/NeoXa7/Cpp-Updater-Class-for-CS2-Offsets/raw/main/Client_Dll.json", "Client_Dll.json"}
        // Add more files here as needed
    };

    bool FileExists(const std::string& name) {
        std::ifstream f(name.c_str());
        return f.good();
    }

    bool DownloadFile(const std::string& url, const std::string& fileName) {
        HINTERNET hInternet, hConnect;

        hInternet = InternetOpen(L"Updater", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) {
            std::cerr << " [Updater] InternetOpen failed." << std::endl;
            return false;
        }

        hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (!hConnect) {
            std::cerr << " [Updater] InternetOpenUrlA failed." << std::endl;
            InternetCloseHandle(hInternet);
            return false;
        }

        std::ofstream outFile(fileName, std::ios::binary);
        if (!outFile) {
            std::cerr << " [Updater] Failed to create local file." << std::endl;
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

    bool GetLastCommitInfo(string api, json& commit) {
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
    bool CheckAndDownload() {
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
                    if (localPath == "Offsets.json")
                    {
                        if (DownloadFile(url, localPath)) {
                            std::cout << " [Updater] Offsets.json : Successfully Updated to latest Offsets\n";
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

    bool UpdateOffsets() {
        std::vector<std::string> file_paths = { "Offsets.json", "Client_Dll.json" };
        json Data;

        for (const auto& file_path : file_paths) {
            if (!FileExists(file_path)) {
                std::cerr << " [Updater] " << file_path << " not found." << std::endl;
                continue;
            }

            std::ifstream inFile(file_path);
            if (!inFile) {
                std::cerr << " [Updater] Failed to open " << file_path << "." << std::endl;
                return false;
            }

            try {
                inFile >> Data;
            }
            catch (const std::exception& e) {
                std::cerr << " [Updater] Failed to parse JSON from " << file_path << ": " << e.what() << std::endl;
                return false;
            }

            
            
            const auto& C_BaseEntity = Data["C_BaseEntity"];
            const auto& C_CSPlayerPawn = Data["C_CSPlayerPawn"];
            const auto& CCSPlayerController = Data["CCSPlayerController"];
            const auto& C_CSPlayerPawnBase = Data["C_CSPlayerPawnBase"];
            const auto& C_BasePlayerPawn = Data["C_BasePlayerPawn"];
            const auto& C_BaseModelEntity = Data["C_BaseModelEntity"];
            const auto& CGlowProperty = Data["CGlowProperty"];
            const auto& C_CSGameRules = Data["C_CSGameRules"];
            const auto& C_PlantedC4 = Data["C_PlantedC4"];
            const auto& CGameSceneNode = Data["CGameSceneNode"];
            const auto& EntitySpottedState_t = Data["EntitySpottedState_t"];


            if (file_path == "Offsets.json")
            {
                const auto& Client = Data["client.dll"];
                if (Data.contains("client.dll")) {
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
                }

                if (Data.contains("matchmaking.dll"))
                {
                    const auto& Matchmaking = Data["matchmaking.dll"];
                    Offsets::dwGameTypes = Matchmaking["dwGameTypes"];
                    Offsets::dwGameTypes_mapName = Matchmaking["dwGameTypes_mapName"];
                }

            }else if (file_path == "Client_Dll.json")
            {
                if (Data.contains("C_CSPlayerPawn"))
                {
                    if (C_CSPlayerPawn.contains("fields")) {
                        const auto& fields = C_CSPlayerPawn["fields"];
                        Offsets::m_ArmorValue = fields["m_ArmorValue"];
                        Offsets::m_iShotsFired = fields["m_iShotsFired"];
                        Offsets::m_aimPunchAngle = fields["m_aimPunchAngle"];
                        Offsets::m_bIsScoped = fields["m_bIsScoped"];
                        Offsets::m_entitySpottedState = fields["m_entitySpottedState"];
                    }
                }

                if (Data.contains("C_BaseEntity")) {
                    if (C_BaseEntity.contains("fields")) {
                        const auto& fields = C_BaseEntity["fields"];
                        Offsets::m_iTeamNum = fields.value("m_iTeamNum", 0);
                        Offsets::m_iHealth = fields["m_iHealth"];
                        Offsets::m_pGameSceneNode = fields["m_pGameSceneNode"];
                        Offsets::m_fFlags = fields["m_fFlags"];
                        Offsets::m_vecAbsVelocity = fields["m_vecAbsVelocity"];
                        Offsets::m_fFlags = fields["m_fFlags"];
                        Offsets::m_hOwnerEntity = fields["m_hOwnerEntity"];
                    }
                }

                // CCSPlayerController
                if (Data.contains("CCSPlayerController"))
                {
                    if (CCSPlayerController.contains("fields")) {
                        const auto& fields = CCSPlayerController["fields"];
                        Offsets::m_hPlayerPawn = fields["m_hPlayerPawn"];
                        Offsets::m_sSanitizedPlayerName = fields["m_sSanitizedPlayerName"];
                        Offsets::m_iPing = fields["m_iPing"];
                    }
                }

                // C_CSPlayerPawnBase
                if (Data.contains("C_CSPlayerPawnBase"))
                {
                    if (C_CSPlayerPawnBase.contains("fields")) {
                        const auto& fields = C_CSPlayerPawnBase["fields"];
                        Offsets::m_flFlashBangTime = fields["m_flFlashBangTime"];
                        Offsets::m_iIDEntIndex = fields["m_iIDEntIndex"];
                    }
                }

                // C_BasePlayerPawn
                if (Data.contains("C_BasePlayerPawn"))
                {
                    if (C_BasePlayerPawn.contains("fields")) {
                        const auto& fields = C_BasePlayerPawn["fields"];
                        Offsets::m_vOldOrigin = fields["m_vOldOrigin"];
                    }
                }

                // C_BaseModelEntity
                if (Data.contains("C_BaseModelEntity"))
                {
                    if (C_BaseModelEntity.contains("fields")) {
                        const auto& fields = C_BaseModelEntity["fields"];
                        Offsets::m_vecViewOffset = fields["m_vecViewOffset"];
                        Offsets::m_Glow = fields["m_Glow"];
                    }
                }

                // CGlowProperty
                if (Data.contains("CGlowProperty"))
                {
                    if (CGlowProperty.contains("fields")) {
                        const auto& fields = CGlowProperty["fields"];
                        Offsets::m_glowColorOverride = fields["m_glowColorOverride"];
                        Offsets::m_bGlowing = fields["m_bGlowing"];
                    }
                }

                // C_CSGameRules
                if (Data.contains("C_CSGameRules"))
                {
                    if (C_CSGameRules.contains("fields")) {
                        const auto& fields = C_CSGameRules["fields"];
                        Offsets::m_bBombPlanted = fields["m_bBombPlanted"];
                        Offsets::m_bBombDropped = fields["m_bBombDropped"];
                        Offsets::m_bWarmupPeriod = fields["m_bWarmupPeriod"];
                        Offsets::m_totalRoundsPlayed = fields["m_totalRoundsPlayed"];
                    }
                }

                // C_PlantedC4
                if (Data.contains("C_PlantedC4"))
                {
                    if (C_PlantedC4.contains("fields")) {
                        const auto& fields = C_PlantedC4["fields"];
                        Offsets::m_nBombSite = fields["m_nBombSite"];
                        Offsets::m_bHasExploded = fields["m_bHasExploded"];
                        Offsets::m_bBeingDefused = fields["m_bBeingDefused"];
                        Offsets::m_flDefuseLength = fields["m_flDefuseLength"];
                    }
                }

                // CGameSceneNode
                if (Data.contains("CGameSceneNode"))
                {
                    if (CGameSceneNode.contains("fields")) {
                        const auto& fields = CGameSceneNode["fields"];
                        Offsets::m_vecAbsOrigin = fields["m_vecAbsOrigin"];
                    }
                }

                // EntitySpottedState_t
                if (Data.contains("EntitySpottedState_t "))
                {
                    if (EntitySpottedState_t.contains("fields")) {
                        const auto& fields = EntitySpottedState_t["fields"];
                        Offsets::m_bSpotted = fields["m_bSpotted"];
                    }
                }

            }
            
        }
        return true;
    }
};

inline Updater updater; // Global instance of Updater