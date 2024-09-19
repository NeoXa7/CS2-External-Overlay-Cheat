#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <Globals/hGlobals.h>

void DrawCrosshair(float crosshairSize = 10.0f, ImColor color = ImColor(255, 255, 255, 255)) {
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    ImVec2 center = ImVec2(Screen_WIDTH / 2, Screen_HEIGHT / 2);

    // Draw horizontal line
    draw_list->AddLine(ImVec2(center.x - crosshairSize, center.y),
        ImVec2(center.x + crosshairSize, center.y), color, 1.0f);

    // Draw vertical line
    draw_list->AddLine(ImVec2(center.x, center.y - crosshairSize),
        ImVec2(center.x, center.y + crosshairSize), color, 1.0f);
}