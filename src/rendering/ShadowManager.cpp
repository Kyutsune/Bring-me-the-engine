#include "rendering/ShadowManager.h"

ShadowManager::ShadowManager(Shader * dirShadowShader, Shader * pointShadowShader)
    : dirShadowShader(dirShadowShader), pointShadowShader(pointShadowShader) {}

void ShadowManager::init_directionnal_shadows() {
    directionalShadow.init();
}

void ShadowManager::renderShadows(const Scene & scene) {
    // Shadow map directionnelle
    directionalShadow.render(scene, *dirShadowShader);

    // Shadow maps cubemap ponctuelles
    const auto & pointLights = scene.getLightingManager().getPonctualLight();

    // Resize si besoin
    if (punctualShadows.size() < pointLights.size()) {
        size_t oldSize = punctualShadows.size();
        punctualShadows.resize(pointLights.size());
        for (size_t i = oldSize; i < pointLights.size(); ++i)
            punctualShadows[i] = PonctualShadowMap(1024, 1024);
    }

    // Rendu de chaque light active
    for (size_t i = 0; i < pointLights.size(); ++i) {
        if (!pointLights[i].isActive())
            continue;
        punctualShadows[i].render(scene, *pointShadowShader, pointLights[i]);
    }
}

void ShadowManager::bindShadows(Shader & shader, const Scene & scene) {
    const Light & dirLight = scene.getLightingManager().getFirstDirectional();

    if (dirLight.getType() != LightType::LIGHT_ERROR && dirLight.isActive()) {
        shader.set("lightSpaceMatrix", directionalShadow.getLightSpaceMatrix(), false);
        shader.set("dirLightDirection", dirLight.getDirection());

        directionalShadow.bindTexture(GL_TEXTURE3);
        shader.set("shadowMap", 3);
        shader.set("useDirectionalShadow", true);
    } else {
        shader.set("useDirectionalShadow", false);
    }

    shader.set("usePointShadow", punctualShadowEnabled);

    const auto & pointLights = scene.getLightingManager().getPonctualLight();
    size_t realCount = std::min(punctualShadows.size(), pointLights.size());
    constexpr size_t MAX_PONC_LIGHTS = 8;
    size_t count = std::min(realCount, MAX_PONC_LIGHTS);

    shader.set("pointLightNumber", static_cast<int>(count));

    // Bind les shadow maps actives (jusqu'à count)
    for (size_t i = 0; i < count; ++i) {
        punctualShadows[i].bindTexture(GL_TEXTURE4 + i);
    }
    // Si il y a moins que MAX_PONC_LIGHTS, binder les autres à 0 ou rien (optionnel)
    // OpenGL n'aime pas forcément binder des textures "vides" donc on peut laisser vide

    // Préparer un tableau complet de MAX_PONC_LIGHTS unités de texture
    std::vector<GLint> units(MAX_PONC_LIGHTS);
    for (size_t i = 0; i < MAX_PONC_LIGHTS; ++i) {
        units[i] = 4 + static_cast<GLint>(i);
    }
    shader.setArray("pointShadowMaps", units.data(), static_cast<int>(MAX_PONC_LIGHTS));

    // Préparer et passer les autres uniformes en remplissant avec des valeurs neutres pour le reste
    for (size_t i = 0; i < MAX_PONC_LIGHTS; ++i) {
        if (i < count) {
            shader.set("pointLightPositions[" + std::to_string(i) + "]", pointLights[i].getPosition());
            shader.set("pointLightFarPlanes[" + std::to_string(i) + "]", pointLights[i].computeEffectiveRange(0.01f));
            shader.set("pointLightIntensities[" + std::to_string(i) + "]", pointLights[i].getIntensity());
        } else {
            shader.set("pointLightPositions[" + std::to_string(i) + "]", Vec3(0.0f));
            shader.set("pointLightFarPlanes[" + std::to_string(i) + "]", 1.0f);
            shader.set("pointLightIntensities[" + std::to_string(i) + "]", 0.0f);
        }
    }
}