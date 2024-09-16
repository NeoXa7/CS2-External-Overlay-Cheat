#pragma once
#include <Globals/hIncludes.h>
#include <Memory/hMemory.h>

uintptr_t GetBoneMatrix(uintptr_t entityPawn)
{
	uintptr_t node = Memory::ReadMemory<uintptr_t>(entityPawn + 0x308); // m_pGameSceneNode
	uintptr_t boneMatrix = Memory::ReadMemory<uintptr_t>(node + 0x1F0); // some shit
	return boneMatrix;
}

enum BoneIndex : int32_t
{
	HEAD = 6,
	NECK = 5,
	CHEST = 4,
	STOMACH = 2,
	COCK = 0,
	LSHOULDER = 8,
	LARM = 9,
	LHAND = 10,
	RSHOULDER = 13,
	RARM = 14,
	RHAND = 15,
	LTHIGH = 22,
	LCALF = 23,
	LFOOT = 24,
	RTHIGH = 25,
	RCALF = 26,
	RFOOT = 27,
};

struct BoneConnection_Struct
{
	int bone1;
	int bone2;

	BoneConnection_Struct(int b1, int b2) : bone1(b1), bone2(b2) {}
};

BoneConnection_Struct boneConnections[] = {
	BoneConnection_Struct(6, 5),  // head to neck
	BoneConnection_Struct(5, 4),  // neck to spine
	BoneConnection_Struct(4, 0),  // spine to hip
	BoneConnection_Struct(4, 8), // spine to left shoulder
	BoneConnection_Struct(8, 9), // left shoulder to left arm
	BoneConnection_Struct(9, 11), // arm to hand
	BoneConnection_Struct(4, 13),
	BoneConnection_Struct(13, 14),
	BoneConnection_Struct(14, 16),
	BoneConnection_Struct(4, 2),  // spine to spine_1
	BoneConnection_Struct(0, 22), // hip to left_hip
	BoneConnection_Struct(0, 25), // hip to right_hip
	BoneConnection_Struct(22, 23), // left_hip to left_knee
	BoneConnection_Struct(23, 24), // left knee to left foot
	BoneConnection_Struct(25, 26), // right_hip to right_knee
	BoneConnection_Struct(26, 27) // right knee to right foot
};