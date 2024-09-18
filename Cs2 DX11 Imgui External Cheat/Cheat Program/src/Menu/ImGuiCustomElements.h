#pragma once

#include <ImGui/imgui_internal.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

namespace C_Elements
{
	inline void CenterText(const char* format, const float y_padding = 0.0f, ImColor color = ImColor(255, 255, 255))
	{
		const ImVec2 text_size = ImGui::CalcTextSize(format);
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (text_size.x / 2));


		if (y_padding > 0.0f)
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
		ImGui::TextColored(color, format);
	}

	inline void Checkbox(const char* format, bool* value)
	{
		int colorCount = 3; // Number of colors to push when unchecked
	
		if (*value)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(116, 84, 183, 255).Value);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(116, 84, 183, 255).Value);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(116, 84, 183, 255).Value);
			ImGui::PushStyleColor(ImGuiCol_CheckMark, ImColor(10, 10, 10, 255).Value);
			colorCount = 4; // Number of colors to push when checked
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(29, 46, 72, 255).Value);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(29, 46, 72, 255).Value);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(29, 46, 72, 255).Value);
		}
	
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.5f, 1.5f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
	
		ImGui::Checkbox(format, value);
	
		ImGui::PopStyleColor(colorCount); // Pop the exact number of colors that were pushed
		ImGui::PopStyleVar(2); // Pop the style variables
	
		// If spacing is needed, specify the size in ImVec2(x, y)
		 ImGui::Dummy(ImVec2());
	}

	inline void CustomizeMenuTitleBar()
	{
		// Get the current ImGui style
		ImGuiStyle& style = ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();

		// Customize the menu title bar colors
		style.Colors[ImGuiCol_TitleBg] = ImColor(116, 84, 183, 255); 
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(116, 84, 183, 255);

	}

	inline void InputText(const char* label,  float roundness, char* buf, size_t buf_size, auto inputTextFlag, ImVec2 size = ImVec2(0, 0), ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		// Create the custom InputText widget
		ImGui::InputText(label, buf, buf_size, inputTextFlag);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(2); // Pop the 4 style colors
		ImGui::PopStyleVar(2);   // Pop the 2 style variables
	}

	inline void InputFloat(const char* label, float roundness, float* value, ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();
		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		ImGui::InputFloat(label, value);

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	inline void InputInt(const char* label,  float roundness, int* value, ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		// Disable step buttons by setting the step to zero
		ImGui::InputInt(label, value);

		// Pop custom style colors and variables
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	inline void InputIntHex(const char* label, float roundness, int* value, ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		// Create a buffer to hold the hexadecimal string
		char hexValue[16];
		snprintf(hexValue, sizeof(hexValue), "0x%X", *value); // Format the integer as hex

		ImGui::SetNextItemWidth(100.0f);
		// Display the hexadecimal value in an input text box
		if (ImGui::InputText(label, hexValue, sizeof(hexValue), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase))
		{
			// Convert the hexadecimal string back to an integer using sscanf_s
			sscanf_s(hexValue, "%x", value);
		}

		// Pop custom style colors and variables
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	inline void SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImColor SliderBGColor = ImColor(29, 46, 72, 255), ImColor SliderGrabColor = ImColor(66, 150, 250, 255), ImColor SliderGrabActiveColor = ImColor(70, 160, 250, 255))
	{
		// Push custom style variables and colors
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f); // Adjust frame rounding
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); // Adjust padding
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 50.0f); // Adjust grab rounding

		ImGui::PushStyleColor(ImGuiCol_FrameBg, SliderBGColor.Value); // Background color of the slider track
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, SliderBGColor.Value); // Background color of the slider track when hovered
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, SliderBGColor.Value); // Background color of the slider track when clicked
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderGrabColor.Value);
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderGrabActiveColor.Value);

		ImGui::SliderFloat(label, v, v_min, v_max, format);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(5); // Pop the 5 style colors
		ImGui::PopStyleVar(3);   // Pop the 2 style variables
	}

	inline void SliderInt(const char* label, int* v, int v_min, float v_max, const char* format = "%d", ImColor SliderBGColor = ImColor(29, 46, 72, 255), ImColor SliderGrabColor = ImColor(66, 150, 250, 255), ImColor SliderGrabActiveColor = ImColor(70, 160, 250, 255))
	{
		// Push custom style variables and colors
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f); // Adjust frame rounding
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); // Adjust padding
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 50.0f); // Adjust grab rounding

		ImGui::PushStyleColor(ImGuiCol_FrameBg, SliderBGColor.Value); // Background color of the slider track
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, SliderBGColor.Value); // Background color of the slider track when hovered
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, SliderBGColor.Value); // Background color of the slider track when clicked
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderGrabColor.Value);
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderGrabActiveColor.Value);

		ImGui::SliderInt(label, v, v_min, v_max, format);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(5); // Pop the 5 style colors
		ImGui::PopStyleVar(3);   // Pop the 2 style variables
	}

	inline void BeginCustomizingCollapsingHeader(float header_roundess = 3.5f, ImVec4 headerColor = ImColor(25, 47, 73, 255), ImVec4 headerTextColor = ImColor(255, 255, 255, 255), ImVec4 headerHoveredColor = ImColor(32, 58, 94, 255), ImVec4 headerActiveColor = ImColor(25, 47, 73, 255))
	{
		// styling custom header 
		ImGui::PushStyleColor(ImGuiCol_Header, headerColor);
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, headerHoveredColor);
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, headerActiveColor);
		ImGui::PushStyleColor(ImGuiCol_Text, headerTextColor);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, header_roundess); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.5, 2.5)); // Adjust padding
	}

	inline void EndCustomizingCollapsingHeader()
	{
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(2);
	}

	inline void LeaveLine(int a = 1)
	{
		for (int i = 0; i < a; i++)
		{
			ImGui::Dummy(ImVec2());
		}	
	}

	template <typename type>
	inline void ColorEditor(const char* label, type *color)
	{
		ImGui::ColorEdit4(label, (float*)color);	 
	}

	ImColor RGBToImColor(int r, int g, int b, int a = 255) {
		return ImColor(r, g, b, a);
	}

	inline bool ComboBox(const char* label, const char* combo_items, int* current_index, const char* const items[], int items_size, float roundness = 2.0f, float width = 100.0f)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);

		ImGui::SetNextItemWidth(width);
		bool is_open = ImGui::BeginCombo(label, combo_items);
		
		if (is_open)
		{
			for (int i = 0; i < items_size; ++i)
			{
				bool is_selected = (i == *current_index);
				if (ImGui::Selectable(items[i], is_selected))
					*current_index = i;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::PopStyleVar(1);

		return is_open;
	}

}
