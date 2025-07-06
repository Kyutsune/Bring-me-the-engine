#pragma once
#include "engine/Light.h"
#include "engine/LightSettings.h"
#include "math/Vec.h"
#include "rendering/Shader.h"
#include <vector>

class LightingManager {
public:
    LightingManager();

    void addLight(const Light & light);
    void clearLights();

    // Met à jour les uniforms de lumière dans le shader (pour la lumière principale ici)
    void applyLightning(Shader & shader, const Vec3 & viewPos) const;

    void applyPosLights(Shader & shader) const;

    // Accès aux paramètres pour pouvoir les modifier
    LightSettings & settings() { return m_lightingSettings; }
    const LightSettings & settings() const { return m_lightingSettings; }
    const std::vector<Light> & getLights() const { return m_lights; }

    const Light & getFirstDirectional() const;
    Light * getFirstDirectional();

    const std::vector<Light> getPonctualLight() const;
    std::vector<Light> * getPonctualLight();

    void setupLightingOnScene();

private:
    // Liste des lumières dans la scène, côté glsl on à un MAX_LIGHTS = 8 donc attention
    std::vector<Light> m_lights;
    LightSettings m_lightingSettings;

    // TODO: Pour l'instant on considère qu'une lumière ponctuelle est représentée par cette couleur
    //  On pourrait éventuellement rajouter une texture pour cette lumière
    Color m_colorMeshLight;
};