#pragma once
#include <vector>
#include "base/Vec.h"
#include "base/Shader.h"
#include "engine/Light.h"
#include "engine/LightSettings.h"

class LightingManager {
public:
    LightingManager();

    void addLight(const Light& light);
    void clearLights();

    // Met à jour les uniforms de lumière dans le shader (pour la lumière principale ici)
    void applyLightning(Shader& shader, const Vec3& viewPos);

    void applyPosLights(Shader& shader);

    // Accès aux paramètres pour pouvoir les modifier
    LightSettings& settings() { return lightingSettings; }
    const std::vector<Light>& getLights() const { return lights; }

private:
    // Liste des lumières dans la scène, côté glsl on à un MAX_LIGHTS = 8 donc attention
    std::vector<Light> lights;
    static constexpr int MAX_LIGHTS = 8;
    LightSettings lightingSettings;

    Color colorMeshLight = Color::red();
};