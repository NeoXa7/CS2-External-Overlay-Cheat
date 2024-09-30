#pragma once
#include <Memory/hProcess.h>

#define Screen_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define Screen_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define GAME_METRIC_UNITS 40.0f;
#define Min_Menu_Width 500
#define Min_Menu_Height 500

namespace Flags
{
    // menu flags;
    inline bool isRunning = true;
    inline bool showMenu = true;

    // cheats flags;
    inline bool enableTriggerbot = false;
    inline bool enableRCS = false;
    inline bool enableBhop = false;
    inline bool enableAntiflash = false;
    inline bool enableRadarHack = false;
    inline bool enableGlowHack = false;
    inline bool enableAimbot = false;
    inline bool enableJumpShot = true;
    inline bool enablePlayerEsp = true;
    inline bool enableC4Esp = true;
    inline bool enableWorldEsp = false;
}

namespace CS2
{
    inline DWORD procID = ProcessManager::GetProcessID(L"cs2.exe");
    inline uintptr_t ClientDll = ProcessManager::GetModuleBaseAddress(procID, L"client.dll");
    inline uintptr_t Engine2Dll = ProcessManager::GetModuleBaseAddress(procID, L"engine2.dll");
    inline uintptr_t InputsystemDll = ProcessManager::GetModuleBaseAddress(procID, L"inputsystem.dll");
    inline uintptr_t MatchMakingDll = ProcessManager::GetModuleBaseAddress(procID, L"matchmaking.dll");
    inline uintptr_t SoundsystemDll = ProcessManager::GetModuleBaseAddress(procID, L"soundsystem.dll");
    inline uintptr_t ServerDll = ProcessManager::GetModuleBaseAddress(procID, L"server.dll");
}

namespace Offsets
{
    // buttons;
    inline int dwForceAttack = 0x17BA020;
    inline int dwForceAttack2 = 0x17BA0B0;
    inline int dwForceJump = 0x17BA530;

    // offsets;
    inline int dwEntityList = 0x1954568; // uintptr_t
    inline int dwLocalPlayerPawn = 0x17C17F0; // uintptr_t
    inline int dwLocalPlayerController = 0x19A41C8; // uintptr_t
    inline int dwViewAngles = 0x19C5958; // uintptr_t
    inline int dwViewMatrix = 0x19B64F0; // uintptr_t
    inline int dwSensitivity = 0x19B2B38; // uintptr_t
    inline int dwSensitivity_sensitivity = 0x40; // uintptr_t
    inline int dwGameRules = 0x19B1558; // uintptr_t
    inline int dwGameTypes = 0x1A41C0; // uintptr_t
    inline int dwGameTypes_mapName = 0x120; // uintptr_t
    inline int dwPlantedC4 = 0x19BAF38; // uintptr_t
    inline int dwGlobalVars = 0x17B54F8; // uintptr_t
    inline int dwWeaponC4 = 0x1958570;  // uintptr_t


    // client_dll;   
    inline int m_iTeamNum = 0x3C3; // uint8
    inline int m_iHealth = 0x324; // int32
    inline int m_ArmorValue = 0x22D4; // int32
    inline int m_hPlayerPawn = 0x7EC; // CHandle<C_CSPlayerPawn>
    inline int m_flFlashBangTime = 0x1348; // float32
    inline int m_iIDEntIndex = 0x13A8; // CEntityIndex
    inline int m_iShotsFired = 0x22B4; // int32
    inline int m_aimPunchAngle = 0x14CC; // QAngle
    inline int m_vOldOrigin = 0x1274; // Vector
    inline int m_vecViewOffset = 0xC50; // CNetworkViewOffsetVector
    inline int m_Glow = 0xBA0; // CGlowProperty
    inline int m_glowColorOverride = 0x40; // Color
    inline int m_bGlowing = 0x51; // bool
    inline int m_pGameSceneNode = 0x308; // CGameSceneNode*
    inline int m_bBombPlanted = 0x9A5; // bool
    inline int m_bBombDropped = 0x9A4; // bool
    inline int m_nBombSite = 0xED4; // int32
    inline int m_bIsScoped = 0x22A0; // bool
    inline int m_sSanitizedPlayerName = 0x750; // CUtlString
    inline int m_fFlags = 0x3CC; // uint32
    inline int m_vecAbsVelocity = 0x3D0; // Vector
    inline int m_vecAbsOrigin = 0xD0; // Vector
    inline int m_hOwnerEntity = 0x420; // CHandle<C_BaseEntity>
    inline int m_iPing = 0x720; // uint32
    inline int m_bHasExploded = 0xF05; // bool
    inline int m_bBeingDefused = 0xF0C; // bool
    inline int m_flDefuseLength = 0xF1C; // float32
    inline int m_bWarmupPeriod = 0x41; // bool
    inline int m_totalRoundsPlayed = 0x84; // int32
    inline int m_entitySpottedState = 0x2288; // EntitySpottedState_t
    inline int m_bSpotted = 0x8; // bool
}