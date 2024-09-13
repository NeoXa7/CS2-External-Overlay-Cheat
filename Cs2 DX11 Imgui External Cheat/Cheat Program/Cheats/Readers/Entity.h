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
public:
	bool IsSpotted;
	int EntityIndex;
public:
	Vector3 Position;
	Vector3 HeadPosition;
public:
	void UpdateEntities()
	{
		EntityIndex = Memory::ReadMemory<int>(player.localPlayerPawn + Offsets::m_iIDEntIndex);
	}
}; inline Entities entities;