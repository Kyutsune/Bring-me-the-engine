#include "rendering/ShadowManager.h"

ShadowManager::ShadowManager(Shader* dirShadowShader, Shader* pointShadowShader)
    : dirShadowShader(dirShadowShader), pointShadowShader(pointShadowShader) {}

void ShadowManager::init_directionnal_shadows() {
    directionalShadow.init();
}

void ShadowManager::renderShadows(const Scene& scene) {
    // Shadow map directionnelle
    directionalShadow.render(scene, *dirShadowShader);

    // Shadow maps cubemap ponctuelles
    const auto& pointLights = scene.getLightingManager().getPonctualLight();

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

void ShadowManager::bindShadows(Shader& shader, const Scene& scene) {
    const Light& dirLight = scene.getLightingManager().getFirstDirectional();

    if (dirLight.getType() != LightType::LIGHT_ERROR && dirLight.isActive()) {
        shader.set("lightSpaceMatrix", directionalShadow.getLightSpaceMatrix(), false);
        shader.set("dirLightDirection", dirLight.getDirection());

        directionalShadow.bindTexture(GL_TEXTURE3);
        shader.set("shadowMap", 3);
        shader.set("useDirectionalShadow", true);
    } else {
        shader.set("useDirectionalShadow", false);
    }

    // Pour l’instant on gère que la première ponctuelle
    const auto& pointLights = scene.getLightingManager().getPonctualLight();
    if (!punctualShadows.empty() && !pointLights.empty()) {
        punctualShadows[0].bindTexture(GL_TEXTURE4);

        const Light& pl = pointLights[0];
        shader.set("pointShadowMap", 4);
        shader.set("lightPos", pl.getPosition());
        shader.set("farPlane", pl.computeEffectiveRange(0.01f));
        shader.set("pointLightIntensity", pl.getIntensity());
        shader.set("usePointShadow", true);
    } else {
        shader.set("usePointShadow", false);
    }
}
