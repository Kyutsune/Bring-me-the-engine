#include "ui/Sections.h"
#include "Globals.h"
#include "engine/Scene.h"
#include "imgui.h"

namespace Sections {

    void sensitivitySection() {
        if (ImGui::CollapsingHeader("Sensibilité")) {
            ImGui::SeparatorText("Sensibilité de la souris");
            ImGui::SliderFloat("Sensibilité rotation##SliderRot", &g_sensibility_rot, 0.01f, 0.5f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::InputFloat("Sensibilité rotation##InputRot", &g_sensibility_rot, 0.01f, 0.5f, "%.2f");
            ImGui::SeparatorText("Sensibilité du clavier");
            ImGui::SliderFloat("Sensibilité déplacement##Sliderdepl", &g_sensibility_depl, 0.1f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::InputFloat("Sensibilité déplacement##Inputdepl", &g_sensibility_depl, 0.1f, 1.f, "%.2f");
            ImGui::Separator();
            if (ImGui::Button("Réinitialisation rotation")) {
                g_sensibility_rot = 0.01f;
            }
            ImGui::SameLine();
            if (ImGui::Button("Réinitialisation déplacement")) {
                g_sensibility_depl = 0.10f;
            }
        }
    }

    void fogSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Fog")) {
            ImGui::SeparatorText("Type de fog actif");
            static const char * s_items[] = {"Aucun", "Linéaire", "Exponentiel", "Exponentiel²"};
            static int s_currentFogType = scene->getFogType();
            if (ImGui::Combo("Type de Fog", &s_currentFogType, s_items, IM_ARRAYSIZE(s_items))) {
                scene->setFogType(s_currentFogType);
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

    void quitButton(GLFWwindow * window) {
        if (ImGui::Button("Quitter")) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void textureSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Textures")) {
            for (std::shared_ptr<Entity> & entityPtr : scene->getEntities()) {
                ImGui::PushID(entityPtr.get());

                ImGui::SeparatorText(("Entité: " + entityPtr->getName()).c_str());
                Material & material = entityPtr->getMaterial();

                if (material.m_diffuseTexture)
                    ImGui::Checkbox("Utiliser texture diffuse", &material.m_useDiffuse);
                if (material.m_normalMap)
                    ImGui::Checkbox("Utiliser normal map", &material.m_useNormal);
                if (material.m_specularMap)
                    ImGui::Checkbox("Utiliser specular map", &material.m_useSpecular);

                ImGui::PopID();
            }
        }
    }

    void lightSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Lumières")) {

            if (ImGui::TreeNode("Lumière directionnelle")) {
                directionnalLightSection(scene);
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Lumières ponctuelles")) {
                ponctualLightSection(scene);
                ImGui::TreePop();
            }
        }
    }

    void directionnalLightSection(Scene * scene) {
        ImGui::SeparatorText("Paramètres de la lumière directionnelle");
        LightingManager & lightingManager = scene->getLightingManager();
        Light * light = lightingManager.getFirstDirectional();

        bool isActive = light->isActive();
        if (ImGui::Checkbox("Activer", &isActive)) {
            light->setActive(isActive);
        }
        float intensity = light->getIntensity() * 100.0f;
        if (ImGui::SliderFloat("Intensité", &intensity, 0.0f, 100.0f, "%.0f%%", ImGuiSliderFlags_AlwaysClamp)) {
            light->setIntensity(intensity / 100.0f);
        }

        // TODO: Rajouter le fait de pouvoir modifier la direction de la lumière directionnelle
    }

    void ponctualLightSection(Scene * scene) {
        ImGui::SeparatorText("Paramètres des lumières ponctuelles");
        std::vector<Light *> lights = scene->getLightingManager().getPonctualLightsRef();
        size_t count_of_lights = 1;

        for (Light * light : lights) {
            ImGui::PushID(light);
            ImGui::SeparatorText(("Lumière " + std::to_string(count_of_lights++)).c_str());

            bool isActive = light->isActive();
            if (ImGui::Checkbox("Activer", &isActive)) {
                light->setActive(isActive);
            }
            float intensity = light->getIntensity() * 100.0f;
            if (ImGui::SliderFloat("Intensité", &intensity, 0.0f, 200.0f, "%.0f%%", ImGuiSliderFlags_AlwaysClamp)) {
                light->setIntensity(intensity / 100.0f);
            }

            ImGui::SeparatorText("Position de la lumière");
            Vec3 position = light->getPosition();

            if (ImGui::DragFloat3("Position", &position.x, 0.01f, -100.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp)) {
                light->setPosition(position);
            }

            ImGuiIO & io = ImGui::GetIO();

            // TODO: Plus tard il faudrait rajouter un bouton pour pouvoir adapter le delta de déplacement
            //  En gros permettre de déplacer plus vite que de 0.01f par tick au maintien et de 0.2 par clic

            // Axe X
            ImGui::PushID("X");
            ImGui::Text("X");
            ImGui::SameLine();
            static float s_holdTimerX = 0.0f;

            if (ImGui::Button("-")) {
                if (s_holdTimerX < 0.15f) {
                    position.x -= 0.2f;
                    light->setPosition(position);
                }
                s_holdTimerX = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimerX += io.DeltaTime;
                if (s_holdTimerX > 0.15f) {
                    position.x -= 0.01f;
                    light->setPosition(position);
                }
            }
            ImGui::SameLine();

            if (ImGui::Button("+")) {
                if (s_holdTimerX < 0.15f) {
                    position.x += 0.2f;
                    light->setPosition(position);
                }
                s_holdTimerX = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimerX += io.DeltaTime;
                if (s_holdTimerX > 0.15f) {
                    position.x += 0.01f;
                    light->setPosition(position);
                }
            }
            ImGui::PopID();

            // Axe Y
            ImGui::SameLine();
            ImGui::PushID("Y");
            ImGui::Text("Y");
            ImGui::SameLine();
            static float s_holdTimerY = 0.0f;

            if (ImGui::Button("-")) {
                if (s_holdTimerY < 0.15f) {
                    position.y -= 0.2f;
                    light->setPosition(position);
                }
                s_holdTimerY = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimerY += io.DeltaTime;
                if (s_holdTimerY > 0.15f) {
                    position.y -= 0.01f;
                    light->setPosition(position);
                }
            }
            ImGui::SameLine();

            if (ImGui::Button("+")) {
                if (s_holdTimerY < 0.15f) {
                    position.y += 0.2f;
                    light->setPosition(position);
                }
                s_holdTimerY = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimerY += io.DeltaTime;
                if (s_holdTimerY > 0.15f) {
                    position.y += 0.01f;
                    light->setPosition(position);
                }
            }
            ImGui::PopID();

            // Axe Z
            ImGui::SameLine();
            ImGui::PushID("Z");
            ImGui::Text("Z");
            ImGui::SameLine();
            static float s_holdTimerZ = 0.0f;

            if (ImGui::Button("-")) {
                if (s_holdTimerZ < 0.15f) {
                    position.z -= 0.2f;
                    light->setPosition(position);
                }
                s_holdTimerZ = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimerZ += io.DeltaTime;
                if (s_holdTimerZ > 0.15f) {
                    position.z -= 0.01f;
                    light->setPosition(position);
                }
            }
            ImGui::SameLine();

            if (ImGui::Button("+")) {
                if (s_holdTimerZ < 0.15f) {
                    position.z += 0.2f;
                    light->setPosition(position);
                }
                s_holdTimerZ = 0.0f;
            }
            if (ImGui::IsItemActive()) {
                s_holdTimerZ += io.DeltaTime;
                if (s_holdTimerZ > 0.15f) {
                    position.z += 0.01f;
                    light->setPosition(position);
                }
            }
            ImGui::PopID();

            ImGui::SeparatorText("Couleur de la lumière");
            Color & lightColor = light->getColor();

            float colorTmp[3] = {
                lightColor.r / 255.0f,
                lightColor.g / 255.0f,
                lightColor.b / 255.0f};

            if (ImGui::ColorEdit3("Couleur", colorTmp)) {
                lightColor.r = colorTmp[0] * 255.0f;
                lightColor.g = colorTmp[1] * 255.0f;
                lightColor.b = colorTmp[2] * 255.0f;
            }

            ImGui::PopID();
        }
    }

    bool SceneSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Scène")) {
            static int currentScene = g_sceneIndex - 1;
            static int selectedScene = g_sceneIndex - 1;

            ImGui::SeparatorText("Séléction de la scène courante");
            if (ImGui::Combo("Scene", &selectedScene, "Scene 1\0Scene 2\0")) {
                if (selectedScene != currentScene) {
                    currentScene = selectedScene;
                    g_scenePtr.reset();
                    std::cout << "Changement de scène: " << currentScene + 1 << std::endl;
                    g_scenePtr = std::make_unique<Scene>(currentScene + 1);
                    g_scene = g_scenePtr.get();
                    return true;
                }
            }
        }
        return false;
    }

}
