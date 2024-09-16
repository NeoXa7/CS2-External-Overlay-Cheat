#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class Entities
{
public:
    int Team;
    int Health;
    int Armor;
    char Names[128] = { 0 };
    bool IsSpotted;
    Vector3 Position;
    

public:
    void UpdateEntities(int entityIndex)
    {
        uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + (8 * (entityIndex & 0x7FFF) >> 9) + 16);
        if (!listEntry)
            return;

        uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (entityIndex & 0x1FF));
        if (!currentController)
            return;

        uintptr_t pawnHandle = Memory::ReadMemory<uintptr_t>(currentController + Offsets::m_hPlayerPawn);
        if (!pawnHandle)
            return;

        uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
        if (!listEntry2)
            return;

        uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
        if (!currentPawn)
            return;

        uintptr_t NameAddress = Memory::ReadMemory<uintptr_t>(currentController + Offsets::m_sSanitizedPlayerName);
        Memory::ReadArray<char>(NameAddress, Names, sizeof(Names)); // Name  
     
        Health = Memory::ReadMemory<int>(currentPawn + Offsets::m_iHealth);
        IsSpotted = Memory::ReadMemory<bool>(currentPawn + Offsets::m_entitySpottedState + Offsets::m_bSpotted);
        Position = Memory::ReadMemory<Vector3>(currentPawn + Offsets::m_vOldOrigin);
        Armor = Memory::ReadMemory<int>(currentPawn + Offsets::m_ArmorValue);
        Team = Memory::ReadMemory<int>(currentPawn + Offsets::m_iTeamNum);
    }

    float GetHeadHeight(Vector2 screenPos, Vector2 headScreenPos)
    {
        return (screenPos.y - headScreenPos.y) / 8;
    }
};

inline Entities entities;
