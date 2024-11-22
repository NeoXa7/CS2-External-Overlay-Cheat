#pragma once
#include <ImGui/imgui.h>
#include <Maths/Vector.hpp>
#include <Maths/WorldToScreen.hpp>
#include <Utilities/Config.hpp>
#include <Readers/Entity.hpp>
#include <Readers/Game.hpp>

namespace DrawUtils
{
    inline void DrawBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor color = ImColor(255, 255, 255, 255), float thickness = 2.0f) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
    }

    inline void DrawFilledBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor fillColor = ImColor(255, 0, 0, 128), float borderThickness = 2.0f, ImColor borderColor = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), fillColor, 0.0f, ImDrawFlags_None);
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), borderColor, 0.0f, ImDrawFlags_None, borderThickness);
    }


    inline void DrawLine(const Vector2& from, const Vector2& to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, bool drawEndPoint = false, float endPointRadius = 3.0f, ImColor endPointColor = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

        if (drawEndPoint) {
            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), endPointRadius, endPointColor);
        }
    }

    inline void DrawHealthBar(const Vector2& topLeft, const Vector2& bottomRight, int health, ImColor fillColor = ImColor(0, 255, 0, 255), float barWidth = 2.0f, float offset = 6.0f) {
        float boxHeight = bottomRight.y - topLeft.y;
        float healthHeight = (health / 100.0f) * boxHeight;
        float BGRectThickness = 1.0f;

        ImVec2 borderTopLeft(topLeft.x - barWidth - offset - BGRectThickness, topLeft.y - BGRectThickness);
        ImVec2 borderBottomRight(topLeft.x - offset + BGRectThickness, bottomRight.y + BGRectThickness);
        ImColor BGColor = ImColor(10, 10, 10, 255);
        ImGui::GetBackgroundDrawList()->AddRectFilled(borderTopLeft, borderBottomRight, BGColor, 0.0f, ImDrawFlags_None);

        // Draw the actual health bar
        ImVec2 healthTopLeft(topLeft.x - barWidth - offset, bottomRight.y - healthHeight);
        ImVec2 healthBottomRight(topLeft.x - offset, bottomRight.y);
        ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, fillColor, 0.0f, ImDrawFlags_None);
    }


    inline void DrawTextW(std::string Text, Vector2 Pos, ImColor Color = ImColor(255,255,255,255), float FontSize = 15.0f, bool KeepCenter = true)
    {
        if (!KeepCenter)
        {
            ImGui::PushFont(ImGui_Loader::Roboto);
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos.ToImVec2(), Color, Text.c_str());
            ImGui::PopFont();
        }
        else
        {
            ImGui::PushFont(ImGui_Loader::Roboto);
            float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text.c_str()).x;
            ImVec2 Pos_ = { Pos.x - TextWidth / 2,Pos.y };
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text.c_str());
            ImGui::PopFont();
        }
    }

    inline void DrawTextWithStroke(const std::string& text, Vector2 position, ImColor textColor = ImColor(255, 255, 255, 255), ImColor strokeColor = ImColor(0, 0, 0, 255), float fontSize = 15.0f, float strokeThickness = 1.0f)
    {
        ImVec2 pos = ImVec2(position.x, position.y);

        ImGui::PushFont(ImGui_Loader::Roboto);
        // Draw stroke (outline) by rendering the text in 8 surrounding positions (up, down, left, right, and diagonals)
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - strokeThickness, pos.y), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + strokeThickness, pos.y), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y - strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y + strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - strokeThickness, pos.y - strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + strokeThickness, pos.y - strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - strokeThickness, pos.y + strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + strokeThickness, pos.y + strokeThickness), strokeColor, text.c_str());

        // Draw the main text on top
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y), textColor, text.c_str());
        ImGui::PopFont();
    }


    //inline void DrawTextW(const char* text, const Vector2& position, ImU32 color, bool centered = false)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    ImFont* font = ImGui::GetFont(); // Get the current font
    //    ImVec2 textSize = font->CalcTextSizeA(io.FontGlobalScale, FLT_MAX, 0.0f, text); // Get the size of the text

    //    // Apply global font scale if needed
    //    float globalScale = io.FontGlobalScale;

    //    if (centered)
    //    {
    //        ImVec2 textPos(position.x - textSize.x * globalScale / 2.0f, position.y - textSize.y * globalScale / 2.0f);
    //        ImGui::PushFont(ImGui_Loader::Font_Size_15);
    //        ImGui::GetForegroundDrawList()->AddText(textPos, color, text);
    //        ImGui::PopFont();
    //    }
    //    else
    //    {
    //        ImGui::PushFont(ImGui_Loader::Font_Size_15);
    //        ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x, position.y), color, text);
    //        ImGui::PopFont();
    //    }
    //}

    inline void DrawCircle(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, int segments = 0) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, thickness);
    }

    inline void DrawCircleFilled(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, 0);
    }

    inline void DrawBones(uintptr_t pawn)
    {
        uintptr_t BoneMatrix = GetBoneMatrix(pawn);
        Vector3 head = mem.ReadMemory<Vector3>(BoneMatrix + BoneIndex::HEAD * 32);

        Vector2 headScreenPos;
        Vector2 screenPos;

        for (int i = 0; i < sizeof(boneConnections) / sizeof(boneConnections[0]); i++)
        {
            int bone1 = boneConnections[i].bone1;
            int bone2 = boneConnections[i].bone2;

            Vector3 VectorBone1 = mem.ReadMemory<Vector3>(BoneMatrix + bone1 * 32);
            Vector3 VectorBone2 = mem.ReadMemory<Vector3>(BoneMatrix + bone2 * 32);

            if (WorldToScreen(entities->Position, screenPos, game.ViewMatrix) &&
                WorldToScreen(head, headScreenPos, game.ViewMatrix))
            {
                Vector2 b1, b2;
                if (WorldToScreen(VectorBone1, b1, game.ViewMatrix) &&
                    WorldToScreen(VectorBone2, b2, game.ViewMatrix))
                {
                    float headHeight = entities->GetHeadHeight(screenPos, headScreenPos);
                    if (!Config::Esp::ShowBoneJoints)
                    {
                        DrawUtils::DrawLine(b1, b2, Config::Esp::BonesColor, Config::Esp::BonesThickness);
                    }
                    else
                    {
                        if (game.Dist_ETLP < Config::Esp::JointDisplayDistance)
                        {
                            DrawUtils::DrawLine(
                                b1, 
                                b2, 
                                Config::Esp::BonesColor, 
                                Config::Esp::BonesThickness, 
                                true, 
                                Config::Esp::JointRadius, 
                                Config::Esp::BoneJointsColor
                            );
                        }
                        else
                        {
                            DrawUtils::DrawLine(b1, b2, Config::Esp::BonesColor, Config::Esp::BonesThickness);
                        }

                    }

                    if (!Config::Esp::HeadFilled)
                    {
                        DrawUtils::DrawCircle(headScreenPos.x, headScreenPos.y, headHeight, Config::Esp::HeadColor, Config::Esp::BonesThickness);
                    }
                    else
                    {
                        DrawUtils::DrawCircleFilled(headScreenPos.x, headScreenPos.y, headHeight, Config::Esp::HeadColor);
                    }

                }
            }
        }
    }

    inline void DrawCrosshair(float crosshairSize = 10.0f, ImColor color = ImColor(255, 255, 255, 255)) {
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        ImVec2 center = ImVec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

        // Draw horizontal line
        draw_list->AddLine(ImVec2(center.x - crosshairSize, center.y),
            ImVec2(center.x + crosshairSize, center.y), color, 1.0f);

        // Draw vertical line
        draw_list->AddLine(ImVec2(center.x, center.y - crosshairSize),
            ImVec2(center.x, center.y + crosshairSize), color, 1.0f);
    }

    /*inline void DrawAimFovCircle()
    {
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2,
            ImGui::GetIO().DisplaySize.y / 2), Config::Aimbot::AimFov,
            ImGui::ColorConvertFloat4ToU32(Config::Aimbot::FovCircleColor), 100, Config::Aimbot::FovCircleThickness
        );
    }*/

    inline void Draw3DBox(Vector3* corners, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f)
    {
        Vector2 screenCorners[8];

        for (int i = 0; i < 8; i++) {
            if (!WorldToScreen(corners[i], screenCorners[i], game.ViewMatrix))
                return;
        }

        for (int i = 0; i < 4; i++) {
            int next = (i + 1) % 4; 
            DrawUtils::DrawLine(screenCorners[i], screenCorners[next], color, thickness);
            DrawUtils::DrawLine(screenCorners[i + 4], screenCorners[next + 4], color, thickness);
            DrawUtils::DrawLine(screenCorners[i], screenCorners[i + 4], color, thickness);
        }
    }
}