#pragma once
#include <Maths/hColor.h>
#include <Maths/hVector.h>

Color color;

namespace Config
{
	namespace Game
	{
		ImColor TerroristColor = C_Elements::RGBToImColor(234, 209, 139);
		ImColor CounterTerroristColor = C_Elements::RGBToImColor(182, 212, 238);	
		ImVec4 SpectatorColor = ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
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
		inline bool enableEspHealthPointsText = true;

		inline bool enableEspArmorBar = true;
		inline bool enableEspArmorPointsText = true;

		inline bool enableEspNames = true;
		inline bool enableTeamCheck = true;
		inline bool enableEspBones = true;

		ImColor BoxColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor HealthBarColor = ImColor(0, 255, 0, 255); // Default green;
		ImColor ArmorBarColor = C_Elements::RGBToImColor(182, 212, 238);
		ImColor LinesColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor NameColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor LineEndPointCircleColor = ImColor(255, 255, 255, 255); // Default white;

		float LinesThickness = 1.5f;
		float Lines_EndPoint_Radius = 3.0f;
		float BoxThickness = 1.0f;
		
		const char* availableSnapLinesPos[] = { "Top", "Center", "Bottom"};
		static int currentlinePosIndex = 2;
		Vector2 currentlinePos;
	}

	namespace Aimbot
	{
		inline bool enableHotKey = false;
		static int AB_KEYCODE = 0x06;
		static char AB_Default_KEYCODE_STR[16] = "06";

		const char* AimPositions[] = { "Head", "Penis" };
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
	}
}