#pragma once
#include <Maths/hColor.h>
#include <Maths/hVector.h>
#include <Hacks/Bones.h>

Color color;

namespace Config
{
	namespace Game
	{
		ImColor TerroristColor = C_Elements::RGBToImColor(234, 209, 139);
		ImColor CounterTerroristColor = C_Elements::RGBToImColor(182, 212, 238);	
		ImVec4 SpectatorColor = ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
		bool DrawCrosshair = false;
		float CrosshairSize = 10.0f;
		ImColor CrosshairColor = ImColor(255, 255, 255, 255);
	}

	namespace TriggerBot
	{
		inline bool enableHotKey = true;
		inline bool enableTeamCheck = true;
		static int TB_KEYCODE = 0xA0;
		static char TB_Default_KEYCODE_STR[16] = "A0";
	}

	namespace RCS
	{
		float oldPunch_x = 0.0f;
		float oldPunch_y = 0.0f;
	}

	namespace GlowHack
	{
		const char* AvailableColors[] = { "Green", "Yellow", "Blue", "Red", "White", "Purple", "Cyan", "LightBlue" };
		static int CurrentColorIndex = 0;

		namespace GlowColor
		{
			DWORD64 WHITE = color.convertToARGB(Color(253, 228, 132, 255));
			DWORD64 BLUE = color.convertToARGB(Color(128, 0, 0, 255));
			DWORD64 RED = color.convertToARGB(Color(0, 0, 255, 255));
			DWORD64 PURPLE = color.convertToARGB(Color(128, 0, 128, 255));
			DWORD64 GREEN = color.convertToARGB(Color(0, 255, 0, 255));
			DWORD64 CYAN = color.convertToARGB(Color(255, 255, 0, 255));
			DWORD64 LIGHTBLUE = color.convertToARGB(Color(0, 0, 0, 255));
			DWORD64 YELLOW = color.convertToARGB(Color::fromHSV(180.0f, 1.0f, 1.0f));

			DWORD64 CurrentGlowColor = GREEN;
		}

		namespace GlowSettings
		{
			inline bool TeamGlow = false;
			inline bool DeadEntityGlow = false;
		}

	}

	namespace Esp
	{	
		inline bool enableEspBoxes = true;
		inline bool enableEspLines = false;
		inline bool enableEspHealthBar = true;
		inline bool enableEspArmorBar = true;
		inline bool enableEspNames = false;
		inline bool enableDistanceEsp = false;
		inline bool enableEspBones = true;

		inline bool enableEspHealthPointsText = false;
		inline bool enableEspArmorPointsText = true;
		inline bool enableTeamCheck = true;
	
		inline bool HeadFilled = false;
		inline bool ShowBoneJoints = false;

		inline bool enableC4Box = true;
		inline bool enableC4StatusEsp = true;
		inline bool enableC4Distance = true;
		

		ImColor BoxColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor HealthBarColor = ImColor(0, 255, 0, 255); // Default green;
		ImColor ArmorBarColor = C_Elements::RGBToImColor(182, 212, 238);
		ImColor LinesColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor NameColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor BonesColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor HeadColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor DistanceColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor C4_Box_Color = ImColor(255, 255, 255, 255); // Default white;
		ImColor C4_Status_Text_Color = ImColor(255, 255, 255, 255); // Default white;
		ImColor C4_Distance_Text_Color = ImColor(255, 255, 255, 255); // Default white;

		float BonesThickness = 0.5f;
		float C4BoxThickness = 2.5f;
		float LinesThickness = 1.5f;
		float BoxThickness = 1.0f;
		const float JointDisplayDistance = 1000.0f;
		const float SLEndPointDisplayDistance = 3000.0f;

		const char* availableSnapLinesPos[] = { "Top", "Center", "Bottom"};
		static int currentlinePosIndex = 2;
		Vector2 currentlinePos;

		Vector3 SetBoneCoordinates(uintptr_t boneMatrix, BoneIndex bone)
		{
			return Memory::ReadMemory<Vector3>(boneMatrix + (bone * 0x20));
		}

	}

	namespace Aimbot
	{
		inline bool enableHotKey = false;
		static int AB_KEYCODE = 0x06;
		static char AB_Default_KEYCODE_STR[16] = "06";

		const char* AimPositions[] = {
			"Head",
			"Penis"
		};
		static int CurrentAimPosIndex = 0; // Index of the currently selected item

		static float AimFov = 10.f;
		static float AimSmoothness = 1.f;

		static bool ShowFovCircle = false;
		static ImVec4 FovCircleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Default White;
		static float FovCircleThickness = 1.5f;	
		inline bool TeamCheck = true;
		
		Vector3 SetPenisCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
		{
			return entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::m_vecViewOffset) * 0.5;
		}

		Vector3 SetHeadCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
		{
			return entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::m_vecViewOffset);
		}

		/*Vector3 SetHeadCoordinates(uintptr_t boneMatrix)
		{
			Vector3 entityPosition = Memory::ReadMemory<Vector3>(boneMatrix + (BoneIndex::HEAD * 0x20));
			return entityPosition;
		}*/

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
	}
}