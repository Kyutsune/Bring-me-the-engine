#include "ui/Sections.h"
#include "Globals.h"
#include "engine/Scene.h"
#include "imgui.h"
#include "ui/SectionsUtilitary.h"
#include <unordered_map>

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
                fogColor.r,
                fogColor.g,
                fogColor.b};

            if (ImGui::ColorEdit3("Couleur", colorTmp)) {
                fogColor.r = colorTmp[0];
                fogColor.g = colorTmp[1];
                fogColor.b = colorTmp[2];
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
        float intensity = light->getIntensity() * 10.0f;
        if (ImGui::SliderFloat("Intensité", &intensity, 0.0f, 400.0f, "%.0f%%", ImGuiSliderFlags_AlwaysClamp)) {
            light->setIntensity(intensity / 10.0f);
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
            float intensity = light->getIntensity() * 10.f;
            if (ImGui::SliderFloat("Intensité", &intensity, 0.0f, 200.0f, "%.0f%%", ImGuiSliderFlags_AlwaysClamp)) {
                light->setIntensity(intensity / 10.f); // Reconverti en [0.0 – 10.0]
            }

            ImGui::SeparatorText("Position de la lumière");
            Vec3 position = light->getPosition();

            if (ImGui::DragFloat3("Position", &position.x, 0.01f, -100.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp)) {
                light->setPosition(position);
            }

            SectionsUtilitary::renderPositionEditor("Light" + std::to_string(count_of_lights), position, [&](const Vec3 & newPos) {
                light->setPosition(newPos);
            });

            ImGui::SeparatorText("Couleur de la lumière");
            Color & lightColor = light->getColor();

            float colorTmp[3] = {
                lightColor.r,
                lightColor.g,
                lightColor.b};

            if (ImGui::ColorEdit3("Couleur", colorTmp)) {
                lightColor.r = colorTmp[0];
                lightColor.g = colorTmp[1];
                lightColor.b = colorTmp[2];
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

    void objectSection(Scene * scene) {
        // Si on clique sur une entité, on force l'ouverture de cette section là
        if (g_forceOpenObjectHeader) {
            ImGui::SetNextItemOpen(true, ImGuiCond_Always);
            g_forceOpenObjectHeader = false;
        }
        std::shared_ptr<Entity> entityToDelete = nullptr;

        if (ImGui::CollapsingHeader("Objets")) {
            for (const std::shared_ptr<Entity> & entity : scene->getEntities()) {
                ImGui::PushID(entity.get());
                const std::string & name = entity->getName();
                if (name.empty())
                    continue;

                if (ImGui::Selectable(name.c_str(), g_entityExpanded[name])) {
                    g_entityExpanded[name] = !g_entityExpanded[name];
                }

                if (g_entityExpanded[name]) {
                    ImGui::Indent();

                    ImGui::SeparatorText("Position");

                    Vec3 position = entity->getTransform().getTranslation();

                    ImGui::Text("(%.2f, %.2f, %.2f)", position.x, position.y, position.z);

                    if (ImGui::DragFloat3("Position", &position.x, 0.01f, -100.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp)) {
                        entity->setPosition(position);
                    }

                    SectionsUtilitary::renderPositionEditor(name + " Position", position, [&](const Vec3 & newPos) {
                        entity->setPosition(newPos);
                    });

                    ImGui::SeparatorText("Echelle");
                    Vec3 scale = entity->getScale();
                    if (ImGui::DragFloat3("Scale", &scale.x, 0.01f, 0.01f, 100.0f, "%.2f")) {
                        entity->setScale(scale);
                    }

                    ImGui::SeparatorText("Rotation");
                    Vec3 currentEulerDeg = entity->getRotation().toEuler() * (180.0f / M_PI);
                    ImGui::Text("Orientation actuelle : (%.1f°, %.1f°, %.1f°)", currentEulerDeg.x, currentEulerDeg.y, currentEulerDeg.z);

                    static Vec3 deltaRotation = {0, 0, 0};
                    if (ImGui::DragFloat3("", &deltaRotation.x, 0.1f)) {
                        Quat delta = Quat::fromEuler(deltaRotation * (M_PI / 180.0f));
                        entity->setRotation(delta * entity->getRotation());
                        deltaRotation = {0, 0, 0};
                    }
                    if (ImGui::Button("Réinitialiser la rotation")) {
                        entity->setRotation(Quat::identity());
                        deltaRotation = {0, 0, 0};
                    }

                    if (ImGui::Button("Supprimer l'objet")) {
                        entityToDelete = entity;
                    }

                    ImGui::Unindent();
                    ImGui::Separator();
                }

                ImGui::PopID();
            }
            if (entityToDelete) {
                scene->removeEntity(entityToDelete);
                g_entityExpanded.erase(entityToDelete->getName());
            }
        }
    }

    void changeEntityCreatedSection(Scene * scene) {
        if (ImGui::CollapsingHeader("Objets à créer")) {
            ImGui::SeparatorText("Type d'entité à créer");

            static const char * items[] = {"Cube", "Sphere"};

            int currentItem = -1;
            if (g_typeEntityCreated == TypeEntityCreated::Cube)
                currentItem = 0;
            else if (g_typeEntityCreated == TypeEntityCreated::Sphere)
                currentItem = 1;

            if (ImGui::Combo("Type d'entité", &currentItem, items, IM_ARRAYSIZE(items))) {
                if (currentItem == 0)
                    g_typeEntityCreated = TypeEntityCreated::Cube;
                else if (currentItem == 1)
                    g_typeEntityCreated = TypeEntityCreated::Sphere;
            }
        }
    }

}
