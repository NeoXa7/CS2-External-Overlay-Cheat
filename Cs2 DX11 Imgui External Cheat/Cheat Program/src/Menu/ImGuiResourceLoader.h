#pragma once
#include <ImGui/imgui.h>
#include <D3DX11/DX11Loader.h>
#include <Images/iVisuals.hpp>

namespace ImGui_Resource_Loader
{
	
	inline bool LoadImages(ID3D11Device* device)
	{
		// load images;
		bool example_image = D3DX11_Loader::LoadImageByMemory(device, Visuals, sizeof(Visuals), &D3DX11_Loader::ImageResource);
		if (!example_image)
			return false;
	}


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