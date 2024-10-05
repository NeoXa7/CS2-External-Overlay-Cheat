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
    inline int dwForceAttack = 0x181ABC0;
    inline int dwForceAttack2 = 0x181AC50;
    inline int dwForceJump = 0x181B0D0;

    // offsets;
    inline int dwEntityList = 0x19BAC58; // uintptr_t
    inline int dwLocalPlayerPawn = 0x18220C8; // uintptr_t
    inline int dwLocalPlayerController = 0x1A0A5F8; // uintptr_t
    inline int dwViewAngles = 0x1A26BE0; // uintptr_t
    inline int dwViewMatrix = 0x1A1CD70; // uintptr_t
    inline int dwSensitivity = 0x1A19398; // uintptr_t
    inline int dwSensitivity_sensitivity = 0x40; // uintptr_t
    inline int dwGameRules = 0x1A18678; // uintptr_t
    inline int dwGameTypes = 0x1A31B0; // uintptr_t
    inline int dwGameTypes_mapName = 0x120; // uintptr_t
    inline int dwPlantedC4 = 0x1A20EB8; // uintptr_t
    inline int dwGlobalVars = 0x1815F60; // uintptr_t
    inline int dwWeaponC4 = 0x19BDD80;  // uintptr_t


    // client_dll;   
    inline int m_iTeamNum = 0x3E3; // uint8
    inline int m_iHealth = 0x344; // int32
    inline int m_ArmorValue = 0x23F4; // int32
    inline int m_hPlayerPawn = 0x80C; // CHandle<C_CSPlayerPawn>
    inline int m_flFlashBangTime = 0x13F0; // float32
    inline int m_iIDEntIndex = 0x1450; // CEntityIndex
    inline int m_iShotsFired = 0x23D4; // int32
    inline int m_aimPunchAngle = 0x1574; // QAngle
    inline int m_vOldOrigin = 0x131C; // Vector
    inline int m_vecViewOffset = 0xCA8; // CNetworkViewOffsetVector
    inline int m_Glow = 0xBF8; // CGlowProperty
    inline int m_glowColorOverride = 0x40; // Color
    inline int m_bGlowing = 0x51; // bool
    inline int m_pGameSceneNode = 0x328; // CGameSceneNode*
    inline int m_bBombPlanted = 0x9A5; // bool
    inline int m_bBombDropped = 0x9A4; // bool
    inline int m_nBombSite = 0xF8C; // int32
    inline int m_bIsScoped = 0x23C0; // bool
    inline int m_sSanitizedPlayerName = 0x770; // CUtlString
    inline int m_fFlags = 0x3EC; // uint32
    inline int m_vecAbsVelocity = 0x3F0; // Vector
    inline int m_vecAbsOrigin = 0xD0; // Vector
    inline int m_hOwnerEntity = 0x440; // CHandle<C_BaseEntity>
    inline int m_iPing = 0x740; // uint32
    inline int m_bHasExploded = 0xFBD; // bool
    inline int m_bBeingDefused = 0xFC4; // bool
    inline int m_flDefuseLength = 0xFD4; // float32
    inline int m_bWarmupPeriod = 0x41; // bool
    inline int m_totalRoundsPlayed = 0x84; // int32
    inline int m_entitySpottedState = 0x23A8; // EntitySpottedState_t
    inline int m_bSpotted = 0x8; // bool
}