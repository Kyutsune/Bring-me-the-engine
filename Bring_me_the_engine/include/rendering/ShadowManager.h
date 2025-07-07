#pragma once

#include "engine/Scene.h"
#include "rendering/Shader.h"
#include "shadows/DirectionalShadowMap.h"
#include "shadows/PonctualShadowMap.h"

class ShadowManager {
public:
    ShadowManager(Shader * dirShadowShader, Shader * pointShadowShader);

    void init_directionnal_shadows();        // Initialise la shadow map directionnelle
    void renderShadows(const Scene & scene); // Rendu de toutes les ombres

    void bindShadows(Shader & shader, const Scene & scene); // Envoie les infos aux shaders principaux

    void debugSaveDirectionalShadow(const std::string & filename);
    void renderDebugQuad();

private:
    DirectionalShadowMap m_directionalShadow;
    std::vector<PonctualShadowMap> m_punctualShadows;

    Shader * m_dirShadowShader;
    Shader * m_pointShadowShader;

    bool m_punctualShadowEnabled = true;
};