#include "ui/SectionsUtilitary.h"
#include "imgui.h"
#include <array>

namespace SectionsUtilitary {
    void renderPositionEditor(const std::string & labelPrefix, Vec3 & position, const std::function<void(const Vec3 &)> & onPositionChanged) {
        ImGuiIO & io = ImGui::GetIO();
        ImGui::NewLine();

        const float fastDelta = 0.2f;
        const float slowDelta = 0.01f;
        const float holdThreshold = 0.15f;

        static float s_holdTimers[3] = {0.f, 0.f, 0.f}; // X, Y, Z

        const char * axes[] = {"X", "Y", "Z"};
        float * posValues[] = {&position.x, &position.y, &position.z};

        for (int i = 0; i < 3; ++i) {
            ImGui::SameLine();
            ImGui::PushID((labelPrefix + axes[i]).c_str());

            ImGui::Text("%s", axes[i]);
            ImGui::SameLine();

            if (ImGui::Button("-")) {
                if (s_holdTimers[i] < holdThreshold) {
                    *posValues[i] -= fastDelta;
                    onPositionChanged(position);
                }
                s_holdTimers[i] = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimers[i] += io.DeltaTime;
                if (s_holdTimers[i] > holdThreshold) {
                    *posValues[i] -= slowDelta;
                    onPositionChanged(position);
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("+")) {
                if (s_holdTimers[i] < holdThreshold) {
                    *posValues[i] += fastDelta;
                    onPositionChanged(position);
                }
                s_holdTimers[i] = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimers[i] += io.DeltaTime;
                if (s_holdTimers[i] > holdThreshold) {
                    *posValues[i] += slowDelta;
                    onPositionChanged(position);
                }
            }

            ImGui::PopID();
        }
    }

}