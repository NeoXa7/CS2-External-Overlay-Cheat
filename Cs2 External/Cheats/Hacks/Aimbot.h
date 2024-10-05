#pragma once
#include <Maths/hVector.h>
#include <Maths/WorldToScreen.h>
#include <Maths/ViewMatrix.h>
#include <Memory/hMemory.h>
#include <Readers/Player.h>
#include <Readers/Entity.h>
#include <Readers/Game.h>
#include <Hacks/Utils/Config.h>
#include <Hacks/Utils/Bones.h>

class AIMBOT
{
public:
    void BeginAimbot();
private:
    Vector2 FindClosestEnemy();
    void MoveMouseToClosestEnemy(Vector2 position);

    Vector3 SetPenisCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
    {
        return entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::m_vecViewOffset) * 0.5;
    }

    Vector3 SetHeadCoordinates(uintptr_t boneMatrix)
    {
        Vector3 entityPosition = Memory::ReadMemory<Vector3>(boneMatrix + (BoneIndex::HEAD * 0x20));
        return entityPosition;
    }

    Vector3 SetNeckCoordinates(uintptr_t boneMatrix)
    {
        Vector3 entityPosition = Memory::ReadMemory<Vector3>(boneMatrix + (BoneIndex::NECK * 0x20));
        return entityPosition;
    }

    Vector3 SetChestCoordinates(uintptr_t boneMatrix)
    {
        Vector3 entityPosition = Memory::ReadMemory<Vector3>(boneMatrix + (BoneIndex::CHEST * 0x20));
        return entityPosition;
    }

    Vector3 SetStomachCoordinates(uintptr_t boneMatrix)
    {
        Vector3 entityPosition = Memory::ReadMemory<Vector3>(boneMatrix + (BoneIndex::STOMACH * 0x20));
        return entityPosition;
    }

}; inline AIMBOT aimbot;

void AIMBOT::BeginAimbot()
{
    Vector2 closest = FindClosestEnemy();
    MoveMouseToClosestEnemy(closest);
}

Vector2 AIMBOT::FindClosestEnemy()
{
    Vector2 closestEnemyPos = { 0, 0 };
    Vector2 Center_Of_Screen{ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1) / 2 };
    float lowestDistance = 10000.0f;

    for (int i = 1; i < 64; i++)
    {
        uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
        if (!listEntry)
            continue;

        uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
        if (!currentController)
            continue;

        uint32_t pawnHandle = Memory::ReadMemory<uint32_t>(currentController + Offsets::m_hPlayerPawn);
        if (!pawnHandle)
            continue;

        uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
        if (!listEntry2)
            continue;

        uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
        if (!currentPawn)
            continue;

        entities->UpdateEntities(currentPawn, currentController);

        if (currentPawn == player.localPlayerPawn)
            continue;

        uintptr_t BoneMatrix = GetBoneMatrix(currentPawn);
        Vector3 Head3D = SetHeadCoordinates(BoneMatrix);
        Vector3 Neck3D = SetNeckCoordinates(BoneMatrix);
        Vector3 Chest3D = SetChestCoordinates(BoneMatrix);
        Vector3 Stomach3D = SetStomachCoordinates(BoneMatrix);
        Vector3 Penis3D = SetPenisCoordinates(entities->Position, currentPawn);

        if (Config::Aimbot::TeamCheck && entities->Team == player.Team) // Avoiding Aimbot For Team;
            continue;

        if (entities->Health <= 0)  // Avoiding Aimbot if Health is less than or equal to 0;
            continue;

        Vector3 AimPosition3D = Head3D;

        switch (Config::Aimbot::CurrentAimPosIndex)
        {
        case 0: AimPosition3D = Head3D; break;
        case 1: AimPosition3D = Penis3D; break;
        case 2: AimPosition3D = Neck3D; break;
        case 3: AimPosition3D = Chest3D; break;
        case 4: AimPosition3D = Stomach3D; break;
        default: AimPosition3D = Head3D; break;
        }

        Vector2 enemyScreenPos;
        if (WorldToScreen(AimPosition3D, enemyScreenPos, game.ViewMatrix))
        {
            float distance = sqrt(pow(enemyScreenPos.x - Center_Of_Screen.x, 2) + pow(enemyScreenPos.y - Center_Of_Screen.y, 2));
            if (distance < lowestDistance)
            {
                lowestDistance = distance;
                closestEnemyPos = enemyScreenPos;
            }
        }      
    }
    return closestEnemyPos;
}

void AIMBOT::MoveMouseToClosestEnemy(Vector2 position)
{
    if (position.x == 0.0 && position.y == 0.0)
        return;

    Vector2 Center_Of_Screen{ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1) / 2 };

    auto new_x = position.x - Center_Of_Screen.x;
    auto new_y = position.y - Center_Of_Screen.y;

    mouse_event(MOUSEEVENTF_MOVE, new_x, new_y, 0, 0);
}