#include "ui/Sections.h"
#include "Globals.h"
#include "engine/Scene.h"
#include "imgui.h"

namespace UI {

    void drawSensitivitySection() {
        if (ImGui::CollapsingHeader("Sensibilité")) {
            ImGui::SeparatorText("Sensibilité de la souris");
            ImGui::SliderFloat("Sensibilité rotation##SliderRot", &sensibility_rot, 0.01f, 0.5f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::InputFloat("Sensibilité rotation##InputRot", &sensibility_rot, 0.01f, 0.5f, "%.2f");
            ImGui::SeparatorText("Sensibilité du clavier");
            ImGui::SliderFloat("Sensibilité déplacement##Sliderdepl", &sensibility_depl, 0.1f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::InputFloat("Sensibilité déplacement##Inputdepl", &sensibility_depl, 0.1f, 1.f, "%.2f");
            ImGui::Separator();
            if (ImGui::Button("Réinitialisation rotation")) {
                sensibility_rot = 0.01f;
            }
            ImGui::SameLine();
            if (ImGui::Button("Réinitialisation déplacement")) {
                sensibility_depl = 0.10f;
            }
        }
    }

    void drawFogSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Fog")) {
            ImGui::SeparatorText("Type de fog actif");
            static const char * items[] = {"Aucun", "Linéaire", "Exponentiel", "Exponentiel²"};
            static int currentType = scene->getFogType();
            if (ImGui::Combo("Type de Fog", &currentType, items, IM_ARRAYSIZE(items))) {
                scene->setFogType(currentType);
            }

            ImGui::SeparatorText("Valeurs du Fog");
            ImGui::SliderFloat("Début", scene->getFogStart(), 0.0f, *scene->getFogEnd(), "%.1f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::SliderFloat("Fin", scene->getFogEnd(), *scene->getFogStart(), 100.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
            float fogDensity = *scene->getFogDensity();
            if (ImGui::SliderFloat("Densité##slider", &fogDensity, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp) ||
                ImGui::InputFloat("Densité##input", &fogDensity, 0.01f, 0.1f, "%.3f")) {
                scene->setFogDensity(fogDensity);
            }

            ImGui::SeparatorText("Couleur du Fog");
            Color & fogColor = scene->getFogColor();
            float colorTmp[3] = {
                fogColor.r / 255.0f,
                fogColor.g / 255.0f,
                fogColor.b / 255.0f};

            if (ImGui::ColorEdit3("Couleur", colorTmp)) {
                fogColor.r = colorTmp[0] * 255.0f;
                fogColor.g = colorTmp[1] * 255.0f;
                fogColor.b = colorTmp[2] * 255.0f;
            }
        }
    }

    void drawQuitButton(GLFWwindow * window) {
        if (ImGui::Button("Quitter")) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void drawTextureSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Textures")) {
            for (std::shared_ptr<Entity> & entityPtr : scene->getEntities()) {
                ImGui::PushID(entityPtr.get()); // ou entityPtr->getName().c_str()

                std::string * label = new std::string("Entité: " + entityPtr->getName());
                ImGui::SeparatorText(label->c_str());
                delete label;
                Material & material = entityPtr->getMaterial();

                if (material.diffuse_text)
                    ImGui::Checkbox("Utiliser texture diffuse", &material.useDiffuse);
                if (material.normal_map)
                    ImGui::Checkbox("Utiliser normal map", &material.useNormal);
                if (material.specular_map)
                    ImGui::Checkbox("Utiliser specular map", &material.useSpecular);

                ImGui::PopID();
            }
        }
    }

    void drawDirectionnalLightSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Lumière directionnelle")) {
            ImGui::SeparatorText("Paramètres de la lumière directionnelle");
            LightingManager & lightingManager = scene->getLightingManager();
            Light * light = lightingManager.getFirstDirectional();

            ImGui::Checkbox("Activer", &light->active);
        }
    }

}
