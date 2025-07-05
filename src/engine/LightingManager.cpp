#include "engine/LightingManager.h"
#include <iostream>

LightingManager::LightingManager() {
    // // Par défaut, on peut initialiser une lumière blanche
    // lights.push_back({Vec3(0, 2, -3), Vec3(1,1,1), 1.0f});
}

void LightingManager::addLight(const Light & light) {
    lights.push_back(light);
}

void LightingManager::clearLights() {
    lights.clear();
}

void LightingManager::setupLightingOnScene() {
    // Paramètres sur la lumière diffuse et ambiante
    lightingSettings.diffuseIntensity = 0.2f;
    lightingSettings.ambientColor = Vec3(1.f, 1.f, 1.f);
    lightingSettings.ambientStrength = 0.4f;

    // Paramètres sur la lumière spéculaire
    lightingSettings.specularStrength = 0.2f;
    lightingSettings.shininess = 64.f;

    // Paramètres sur le fog
    lightingSettings.fogColor = Color(126.f, 126.f, 126.f, 1.f); // Gris clair
    lightingSettings.fogStart = 15.0f;
    lightingSettings.fogEnd = 30.0f;
    lightingSettings.fogDensity = 0.025f;
    lightingSettings.fogType = 0; // 0: aucun, 1: linéaire, 2: exp, 3: exp²

    colorMeshLight = Color::yellow(); // Couleur par défaut pour les meshes de lumière
}

void LightingManager::applyLightning(Shader & shader, const Vec3 & viewPos) const {
    shader.use();

    int activeCount = 0;
    for (const auto & light : lights) {
        if (light.isActive())
            activeCount++;
    }
    if (activeCount > MAX_LIGHTS)
        activeCount = MAX_LIGHTS;

    shader.set("numLights", activeCount);

    int sentIndex = 0;
    for (int i = 0; i < (int)lights.size() && sentIndex < activeCount; i++) {
        if (!lights[i].isActive())
            continue;
        std::string idx = std::to_string(sentIndex);
        shader.set("lights[" + idx + "].type", (int)lights[i].getType());
        shader.set("lights[" + idx + "].position", lights[i].getPosition());
        shader.set("lights[" + idx + "].direction", lights[i].getDirection().normalized());
        shader.set("lights[" + idx + "].color", Vec3(lights[i].getColor().r, lights[i].getColor().g, lights[i].getColor().b));
        shader.set("lights[" + idx + "].intensity", lights[i].getIntensity());
        shader.set("lights[" + idx + "].constant", lights[i].getConstant());
        shader.set("lights[" + idx + "].linear", lights[i].getLinear());
        shader.set("lights[" + idx + "].quadratic", lights[i].getQuadratic());
        sentIndex++;
    }

    // Paramètres globaux
    shader.set("ambientColor", lightingSettings.ambientColor);
    shader.set("ambientStrength", lightingSettings.ambientStrength);

    shader.set("diffuseColor", lightingSettings.diffuseColor);
    shader.set("diffuseIntensity", lightingSettings.diffuseIntensity);

    shader.set("specularColor", lightingSettings.specularColor);
    shader.set("specularStrength", lightingSettings.specularStrength);
    shader.set("shininess", lightingSettings.shininess);

    // Paramètres sur le fog
    shader.setVec3("fogColor", Vec3(lightingSettings.fogColor.r / 255.0f,
                                    lightingSettings.fogColor.g / 255.0f,
                                    lightingSettings.fogColor.b / 255.0f));
    shader.setFloat("fogStart", lightingSettings.fogStart);
    shader.setFloat("fogEnd", lightingSettings.fogEnd);
    shader.setFloat("fogDensity", lightingSettings.fogDensity);
    shader.setInt("fogType", lightingSettings.fogType);

    shader.set("viewPos", viewPos);
}

void LightingManager::applyPosLights(Shader & shader) const {
    shader.use();
    shader.set("color", Vec3(colorMeshLight));
}

const Light & LightingManager::getFirstDirectional() const {
    for (const Light & light : lights) {
        if (light.getType() == LightType::LIGHT_DIRECTIONAL) {
            return light;
        }
    }
    static Light dummyLight;
    dummyLight.setType(LightType::LIGHT_ERROR);
    return dummyLight;
}

Light * LightingManager::getFirstDirectional() {
    for (Light & light : lights) {
        if (light.getType() == LightType::LIGHT_DIRECTIONAL) {
            return &light;
        }
    }
    static Light dummyLight;
    dummyLight.setType(LightType::LIGHT_ERROR);
    return &dummyLight;
}

const std::vector<Light> LightingManager::getPonctualLight() const {
    std::vector<Light> ponctualLights;
    for (const Light & light : lights) {
        if (light.getType() == LightType::LIGHT_POINT) {
            ponctualLights.emplace_back(light);
        }
    }
    return ponctualLights;
}

std::vector<Light> * LightingManager::getPonctualLight() {
    std::vector<Light> * ponctualLights = new std::vector<Light>();
    for (Light & light : lights) {
        if (light.getType() == LightType::LIGHT_POINT) {
            ponctualLights->emplace_back(light);
        }
    }
    return ponctualLights;
}
