#pragma once
#include <Maths/Vector.hpp>
#include <Readers/LocalPlayer.hpp>

namespace Config
{
	namespace Game
	{
		ImColor TerroristColor = ImColor(234, 209, 139, 255);
		ImColor CounterTerroristColor = ImColor(182, 212, 238, 255);
		ImVec4 SpectatorColor = ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
		inline bool DrawCrosshair = false;
		float CrosshairSize = 10.0f; // Default Crosshair Size;
		ImColor CrosshairColor = ImColor(255, 255, 255, 255); // Default Crosshair Color;
		float Sensitivity = player.Sensitivity;
	}

	namespace TriggerBot
	{
		inline bool enableHotKey = true;
		inline bool enableTeamCheck = true;
		const char* HotkeyOptions[] = {
			"Left Shift",
			"Left CTRL",
			"Left Alt",
			"X1_Mouse Button",
			"X2_Mouse Button"
		};
		static int CurrentHotkeyIndex = 0; // Index of the currently selected item
		int currentKey = 0xA0;
	}

	namespace RCS
	{
		float oldPunch_x = 0.0f;
		float oldPunch_y = 0.0f;
	}

	namespace Esp
	{
		inline bool enableEspBoxes = true;
		inline bool enableEspBoxesFilled = true;
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

		inline bool enableChickensEsp = true;
		inline bool enableHostagesEsp = true;
		inline bool enableDroppedWeaponEsp = true;
		inline bool enableProjectilesEsp = true;


		ImColor BoxColorNotFilled = ImColor(0, 255, 224, 255); // Default nylon;
		ImColor BoxColorFilled = ImColor(10, 10, 10, 128); // Default Black;
		ImColor VisibleBoxColor = ImVec4(0, 183, 0, 255); // Default green;
		ImColor HealthBarColor = ImColor(0, 255, 0, 255); // Default green;
		ImColor ArmorBarColor = ImColor(182, 212, 238, 255); // Default CT Color;
		ImColor LinesColor = ImColor(0, 255, 140, 255); // Default white;
		ImColor NameColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor BonesColor = ImColor(0, 255, 224, 255); // Default white;
		ImColor BoneJointsColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor HeadColor = ImColor(0, 255, 224, 255); // Default white;
		ImColor DistanceColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor C4_Planted_Box_Color = ImColor(255, 0, 0, 128); // Default white;
		ImColor C4_Dropped_Box_Color = ImColor(0, 255, 0, 128); // Default white;
		ImColor C4_Distance_Text_Color = ImColor(255, 255, 255, 255); // Default white;

		ImColor Weapon_Esp_Text_Color = ImColor(255, 255, 0, 255); // Default Yellow;
		ImColor Projectiles_Text_Color = ImColor(255, 0, 0, 255); // Default Red;
		ImColor Chicken_Text_Color = ImColor(255, 255, 255, 255); // Default white;
		ImColor World_Entities_BoxColor = ImColor(255, 255, 255, 255); // Default white;

		float BonesThickness = 0.5f;
		float C4BoxThickness = 2.5f;
		float LinesThickness = 1.5f;
		float BoxThickness = 1.7f;
		float nameTextSize = 15.0f;
		float distTextSize = 15.0f;
		float healthTextSize = 15.0f;
		float JointRadius = 2.0f;
		const float JointDisplayDistance = 2000.0f;
		const float SLEndPointDisplayDistance = 3000.0f;

		const char* availableSnapLinesPos[] = { "Top", "Center", "Bottom" };
		static int currentlinePosIndex = 2;
		Vector2 currentlinePos;

		const char* availableBoxDimensions[] = { "2D", "3D Shit" };
		static int currentBoxDimensionIndex = 0;
	}

	namespace Aimbot // Excluded
	{
		inline bool enableHotKey = true;
		const char* HotkeyOptions[] = {
			"X2_Mouse Button",
			"X1_Mouse Button",
			"Right Mouse Button",
			"Left Shift",
			"Left CTRL",
			"Left Alt"
		};
		static int CurrentHotkeyIndex = 0; // Index of the currently selected item
		int currentKey = 0x06;

		const char* AimPositions[] = {
			"Head",
			"Penis",
			"Neck",
			"Chest",
			"Stomach"
		};
		static int CurrentAimPosIndex = 0; // Index of the currently selected item
		inline bool TeamCheck = true;
		inline bool DormantCheck = true;

	}

	namespace Fov
	{
		inline int Default = 60;
	}
}