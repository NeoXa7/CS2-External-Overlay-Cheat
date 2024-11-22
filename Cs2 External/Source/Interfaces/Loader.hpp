#pragma once
#include <ImGui/imgui.h>
#include <Fonts/Poppins.hpp>
#include <Fonts/Roboto-Bold.hpp>
#include <wtypes.h>

namespace ImGui_Loader
{	
	static ImFont* Font_Size_17 = nullptr;
	static ImFont* Font_Size_15 = nullptr;
	static ImFont* Font_Size_22 = nullptr;
	static ImFont* Icon_Font = nullptr;
	static ImFont* Roboto = nullptr;

	inline bool LoadFont() {		
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		io.LogFilename = nullptr;
		io.IniFilename = nullptr;

		// loading fonts;
		io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 20);
		Font_Size_17 = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 17);
		Font_Size_15 = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 15);
		Font_Size_22 = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 22);

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.FontDataOwnedByAtlas = false;
		Icon_Font = io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 22, &icons_config, icons_ranges);

		Roboto = io.Fonts->AddFontFromMemoryTTF((void*)RobotoBold, sizeof(Roboto), 15);

		return true;
	}
}

