#include <ImGui/imgui.h>

inline void LeaveLine(int num = 1)
{
	for (int i = 0; i < num; i++)
	{
		ImGui::Dummy(ImVec2());
	}
}

template <typename type>
inline void ColorEditor(const char* label, type* color, float roundness = 2.0f)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(239, 73, 88, 255).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(229, 63, 78, 255).Value);
    ImGui::ColorEdit4(label, (float*)color);
    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(2);
}

inline bool ComboBox(const char* label, const char* combo_items, int* current_index, const char* const items[], int items_size, float roundness = 2.0f, float width = 150.0f)
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(15, 15, 15, 155).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(15, 15, 15, 155).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(15, 15, 15, 155).Value);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);

    ImGui::SetNextItemWidth(width);
    bool is_open = ImGui::BeginCombo(label, combo_items);

    if (is_open)
    {
        for (int i = 0; i < items_size; ++i)
        {
            bool is_selected = (i == *current_index);
            if (is_selected)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 215, 0).Value);
            }

            if (ImGui::Selectable(items[i], is_selected))
            {
                *current_index = i;
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }

            if (is_selected)
            {
                ImGui::PopStyleColor();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(3);

    return is_open;
}

inline bool CustomButton(const char* label, ImVec2 size = ImVec2(150, 40)) // width, height
{
    bool clicked = ImGui::Button(label, size);
    return clicked;
}

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
    ImColor CheckMarkColor = ImColor(239, 73, 88, 255);
    ImColor CheckBoxBGColor = ImColor(31, 30, 31, 255);
    ImColor CheckBoxHoveredBGColor = ImColor(27, 25, 22, 255);
    ImColor CheckBoxActiveBGColor = ImColor(31, 30, 31, 255);

	int colorCount = 3; // Number of colors to push when unchecked

	if (*value)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckBoxBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckBoxHoveredBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckBoxActiveBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckMarkColor.Value);
		colorCount = 4; // Number of colors to push when checked
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckBoxBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckBoxHoveredBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckBoxActiveBGColor.Value);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.5f, 1.5f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

	ImGui::Checkbox(format, value);

	ImGui::PopStyleColor(colorCount); // Pop the exact number of colors that were pushed
	ImGui::PopStyleVar(2); // Pop the style variables

	// If spacing is needed, specify the size in ImVec2(x, y)
	ImGui::Dummy(ImVec2());
}

inline void SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f")
{
    ImColor SliderBGColor = ImColor(30, 29, 30, 255);
    ImColor SliderGrabColor = ImColor(239, 73, 88, 255);
    ImColor SliderGrabActiveColor = ImColor(219, 63, 78, 255);

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

inline void SliderInt(const char* label, int* v, int v_min, float v_max, const char* format = "%d")
{
    ImColor SliderBGColor = ImColor(30, 29, 30, 255);
    ImColor SliderGrabColor = ImColor(239, 73, 88, 255);
    ImColor SliderGrabActiveColor = ImColor(219, 63, 78, 255);

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

inline void PlainText(const char* label, ImColor color = ImColor(255, 255, 255, 255))
{
    ImGui::TextColored(color, label);
}

inline void SetCustomStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    ImColor MenuBGColor = ImColor(11, 14, 15, 255);
    ImColor ButtonBGColor = ImColor(239, 73, 88, 255);
    ImColor ButtonHoveredBGColor = ImColor(219, 53, 68, 255);
    ImColor ButtonActiveBGColor = ImColor(239, 73, 88, 255);
    ImColor ContainerBGColor = ImColor(33, 34, 45, 255);

    // Window and container background colors
    style.Colors[ImGuiCol_WindowBg] = MenuBGColor.Value;
    style.Colors[ImGuiCol_ChildBg] = ContainerBGColor.Value;

    // Button style
    style.Colors[ImGuiCol_Button] = ButtonBGColor.Value;
    style.Colors[ImGuiCol_ButtonHovered] = ButtonHoveredBGColor.Value;
    style.Colors[ImGuiCol_ButtonActive] = ButtonActiveBGColor.Value;

    // Roundings and padding
    style.WindowRounding = 10.0f;
    style.ChildRounding = 10.0f;
    style.FrameRounding = 8.0f; // Adjust frame rounding (slider track, buttons, etc.)
    style.FramePadding = ImVec2(10, 5); // Padding for the slider or buttons
    style.ChildBorderSize = 0.1f;
    style.ScrollbarSize = 5.0f;
    style.ScrollbarRounding = 2.0f;

    // You can adjust these to customize how sliders appear:
    style.ItemSpacing = ImVec2(8, 6); // Spacing between widgets
}
