#pragma once
#include <ImGui/imgui.h>

namespace ImGui_Resource_Loader
{
	inline bool LoadStyles()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		io.LogFilename = nullptr;
		io.IniFilename = nullptr;

		// window styles;
		style.WindowRounding = 0;

		// loading fonts;
		io.Fonts->AddFontFromFileTTF("D:\\Apps\\Fonts\\Roboto\\Roboto-Bold.ttf", 15.0f);

		return true;
	}
}