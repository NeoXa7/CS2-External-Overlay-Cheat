#pragma once
#include <ImGui/imgui.h>
#include <Maths/hVector.h>
#include <Maths/WorldToScreen.h>

namespace ESP
{
    inline void DrawBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor color = ImColor(255, 255, 255, 255), float thickness = 2.0f) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
    }

	inline void DrawLine(const Vector2& from, const Vector2& to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, bool drawEndPoint = false, float endPointRadius = 3.0f, ImColor endPointColor = ImColor(255, 255, 255, 255)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

		if (drawEndPoint) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), endPointRadius, endPointColor);
		}
	}

    inline void DrawHealthBar(const Vector2& topLeft, const Vector2& bottomRight, int health, ImColor fillColor = ImColor(0, 255, 0, 255), float barWidth = 7.0f, float offset = 5.0f) {
        float boxHeight = bottomRight.y - topLeft.y;
        float healthHeight = (health / 100.0f) * boxHeight;

        // Draw the filled portion of the health bar (only up to the health amount)
        ImVec2 healthTopLeft(topLeft.x - barWidth - offset, bottomRight.y - healthHeight); // Adjust based on health
        ImVec2 healthBottomRight(topLeft.x - offset, bottomRight.y);
        ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, fillColor, 0.0f, ImDrawFlags_None);
    }

    inline void DrawTextW(const char* text, const Vector2& position, ImU32 color, bool centered = false)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = ImGui::GetFont(); // Get the current font
        ImVec2 textSize = font->CalcTextSizeA(io.FontGlobalScale, FLT_MAX, 0.0f, text); // Get the size of the text

        // Apply global font scale if needed
        float globalScale = io.FontGlobalScale;

        if (centered)
        {
            ImVec2 textPos(position.x - textSize.x * globalScale / 2.0f, position.y - textSize.y * globalScale / 2.0f);
            ImGui::GetBackgroundDrawList()->AddText(textPos, color, text);
        }
        else
        {
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x, position.y), color, text);
        }
    }

	inline void DrawCircle(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x,y), radius, color, 0, thickness);
	}

    inline void DrawCircleFilled(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, 0);
    }

    inline void DrawBones(uintptr_t pawn)
    {
        uintptr_t BoneMatrix = GetBoneMatrix(pawn);
        Vector3 head = Memory::ReadMemory<Vector3>(BoneMatrix + BoneIndex::HEAD * 32);

        Vector2 headScreenPos;
        Vector2 screenPos;

        for (int i = 0; i < sizeof(boneConnections) / sizeof(boneConnections[0]); i++)
        {
            int bone1 = boneConnections[i].bone1;
            int bone2 = boneConnections[i].bone2;

            Vector3 VectorBone1 = Memory::ReadMemory<Vector3>(BoneMatrix + bone1 * 32);
            Vector3 VectorBone2 = Memory::ReadMemory<Vector3>(BoneMatrix + bone2 * 32);

            if (WorldToScreen(entities.Position, screenPos, game.ViewMatrix, Screen_WIDTH, Screen_HEIGHT) &&
                WorldToScreen(head, headScreenPos, game.ViewMatrix, Screen_WIDTH, Screen_HEIGHT))
            {
                Vector2 b1, b2;
                if (WorldToScreen(VectorBone1, b1, game.ViewMatrix, Screen_WIDTH, Screen_HEIGHT) &&
                    WorldToScreen(VectorBone2, b2, game.ViewMatrix, Screen_WIDTH, Screen_HEIGHT))
                {
                    float headHeight = entities.GetHeadHeight(screenPos, headScreenPos);
                    ESP::DrawLine(b1, b2, Config::Esp::BonesColor, Config::Esp::BonesThickness);

                    if (!Config::Esp::headBoneFilled)
                    {
                        ESP::DrawCircle(headScreenPos.x, headScreenPos.y, headHeight, Config::Esp::HeadBoneColor, Config::Esp::BonesThickness);
                    }
                    else
                    {
                        ESP::DrawCircleFilled(headScreenPos.x, headScreenPos.y, headHeight, Config::Esp::HeadBoneColor);
                    }
                    
                }
            }          
        }
    }
}