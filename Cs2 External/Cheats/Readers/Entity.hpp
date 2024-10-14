#pragma once
#include <Memory/Memory.hpp>
#include <Maths/Vector.hpp>
#include <Globals/Globals.hpp>
#include <ImGui/imgui.h>
#include <Utilities/Bones.hpp>

class Entities
{
public:
    int Team;
    int Health;
    int Armor;
    char Names[128] = { 0 };
    Vector3 Position;
    uintptr_t BoneMatrix;
    bool IsFiring;
    uint32_t Ping;
    Vector3 VecViewOffset;
    bool IsSpotted;
    bool IsScoped;
public:
    void UpdateEntities(uintptr_t currentPawn, uintptr_t currentController)
    {
        // Read player name
        uintptr_t NameAddress = mem.ReadMemory<uintptr_t>(currentController + Offsets::m_sSanitizedPlayerName);
        mem.ReadArray<char>(NameAddress, Names, sizeof(Names));

        // Read other attributes
        Team = mem.ReadMemory<int>(currentPawn + Offsets::m_iTeamNum);
        Health = mem.ReadMemory<int>(currentPawn + Offsets::m_iHealth);
        Armor = mem.ReadMemory<int>(currentPawn + Offsets::m_ArmorValue);
        Position = mem.ReadMemory<Vector3>(currentPawn + Offsets::m_vOldOrigin);
        BoneMatrix = GetBoneMatrix(currentPawn);
        IsFiring = mem.ReadMemory<bool>(currentPawn + Offsets::m_iShotsFired);
        Ping = mem.ReadMemory<uint32_t>(currentController + Offsets::m_iPing);
        VecViewOffset = mem.ReadMemory<Vector3>(currentPawn + Offsets::m_vecViewOffset);
        IsSpotted = mem.ReadMemory<bool>(currentPawn + Offsets::m_entitySpottedState + Offsets::m_bSpotted);
        IsScoped = mem.ReadMemory<bool>(currentPawn + Offsets::m_bIsScoped);
    }

    float GetHeadHeight(Vector2 screenPos, Vector2 headScreenPos)
    {
        return (screenPos.y - headScreenPos.y) / 8;
    }

    ImColor GetColorHealth()
    {
        if (Health >= 100)
        {
            return ImColor(0, 255, 0, 255); // Green for full health
        }
        else if (Health >= 60)
        {
            return ImColor(255, 255, 0, 255); // Yellow for medium health
        }
        else if (Health >= 30)
        {
            return ImColor(255, 165, 0, 255); // Orange for low health
        }
        else
        {
            return ImColor(255, 0, 0, 255); // Red for critical health
        }
    }

}; inline Entities entities[64];