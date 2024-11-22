#pragma once
#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define MIN_MENU_WIDTH 800
#define MIN_MENU_HEIGHT 600
#define GAME_METRIC_UNITS 40.0f;
#define STROKEW ImColor(10, 10, 10, 255)

#include <Memory/Process.hpp>

namespace Flags
{
	inline bool IsRunning = true;
	inline bool IsVisible = true;
    inline bool g_showWarningBox = true;
    inline bool g_showConsole= true;

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
    inline bool enableNoSky = false;
    inline bool enableNoSpread = false;
    inline bool enableTPV = false;
    inline bool enableMapView = false;
    inline bool enableFovChanger = false;
    inline bool enableSensiChanger = false;
}

namespace CS2
{
    inline DWORD ProcID = PM.GetProcessID(L"cs2.exe");
    inline DWORD SteamProcID = PM.GetProcessID(L"steam.exe");
    inline uintptr_t ClientDll = PM.GetModuleBaseAddress(ProcID, L"client.dll");
    inline uintptr_t Engine2Dll = PM.GetModuleBaseAddress(ProcID, L"engine2.dll");
    inline uintptr_t InputsystemDll = PM.GetModuleBaseAddress(ProcID, L"inputsystem.dll");
    inline uintptr_t MatchMakingDll = PM.GetModuleBaseAddress(ProcID, L"matchmaking.dll");
    inline uintptr_t SoundsystemDll = PM.GetModuleBaseAddress(ProcID, L"soundsystem.dll");
    inline uintptr_t ServerDll = PM.GetModuleBaseAddress(ProcID, L"server.dll");
}

namespace Offsets
{
    // buttons;
    inline int dwForceAttack = 0x181ABC0;
    inline int dwForceAttack2 = 0x181AC50;
    inline int dwForceJump = 0x181B0D0;

    // offsets;
    inline int dwEntityList = 0x19CA858; // uintptr_t
    inline int dwLocalPlayerPawn = 0x182FAD8; // uintptr_t
    inline int dwLocalPlayerController = 0x1A1A6C0; // uintptr_t
    inline int dwViewAngles = 0x1A36990; // uintptr_t
    inline int dwViewMatrix = 0x1A2CB00; // uintptr_t
    inline int dwSensitivity = 0x1A29158; // uintptr_t
    inline int dwSensitivity_sensitivity = 0x40; // uintptr_t
    inline int dwGameRules = 0x1A28438; // uintptr_t
    inline int dwGameTypes = 0x1A31B0; // uintptr_t
    inline int dwGameTypes_mapName = 0x120; // uintptr_t
    inline int dwPlantedC4 = 0x1A32070; // uintptr_t
    inline int dwGlobalVars = 0x1823C50; // uintptr_t
    inline int dwWeaponC4 = 0x19CDC50;  // uintptr_t


    // client_dll;   
    inline int m_iTeamNum = 0x3E3; // uint8
    inline int m_iHealth = 0x344; // int32
    inline int m_ArmorValue = 0x2404; // int32
    inline int m_hPlayerPawn = 0x80C; // CHandle<C_CSPlayerPawn>
    inline int m_flFlashBangTime = 0x13F8; // float32
    inline int m_iIDEntIndex = 0x1458; // CEntityIndex
    inline int m_iShotsFired = 0x23E4; // int32
    inline int m_aimPunchAngle = 0x1584; // QAngle
    inline int m_vOldOrigin = 0x1324; // Vector
    inline int m_vecViewOffset = 0xCB0; // CNetworkViewOffsetVector
    inline int m_pGameSceneNode = 0x328; // CGameSceneNode*
    inline int m_bBombPlanted = 0x9A5; // bool
    inline int m_bBombDropped = 0x9A4; // bool
    inline int m_nBombSite = 0xF94; // int32
    inline int m_bIsScoped = 0x23D0; // bool
    inline int m_sSanitizedPlayerName = 0x770; // CUtlString
    inline int m_fFlags = 0x3EC; // uint32
    inline int m_vecAbsVelocity = 0x3F0; // Vector
    inline int m_vecAbsOrigin = 0xD0; // Vector
    inline int m_hOwnerEntity = 0x440; // CHandle<C_BaseEntity>
    inline int m_iPing = 0x740; // uint32
    inline int m_bHasExploded = 0xFC5; // bool
    inline int m_bBeingDefused = 0xFCC; // bool
    inline int m_flDefuseLength = 0xFDC; // float32
    inline int m_bWarmupPeriod = 0x41; // bool
    inline int m_bCTTimeOutActive = 0x4E; // bool
    inline int m_bTerroristTimeOutActive = 0x4D; // bool
    inline int m_pCameraServices = 0x11E0; // (CPlayer_CameraServices*)
    inline int m_iFOV = 0x210; // uint32
    inline int m_bDormant = 0xEF; // bool
    inline int m_pWeaponServices = 0x11A8; // CPlayer_WeaponServices*
    inline int m_hMyWeapons = 0x40; // C_NetworkUtlVectorBase<CHandle<C_BasePlayerWeapon>>
    inline int m_AttributeManager = 0x1148; // C_AttributeContainer
    inline int m_Item = 0x50; // C_EconItemView
    inline int m_iItemDefinitionIndex = 0x1BA; // uint16
    inline int m_MeshGroupMask = 0x198; // uint64
    inline int m_nFallbackStatTrak = 0x1604; // int32
    inline int m_nFallbackPaintKit = 0x15F8; // int32
    inline int m_nFallbackSeed = 0x15FC; // int32
    inline int m_flFallbackWear = 0x1600; // float32
    inline int m_pViewModelServices = 0x1368; // CPlayer_ViewModelServices*
    inline int m_hViewModel = 0x40; // CHandle<C_BaseViewModel>[3]
}